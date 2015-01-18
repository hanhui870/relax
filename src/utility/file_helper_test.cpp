#include <gtest/gtest.h>
#include <relax/timer.h>
#include <relax/file_helper.h>
#include <iostream>

using namespace std;
using relax::FileHelper;
using relax::Status;

TEST(file_helper, common_actions) {
	relax::timer t;

	{
		string file("file-test/test.txt");
		string content;
		Status s = FileHelper::read(file, content);
		if (s.IsOK()) {
			cout << content << endl;
			EXPECT_STREQ("hello world.", content.c_str());
		} else {
			cout << s.message() << endl;
		}
	}

	{
		string file("file-test/test-not-exist.txt");
		string content;
		Status s = FileHelper::read(file, content);
		if (s.IsOK()) {
			cout << content << endl;
		} else {
			cout << s.message() << endl;
		}
	}

	{
		string file("file-test/test-multilen.txt");
		string content;
		Status s = FileHelper::read(file, content);
		if (s.IsOK()) {
			cout << content << endl;
			EXPECT_STREQ("hello world.\ngogo", content.c_str());
		} else {
			cout << s.message() << endl;
		}
	}
}
