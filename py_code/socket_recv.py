import numpy as np
import socket
import time


try:
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		s.connect(('192.168.1.23', 8700))
except socket.error as msg:
		print(msg)
		sys.exit(1)
        
        
while True:
            
            print('---------------------')

            pasttime = time.time()

            # depth
            s.send(b's')
            print('send s')
            all_data = []
            while True:
                data = s.recv(4096)#.decode("ascii") 
                all_data.extend(np.fromstring(data, dtype=np.uint16))
                if np.fromstring(data[-2:], dtype=np.uint16)[0]>6001:
                    break
            depth = np.array(all_data[:-1]).reshape((480,640))
            print('get depth')