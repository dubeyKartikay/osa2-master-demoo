rm -rf linux-5.19.9.2
mkdir linux-5.19.9.2
cp -r linux-5.19.9 ./linux-5.19.9.2 
cd linux-5.19.9.2
cd linux-5.19.9
make clean
make -j16