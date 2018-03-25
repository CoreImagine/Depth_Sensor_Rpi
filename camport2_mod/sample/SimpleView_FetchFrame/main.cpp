#include "../common/common.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <inttypes.h>	//used to print int32_t

#undef DEVELOPER_MODE

static char buffer[1024 * 1024];
static int  n;
static volatile bool exit_main;

static int fps_counter = 0;
static clock_t fps_tm = 0;
 

struct CallbackData {
    int             index;
    TY_DEV_HANDLE   hDevice;
    DepthRender*    render;
    cv::Mat         depth;	//added
};

void frameHandler(TY_FRAME_DATA* frame, void* userdata, int forClientSockfd) {

    char inputBuffer[32] = {};
    char recv_key[32] = {"s"};

    CallbackData* pData = (CallbackData*) userdata;
    LOGD("=== Get frame %d", ++pData->index);


    cv::Mat depth, irl, irr, color;
    parseFrame(*frame, &depth, &irl, &irr, &color, 0);
    if(!depth.empty()){
        //cv::Mat colorDepth = pData->render->Compute(depth);
        //cv::imshow("ColorDepth", colorDepth);
	
	//int dept_cent = depth.at<char>(320,240);
	uint16_t dept = depth.at<uint16_t>(320,240);
	char strd[32];
	sprintf(strd,"%d",dept);
  	printf("dept at center is ");
	printf(strd);
	printf(" mm\n");

	//-------cvmat to 1D array---------
	std::vector<uint16_t> array;
	if (depth.isContinuous()) {
		array.assign((uint16_t*)depth.datastart, (uint16_t*)depth.dataend);
	} else {
	for (int i = 0; i < depth.rows; ++i) {
		array.insert(array.end(), depth.ptr<uint16_t>(i), depth.ptr<uint16_t>(i)+depth.cols);
			}
		}


	//put @ symbol
	//array.insert(array.end(),(uint16_t) '@');
	
	uint16_t msg[307201];
	std::copy(array.begin(), array.end(), msg);
	msg[307201]=0xFFFF;

    //-----------socket send--------
      recv(forClientSockfd,inputBuffer,sizeof(inputBuffer),0);
        printf("Get:%s\n",inputBuffer);
	//int ind=0;
	if(strcmp(inputBuffer,recv_key)==0){
		printf("KEY!! sent size= %d bytes",sizeof(msg));
        	send(forClientSockfd,msg,sizeof(msg),0);

	}
    //-----------------------------


    }
    //end

    //if(!irl.empty()){ cv::imshow("LeftIR", irl); }
    //if(!irr.empty()){ cv::imshow("RightIR", irr); }
    //if(!color.empty()){ cv::imshow("Color", color); }

    LOGD("=== Callback: Re-enqueue buffer(%p, %d)", frame->userBuffer, frame->bufferSize);
    ASSERT_OK( TYEnqueueBuffer(pData->hDevice, frame->userBuffer, frame->bufferSize) );
}

int main(int argc, char* argv[]) {


    const char* IP = NULL;
    TY_DEV_HANDLE hDevice;
    int32_t color, ir, depth; 
    //color = ir = depth = 1;

    color=0;
    ir=0;
    depth=1;


    LOGD("=== Init lib");
    ASSERT_OK( TYInitLib() );
    TY_VERSION_INFO* pVer = (TY_VERSION_INFO*)buffer;
    ASSERT_OK( TYLibVersion(pVer) );
    LOGD("     - lib version: %d.%d.%d", pVer->major, pVer->minor, pVer->patch);

    if(IP) {
        LOGD("=== Open device %s", IP);
        ASSERT_OK( TYOpenDeviceWithIP(IP, &hDevice) );
    } else {
        LOGD("=== Get device info");
        ASSERT_OK( TYGetDeviceNumber(&n) );
        LOGD("     - device number %d", n);

        TY_DEVICE_BASE_INFO* pBaseInfo = (TY_DEVICE_BASE_INFO*)buffer;
        ASSERT_OK( TYGetDeviceList(pBaseInfo, 100, &n) );

        if(n == 0) {
            LOGD("=== No device got");
            return -1;
        }

        LOGD("=== Open device 0");
        ASSERT_OK( TYOpenDevice(pBaseInfo[0].id, &hDevice) );
    }

#ifdef DEVELOPER_MODE
    LOGD("=== Enter Developer Mode");
    ASSERT_OK(TYEnterDeveloperMode(hDevice));
#endif

    int32_t allComps;
    ASSERT_OK( TYGetComponentIDs(hDevice, &allComps) );
    if(allComps & TY_COMPONENT_RGB_CAM  && color) {
        LOGD("=== Has RGB camera, open RGB cam");
        ASSERT_OK( TYEnableComponents(hDevice, TY_COMPONENT_RGB_CAM) );
    }

    int32_t componentIDs = 0;
    LOGD("=== Configure components, open depth cam");
    if (depth) {
        componentIDs = TY_COMPONENT_DEPTH_CAM;  
    }
    
    if (ir) {
        componentIDs |= TY_COMPONENT_IR_CAM_LEFT; 
    }
    
    if (depth || ir) {
        ASSERT_OK( TYEnableComponents(hDevice, componentIDs) );
    }

    LOGD("=== Configure feature, set resolution to 640x480.");
    LOGD("Note: DM460 resolution feature is in component TY_COMPONENT_DEVICE,");
    LOGD("      other device may lays in some other components.");
    TY_FEATURE_INFO info;
    TY_STATUS ty_status = TYGetFeatureInfo(hDevice, TY_COMPONENT_DEPTH_CAM, TY_ENUM_IMAGE_MODE, &info);
    if ((info.accessMode & TY_ACCESS_WRITABLE) && (ty_status == TY_STATUS_OK)) {
        int err = TYSetEnum(hDevice, TY_COMPONENT_DEPTH_CAM, TY_ENUM_IMAGE_MODE, TY_IMAGE_MODE_640x480);
        ASSERT(err == TY_STATUS_OK || err == TY_STATUS_NOT_PERMITTED);
    }

    LOGD("=== Prepare image buffer");
    int32_t frameSize;
    ASSERT_OK( TYGetFrameBufferSize(hDevice, &frameSize) );
    LOGD("     - Get size of framebuffer, %d", frameSize);
    ASSERT( frameSize >= 640 * 480 * 2 );

    LOGD("     - Allocate & enqueue buffers");
    char* frameBuffer[2];
    frameBuffer[0] = new char[frameSize];
    frameBuffer[1] = new char[frameSize];
    LOGD("     - Enqueue buffer (%p, %d)", frameBuffer[0], frameSize);
    ASSERT_OK( TYEnqueueBuffer(hDevice, frameBuffer[0], frameSize) );
    LOGD("     - Enqueue buffer (%p, %d)", frameBuffer[1], frameSize);
    ASSERT_OK( TYEnqueueBuffer(hDevice, frameBuffer[1], frameSize) );

    LOGD("=== Register callback");
    LOGD("Note: Callback may block internal data receiving,");
    LOGD("      so that user should not do long time work in callback.");
    LOGD("      To avoid copying data, we pop the framebuffer from buffer queue and");
    LOGD("      give it back to user, user should call TYEnqueueBuffer to re-enqueue it.");
    DepthRender render;
    CallbackData cb_data;
    cb_data.index = 0;
    cb_data.hDevice = hDevice;
    cb_data.render = &render;
    // ASSERT_OK( TYRegisterCallback(hDevice, frameHandler, &cb_data) );

    LOGD("=== Disable trigger mode");
    ty_status = TYGetFeatureInfo(hDevice, TY_COMPONENT_DEVICE, TY_BOOL_TRIGGER_MODE, &info);
    if ((info.accessMode & TY_ACCESS_WRITABLE) && (ty_status == TY_STATUS_OK)) {
        ASSERT_OK(TYSetBool(hDevice, TY_COMPONENT_DEVICE, TY_BOOL_TRIGGER_MODE, false));
    }

    //show IR val
    int32_t IR_value;
    int32_t IR_off_val=0;
    int32_t IR_on_val=100;
    ASSERT_OK( TYGetInt (hDevice, TY_COMPONENT_LASER, TY_INT_LASER_POWER, &IR_value));    printf("IR value is: ");
    printf("%" PRId32 "\n", IR_value);
    //

    LOGD("=== Start capture");
    ASSERT_OK( TYStartCapture(hDevice) );

    LOGD("=== While loop to fetch frame");
    exit_main = false;
    TY_FRAME_DATA frame;


//-----------------------start----socketset
    //socket的建立
    //char inputBuffer[32] = {};
    //char recv_key[32] = {"s"};
    //uint16_t message[307201];
    

    int sockfd = 0,forClientSockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線
    struct sockaddr_in serverInfo,clientInfo;
    socklen_t addrlen = sizeof(clientInfo);
    bzero(&serverInfo,sizeof(serverInfo));

    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(8700);
    bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));

    listen(sockfd,5);

    forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);
        //send(forClientSockfd,test_char,1,0);

//---------------------------------endof socketset


    while(!exit_main) {
	//MSLEEP(260);
	//LOGD("Delay for 3s");
        int err = TYFetchFrame(hDevice, &frame, -1);
        if( err != TY_STATUS_OK ) {
            LOGD("... Drop one frame");
        } else {
            //turn off IR
	    //ASSERT_OK( TYSetInt (hDevice, TY_COMPONENT_LASER, TY_INT_LASER_POWER, IR_off_val));
            //handle frame
            frameHandler(&frame, &cb_data, forClientSockfd);
	    //turn on IR
            //ASSERT_OK( TYSetInt (hDevice, TY_COMPONENT_LASER, TY_INT_LASER_POWER, IR_on_val));
        }

//#ifdef DEVELOPER_MODE
//        DEVELOPER_MODE_PRINT();
//#endif
    }

    ASSERT_OK( TYStopCapture(hDevice) );
    ASSERT_OK( TYCloseDevice(hDevice) );
    ASSERT_OK( TYDeinitLib() );
    // MSLEEP(10); // sleep to ensure buffer is not used any more
    delete frameBuffer[0];
    delete frameBuffer[1];

    LOGD("=== Main done!");
    return 0;
}
