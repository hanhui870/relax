#include <gtest/gtest.h>
#include <relax/cookie.h>
#include <relax/timer.h>

TEST(cookie, common_actions)
{
	relax::timer t;

	using namespace ::relax::fetcher;
	using namespace std;
	CookieManager* ckm=CookieManager::GetInstance();



	cout<<"inited"<<endl;

}
