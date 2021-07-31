
#include <iostream>
#include "/home/kianaz/Documents/ApPr/httplib.h"
using namespace std;
int main(void)
{
    
httplib::Client cli("localhost", 8080);
if (auto res= cli.Get("/hi")){
    if(res->status == 200) {
        cout << res->body <<endl;
    }
}


if (auto res= cli.Get("/body-header-param")){
    if(res->status == 200) {
        cin>> req;
    }
}
// auto res = cli.Get("/hi");
// res->status;
// res->body;
}
