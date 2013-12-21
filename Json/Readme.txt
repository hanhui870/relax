CPPJson安装

cd /biz/soft/jsoncpp-src-0.5.0/

#编译安装
scons platform=linux-gcc

#移到系统库目录
cp include/* /usr/include/
cp libs/linux-gcc-4.8.2/* /usr/lib/