#include <gtest/gtest.h>
#include <relax/cookie.h>
#include <relax/timer.h>

TEST(cookie, common_actions)
{
	relax::timer t;

	using namespace ::relax::fetcher;
	using ::relax::Status;
	using ::relax::fetcher::CookieValue;
	using namespace std;
	CookieManager* ckm=CookieManager::GetInstance();
	Cookie ck=ckm->GetCookie("zjgsdx.com");

	//空字符
	string tmp("");
	cout<<"blank string size:"<<tmp.size()<<endl;
	EXPECT_EQ(0, tmp.size());

	Status s;
	s=ck.Add("Token=v2gscbncfz5gk5bx4xphlkma4rlnvm13l65er8ix; expires=Fri, 20-Sep-2019 03:16:02 GMT; path=/; HttpOnly; secure;");
	EXPECT_EQ(true, s.IsOK());

	//key=>value pair test
	s=ck.Add("hanhui", "zhujingfa");
	EXPECT_EQ(true, s.IsOK());

	CookieValue value;
	s=ck.Get("hanhui", value);
	EXPECT_STREQ("zhujingfa", value.value().c_str());
	s=ck.Get("Token", value);
	EXPECT_STREQ("v2gscbncfz5gk5bx4xphlkma4rlnvm13l65er8ix", value.value().c_str());
	CookieString cstr;
	s=ck.Get("Token", cstr);
	cout<<"Cookie Token string:"<<cstr.ToString()<<endl;

	s=ck.Add("sechrefdafda");
	if(s.IsFail()){
	    cout<<"Failed to add: "<<s.message()<<endl;
	}else{
	    EXPECT_EQ(true, s.IsOK());
	}
}
