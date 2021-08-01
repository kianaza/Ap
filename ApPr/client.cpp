
#include<iostream>
#include<sstream>
#include<map>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>

#include "httplib.h"

using namespace std;

int main() {
	httplib::Client cli("http://localhost:8888");
	cli.set_keep_alive(true);

	bool is_login = false;
	string id = "-1";
	string token = "";

	while(true) {
        string func;
        
        if(cli.Get("/start_mark")->body == "1"){
        	string turn = cli.Get("/turn")->body;
            cout<<"nobat shomare: "<< turn <<endl;
            cout<<(cli.Get("/show")->body)<<endl;
            if (turn!=id) {
            	sleep(1);
            	system("clear");
            	continue;
            }
        }

        cin>> func;
        if(func == "login"){
        	if (is_login) {
        		cout << "shoma login hastid" << endl;
        		continue;
        	}
            string res = cli.Post("/login")->body;
            id = res.substr(0, res.find(":"));
            token = res.substr(res.find(":") + 1);
            is_login = true;
            cout << "done " << id << endl;
        } 
        if(func == "start"){
        	if (!is_login) {
        		cout<<"lotfan vared shavid"<<endl;
        		continue;
        	}
            cout << (cli.Post("/start")->body) << endl;
        }
        if (func == "show"){
        	if (!is_login) {
        		cout<<"lotfan vared shavid"<<endl;
        		continue;
        	}
        	cout << (cli.Get("/show")->body) << endl;
        }
        if(func == "move"){
        	if (!is_login) {
        		cout<<"lotfan vared shavid"<<endl;
        		continue;
        	}
        	string s;
        	cin >> s;
            cout << (cli.Post("/move", token + " " + s, "text/plain")->body) << endl;
        }
        if(func == "wall"){
        	if (!is_login) {
        		cout<<"lotfan vared shavid"<<endl;
        		continue;
        	}
        	string x, y, d;
        	cin >> x >> y >> d;
            cout << (cli.Post("/wall", token + " " + x + " " + y + " " + d, "text/plain")->body) << endl;
        }
    }
}
