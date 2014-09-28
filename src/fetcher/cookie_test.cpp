#include <gtest/gtest.h>
#include <relax/cookie.h>
#include <relax/timer.h>

TEST(cookie, common_actions)
{
	relax::timer t;

	using namespace ::relax::fetcher;
	using ::relax::Status;
	using namespace std;
	CookieManager* ckm=CookieManager::GetInstance();

	//TODO  to be checked
	Cookie ck=ckm->GetCookie("zjgsdx.com");

	Status s;
	s=ck.Add("Token=v2gscbncfz5gk5bx4xphlkma4rlnvm13l65er8ix; expires=Fri, 20-Sep-2019 03:16:02 GMT; path=/; HttpOnly; secure;");
	EXPECT_EQ(true, s.IsOK());

	//key=>value pair test
	s=ck.Add("hanhui", "zhujingfa");
	cout<<"Add cookie add cookie: "<<s.message()<<endl;
	EXPECT_EQ(true, s.IsOK());

	//CookieValue value;
	//s=ck.Get("hanhui", value);
	//EXPECT_STREQ("zhujingfa", value);
	//EXPECT_STREQ("v2gscbncfz5gk5bx4xphlkma4rlnvm13l65er8ix", ck.Get("Token").c_str());
}
