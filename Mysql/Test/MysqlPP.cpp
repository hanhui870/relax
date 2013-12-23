#include <iostream>
#include <mysql++/mysql++.h>

using namespace std;
using namespace mysqlpp;

int main(int argc, char **argv){
    try {
        Connection conn(true);
        if(!conn.connect("iyunlin", "localhost", "hanhui", "han@#$%2213")){
            cout<<"DB connect error."<<endl;
            return 0;
        }

        Query query = conn.query("SELECT * FROM  `system_log` LIMIT 0 , 30");
        StoreQueryResult res = query.store();

        StoreQueryResult::const_iterator iter;
        //前置自增性能更好
        for(iter=res.begin(); iter!=res.end(); ++iter){
            Row it=*iter;
            cout<<it[0]<<"\t"<<it[1]<<"\t"<<it[2]<<"\t"<<it[3]<<"\n";
        }

    }catch (const BadQuery& er) {
        // Handle any query errors
        cerr << "Query error: " << er.what() << endl;
        return -1;
    }

    return 0;
}


