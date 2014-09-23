#include <gtest/gtest.h>
#include <relax/cookie.h>
#include <relax/timer.h>

TEST(cookie, common_actions)
{
	relax::timer t;

	using namespace ::relax::fetcher;
	using namespace std;
	CookieManager* ckm=CookieManager::GetInstance();

	//TODO  to be checked
	Cookie ck=ckm->GetCookie("zjgsdx.com");
	ck.Add("Token=v2gscbncfz5gk5bx4xphlkma4rlnvm13l65er8ix; expires=Fri, 20-Sep-2019 03:16:02 GMT; path=/; HttpOnly; secure;");
	ck.Add("hanhui", "zhujingfa");

	EXPECT_STREQ("zhujingfa", ck.Get("hanhui").c_str());
	EXPECT_STREQ("v2gscbncfz5gk5bx4xphlkma4rlnvm13l65er8ix", ck.Get("Token").c_str());
}
