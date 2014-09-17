/**
 * Relax library
 *
 * @author 祝景法
 * @email zhujingfa@gmail.com
 *
 * @since 2014/09/17
 */
#ifndef ROBOT_FETCHER_H_
#define ROBOT_FETCHER_H_

namespace relax{
namespace fetcher{

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

}//adn
}//robot

#endif
