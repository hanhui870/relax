#include <gtest/gtest.h>
#include <relax/cookie.h>
#include <relax/timer.h>
#include <memory>

TEST(cookie, common_actions)
{
	relax::timer t;

	using namespace ::relax::fetcher;
	using ::relax::Status;
	using ::relax::fetcher::CookieValue;
	using namespace std;
	CookieManager& ckm =CookieManager::GetInstance();
	//空字符
    string tmp("");
    Status s;

	{
		Cookie& ck=ckm.GetCookie("zjgsdx.com");

		cout<<"blank string size:"<<tmp.size()<<endl;
		EXPECT_EQ(0, tmp.size());

		s=ck.Add("Token=v2gscbncfz5gk5bx4xphlkma4rlnvm13l65er8ix; expires=Fri, 20-Sep-2019 03:16:02 GMT; path=/; HttpOnly; secure;");
		EXPECT_EQ(true, s.IsOK());

		ckm.GetCookie("zjgsdx.com").GetAll(tmp);
		std::cout<<"CookieManager 1 Result:";
		relax::Debug::out(tmp);
		EXPECT_STREQ("Token=v2gscbncfz5gk5bx4xphlkma4rlnvm13l65er8ix; ", tmp.c_str());

		//删除一个域名
		ckm.DeleteDomain("zjgsdx.com");
		ckm.GetCookie("zjgsdx.com").GetAll(tmp);
		std::cout<<"CookieManager 2 Result:";
		relax::Debug::out(tmp);
		EXPECT_STREQ("", tmp.c_str());

		s=ckm.GetCookie("zjgsdx.com").Add("Token=v2gscbncfz5gk5bx4xphlkma4rlnvm13l65er8ix; expires=Fri, 20-Sep-2019 03:16:02 GMT; path=/; HttpOnly; secure;");
		EXPECT_EQ(true, s.IsOK());
	}


	//清空整个库 所有之前的cookie引用失效
	ckm.reset();
	s=ckm.GetCookie("zjgsdx.com").Add("Token=newadd ed; expires=Fri, 20-Sep-2019 03:16:02 GMT; path=/; HttpOnly; secure;");
	EXPECT_EQ(true, s.IsOK());
	ckm.GetCookie("zjgsdx.com").GetAll(tmp);
	std::cout<<"CookieManager 3 Result:";
	relax::Debug::out(tmp);
	EXPECT_STREQ("Token=newadd ed; ", tmp.c_str());

	{
		Cookie& ck=ckm.GetCookie("zjgsdx.com");
		s=ck.Add("spanner=peFXug9jwtvpRIuthTpRynbA4ws1VM1/;path=/;secure;");
		s=ck.Add("umt=HBf4721f420e82d869184a949e2eefcc2a; Domain=.alipay.com; Path=/; HttpOnly");
		s=ck.Add("CAT=deleted; expires=Fri, 27-Sep-2013 15:21:13 GMT");
		s=ck.Add("OUTFOX_SEARCH_USER_ID=551468692@58.101.75.242; domain=huihui.cn; path=/; expires=Mon, 19-Sep-2044 15:21:15 GMT");
		s=ck.Add("hanhui", "zhujingfa");
		EXPECT_EQ(true, s.IsOK());

		ckm.GetCookie("zjgsdx.com").GetAll(tmp);
		std::cout<<"CookieManager Result:";
		relax::Debug::out(tmp);

		CookieValue value;
		s=ck.Get("hanhui", value);
		EXPECT_STREQ("zhujingfa", value.value().c_str());
		s=ck.Get("Token", value);
		EXPECT_STREQ("newadd ed", value.value().c_str());
		CookieString cstr;
		s=ck.Get("Token", cstr);
		cout<<"Cookie Token string:"<<cstr.ToString()<<endl;

		s=ck.Get("OUTFOX_SEARCH_USER_ID", cstr);
		cout<<"Cookie OUTFOX_SEARCH_USER_ID string:"<<cstr.ToString()<<endl;

		s=ck.Add("sechrefdafda");
		if(s.IsFail()){
			cout<<"Failed to add: "<<s.message()<<endl;
		}
		EXPECT_EQ(false, s.IsOK());

		string result;
		s=ck.GetAll(result);
		cout<<"Result KV string: "<<result<<endl;
		EXPECT_STREQ("OUTFOX_SEARCH_USER_ID=551468692@58.101.75.242; Token=newadd ed; hanhui=zhujingfa; spanner=peFXug9jwtvpRIuthTpRynbA4ws1VM1/; umt=HBf4721f420e82d869184a949e2eefcc2a; ", result.c_str());
		EXPECT_EQ(true, s.IsOK());
	}

}
