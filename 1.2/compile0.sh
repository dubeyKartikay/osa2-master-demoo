rm -rf linux-5.19.9.0
mkdir linux-5.19.9.0
cp -r linux-5.19.9 ./linux-5.19.9.0 
cd linux-5.19.9.0
cd linux-5.19.9
make clean
make -j16