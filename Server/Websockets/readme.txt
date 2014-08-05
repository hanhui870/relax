LibWebsockets编程

* 下载地址： http://libwebsockets.org/trac/libwebsockets

* 编译：cmake ./ -DOPENSSL_ROOT_DIR=/usr/local/ssl

* cygwin编译会报bug：/cygdrive/d/techExplorer/libwebsockets/lib/parsers.c:33:2: 错误：数组下标类型为‘char’ [-Werror=char-subscripts] c = tolower(c);
原来c是char c，改为unsigned char c后搞定。因为char是含正负的，在某些情况下作为索引是无效的，编译器有专门这项提示。
