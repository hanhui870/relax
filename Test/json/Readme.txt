一、CPPJson安装
下载页：http://sourceforge.net/projects/jsoncpp/

cd /biz/soft/jsoncpp-src-0.5.0/

#编译安装
scons platform=linux-gcc

#移到系统库目录
cp include/* /usr/include/
cp libs/linux-gcc-4.8.2/* /usr/lib/

2、使用Rapidjson，性能非常不错
下载页：https://code.google.com/p/rapidjson/wiki/UserGuide