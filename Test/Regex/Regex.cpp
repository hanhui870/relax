#include <regex>
#include <iostream>
using namespace std;

int main()
{
    // find XML/HTML-tagged value (using default syntax):
    regex reg1("<.*>.*</.*>");
    bool found = regex_match ("<tag>value</tag>", reg1); // regular expression
    if(found){
    	cout<<"Found!"<<endl;
    }else{
    	cout<<"Not found!"<<endl;
    }

    return 0;
}
