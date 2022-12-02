rm -rf linux-5.19.9.1
mkdir linux-5.19.9.1
cp -r linux-5.19.9 ./linux-5.19.9.1 
cd linux-5.19.9.1
cd linux-5.19.9
make clean
make -j16