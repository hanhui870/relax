/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#ifndef RELAX_FETCHER_H_
#define RELAX_FETCHER_H_

namespace relax{

class Curl;

/**
 * 资源获取器
 */
class Fetcher{
public:
    Fetcher();



private:
	bool InitCurl();

	Curl* _curl;
};

} //relax

#endif//RELAX_FETCHER_H_
