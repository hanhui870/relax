CPP=g++

#gtes已经支持c++11，但是不能存在__STRICT_ANSI__宏变量，cygwin取消掉即可；其他环境未测试
CXXFLAGS=-g -std=c++11 -DGTEST_LANG_CXX11=1 -U__STRICT_ANSI__
#C语言版定义
CFLAGS=-g

LIBS=-L/usr/local/lib   -lgtest -lgtest_main
LIBOBJECTS=algorithm.o test.o
BINARY=test.exe

all: $(BINARY)

$(BINARY): $(LIBOBJECTS)
	$(CPP) -o test.exe $(LIBOBJECTS) $(LIBS)

$(objects): %.o: %.c 
	$(CPP) -c $(CXXFLAGS) $< -o $@ 
	
.PHONY:clean 
clean: 
	-rm $(LIBOBJECTS) $(BINARY)
    