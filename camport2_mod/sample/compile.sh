#/bin/sh

echo "Please Open in sample dir! auto compiler bt cheng"

rm -r build/
mkdir build
cd build/
cmake ..
make -j4
