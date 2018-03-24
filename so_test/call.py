#python3.5

from ctypes import cdll

api=cdll.LoadLibrary("./test.so")
#api=CDLL("./test.so")
api.add.argtypes[c_int, c_int]
api.add.restype=c_int
api.sub.argtypes[c_int, c_int]
api.sub.restype=c_int


a=api.add(3,2)
b=api.sub(3,2)
print (a)
print (b)

