import socket
import sys
import picamera
import time
import numpy as np
from PIL import Image

import cv2
import ast




#/home/pi/Depth_Sensor_Rpi/camport2_mod/sample/build/bin/SimpleView_FetchFrame
#server
#client

host = '192.168.1.13'  # server address
port = int(sys.argv[1])
address = (host, port)
socket01 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket01.bind(address)  
socket01.listen(1)  # listen(backlog)
print('Socket Startup')
conn, addr = socket01.accept()  # 
print('Connected by', addr)
################
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((host, 8700))
except socket.error as msg:
    #print(msg)
    sys.exit(1)
################

with picamera.PiCamera() as camera:
    camera.resolution = (560, 460)
    time.sleep(2)
    start = time.time()
    while True:
    	print("==============================")
        ##################################################
        # start transition
        #print(1)
        camera.capture('test.jpg')
        #print(2)
        imgFile = open("test.jpg", "rb")
        #print(3)
        get = conn.recv(512).decode()
        #print(4)
        try:
            GET = True
            get = ast.literal_eval(get)
        except:
            GET = False

################
        s.send(b's')
        #print('send s')
        all_data = []
        while True:
            data = s.recv(4096)#.decode("ascii") 
            all_data.extend(np.fromstring(data, dtype=np.uint16))
            if np.fromstring(data[-2:], dtype=np.uint16)[0]>6001:
                break

        depth = np.array(all_data[:-1]).reshape((480,640))[10:470,70:630]#460,560
        DEPTH = depth.copy()
        d = []
        d.append(depth[:,:180])
        d.append(depth[:,180:380])
        d.append(depth[:,380:])
        #print(np.min((d[0]+6000)%6001))
        #print(np.min((d[1]+6000)%6001))
        #print(np.min((d[2]+6000)%6001))
    	DIRECTION = ['left','middle','right']
    	save_json = {}
    	for i in range(3):
    		save_json[DIRECTION[i]]=[np.min((d[i]+6000)%6001)]
        if GET:

        	ADAPT_X = -40
        	ADAPT_Y = -40   # -80     	
	        for x in get:
	        	n = x[0]
	        	y1,x1 = x[1]
	        	y2,x2 = x[2]
	        	X1,X2,Y1,Y2 = x1,x2,y1,y2
	        	x1,x2,y1,y2 = x1+ADAPT_X,x2+ADAPT_X,y1+ADAPT_Y,y2+ADAPT_Y
	        	x1 = 0 if x1<0 else x1
	        	x2 = 0 if x2<0 else x2
	        	y1 = 0 if y1<0 else y1
	        	y2 = 0 if y2<0 else y2
	        	y = (Y1+Y2)/2.0
	        	save_json[DIRECTION[np.argmax([y>=0 and y<180,y>=180 and y < 380, y >= 380])]].append([n,X1,Y1,X2,Y2,np.min((DEPTH[x1:x2,y1:y2]+6000)%6001)])


	        	#print(y,np.argmax([y>=0 and y<180,y>=180 and y < 380, y >= 380]))

	        	#print(n,x1,x2,y1,y2)
	        	#print(np.shape(DEPTH[x1:x2,y1:y2]))
	        	#print(np.min((DEPTH[x1:x2,y1:y2]+6000)%6001))



	        	#print('-------')
	        	cv2.rectangle(DEPTH, (y1, x1), (y2, x2),[6000,6000,6000], 2)
	        	cv2.putText(DEPTH, n, (y1+10, x1+10),cv2.FONT_HERSHEY_SIMPLEX, 0.5, [6000,6000,6000], 2)

	        


        
        for i in range(3):
            depth_img = d[i]/6000.0*255
            img = Image.fromarray(depth_img).convert('RGB')
            img.save("depth_{}.jpg".format(i))
		

        depth_img = DEPTH/6000.0*255
        img = Image.fromarray(depth_img).convert('RGB')
        img.save("depth.jpg")


        print(save_json)

        #with open("dep.txt","wb") as f:
        #    f.write(str(depth))

        #edges = cv2.Canny(depth,100,200)
        #scipy.misc.imsave('edge.jpg', edges)
################

        while True:
            imgData = imgFile.readline(512)    
            if not imgData:
                #print(len(imgData))
                conn.send(b'fuckfuck')        
                break  # break loop after finishing
            conn.send(imgData)
        imgFile.close()
        print('current image end ',time.time()-start)
        start=time.time()
        ##################################################


conn.close()  
socket01.close()
print('server close')