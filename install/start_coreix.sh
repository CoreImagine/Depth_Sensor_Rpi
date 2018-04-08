#!/bin/bash

echo "Coreix is Initializing..."

cd ~/Depth_Sensor_Rpi/install/bin/
pwd

./depth_C &
python3.5 server.py &
python3.5 socket_recv.py &

echo "All processes have been started!"
