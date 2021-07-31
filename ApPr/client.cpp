
#include <iostream>
#include "/home/kianaz/Documents/ApPr/httplib.h"
using namespace std;
int main(void)
{
    
httplib::Client cli("localhost", 8080);
cout<<"hi"<<endl;
if (auto res= cli.Get("/hi")){
    cout<<"hi"<<endl;
    if(res->status == 200) {
        cout<<"hi"<<endl;
        cout << res->body <<endl;
    }
}
// auto res = cli.Get("/hi");
// res->status;
// res->body;
}
