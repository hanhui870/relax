CPP=g++

#gtes已经支持c++11，但是不能存在__STRICT_ANSI__宏变量，cygwin取消掉即可；其他环境未测试
CXXFLAGS=-g -std=c++11 -DGTEST_LANG_CXX11=1 -U__STRICT_ANSI__ -I../../include

LIBS=-L/usr/local/lib   -lgtest -lgtest_main -lboost_timer.dll -lboost_system.dll
OBJECTS=time_helper.o time_helper_test.o env_helper.o env_helper_test.o string_helper.o string_helper_test.o
BINARY=test.exe

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CPP) -o $(BINARY) $(OBJECTS) $(LIBS)

$(OBJECTS): %.o: %.cpp
	$(CPP) -c $(CXXFLAGS) $< -o $@ 
	
.PHONY:clean 
clean: 
	-rm -f $(OBJECTS) $(BINARY)
    