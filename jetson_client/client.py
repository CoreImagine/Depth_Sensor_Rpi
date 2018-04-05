import socket
import sys
import numpy as np
from PIL import Image


import argparse
import cv2
import os
import time
import scipy.misc


# construct the argument parse and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--image", 
	help="path to input image",
	default="images")
ap.add_argument("-p", "--prototxt", 
	help="path to Caffe 'deploy' prototxt file",
	default="MobileNetSSD_deploy.prototxt.txt")
ap.add_argument("-m", "--model", 
	help="path to Caffe pre-trained model",
	default="MobileNetSSD_deploy.caffemodel")
ap.add_argument("-c", "--confidence", type=float, default=0.6,
	help="minimum probability to filter weak detections")
ap.add_argument("-port", "--port", type=float,
	help="port")
args = vars(ap.parse_args())

# initialize the list of class labels MobileNet SSD was trained to
# detect, then generate a set of bounding box colors for each class
CLASSES = ["background", "aeroplane", "bicycle", "bird", "boat",
	"bottle", "bus", "car", "cat", "chair", "cow", "diningtable",
	"dog", "horse", "motorbike", "person", "pottedplant", "sheep",
	"sofa", "train", "tvmonitor"]
COLORS = np.random.uniform(0, 255, size=(len(CLASSES), 3))



print("[INFO] loading model...")
net = cv2.dnn.readNetFromCaffe(args["prototxt"], args["model"])

# host = socket.gethostname()
# port = 5000
host = '192.168.1.13'  # 對server端為主機位置
port = int(args["port"])
address = (host, port)

socket02 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# AF_INET:默認IPv4, SOCK_STREAM:TCP

socket02.connect(address)  # 用來請求連接遠程服務器

data = []
while True:
	##################################################
	# 開始接收
	print('begin write image file')

	#print(1)

	s= time.time()
	imgFile = open('test.jpg', 'wb')  # 開始寫入圖片檔
	#print(2)
	#socket02.send(b'gogogo')
	send_data = b'gogogo' if data == [] else str.encode(str(data))
	socket02.send(send_data)
	data = []
	last_img_Data = str.encode(str([]))
	#print(3)
	while True:
	    imgData = socket02.recv(512)  # 接收遠端主機傳來的數據
	    #print('================')
	    #print(imgData[-4:],imgData[-4:]==b'fuck')
	    #print('@@@',last_img_Data[-4:]+imgData[-4:])
	    #print((last_img_Data[-4:]+imgData[-4:])[-4:])
	    if (last_img_Data[-4:]+imgData[-4:])[-4:]==b'fuck':
	    	break
	    imgFile.write(imgData)
	    last_img_Data = imgData
	imgFile.close()
	#print(4)
	###
	time.sleep(0.2)
	try:
		image = cv2.imread('test.jpg')
		image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
		#image = scipy.misc.imread('test.jpg')
		#print(image)	
		(h, w) = image.shape[:2]
		blob = cv2.dnn.blobFromImage(cv2.resize(image, (300, 300)), 0.007843, (300, 300), 127.5)
		net.setInput(blob)
		detections = net.forward()
		
		for i in np.arange(0, detections.shape[2]):
			confidence = detections[0, 0, i, 2]
			if confidence > args["confidence"]:
				idx = int(detections[0, 0, i, 1])
				box = detections[0, 0, i, 3:7] * np.array([w, h, w, h])
				(startX, startY, endX, endY) = box.astype("int")

				# display the prediction
				label = "{}: {:.2f}%".format(CLASSES[idx], confidence * 100)
				#print("{}".format(label),(startX, startY), (endX, endY))
				data.append([CLASSES[idx],(startX, startY), (endX, endY)])
				cv2.rectangle(image, (startX, startY), (endX, endY),COLORS[idx], 2)
				y = startY - 15 if startY - 15 > 15 else startY + 15
				cv2.putText(image, label, (startX, y),cv2.FONT_HERSHEY_SIMPLEX, 0.5, COLORS[idx], 2)
		scipy.misc.imsave('outfile.jpg', image)
		#
		#edges = cv2.Canny(image,100,200)
		#scipy.misc.imsave('edge.jpg', edges)

		print(data,' | last: ',time.time()-s)
		print("==============================")
		s=time.time()
	except:
		pass

	##################################################

socket02.close()  # 關閉
print('client close')