// server.cpp

#include<iostream>
#include<sstream>
#include<map>

#include "httplib.h"

using namespace std;

const int Maxn=13;

map<int, int>tokens;

int player_mark[Maxn][Maxn],player_cnt= 1;
int wall_mark[Maxn][Maxn];
bool start_mark,winner_mark,winner_mark_show;
int turn = 0;
bool vertical_wall[Maxn][Maxn],horizontal_wall[Maxn][Maxn];

struct Player {
    int x, y, cnt;
    Player(int _x = 0, int _y = 0, int _cnt = 0): x(_x), y(_y), cnt(_cnt) {
        player_mark[_x][_y]=cnt;
    }

    bool move_up(){
        if(x == 0 || horizontal_wall[x-1][y]){
            return false;
        }
        player_mark[x][y]=0;
        x--;
        player_mark[x][y]=cnt;
        return true;
    }
    bool move_left(){
        if(y == 0 || vertical_wall[x][y-1]){
            return false;
        }
        player_mark[x][y]=0;
        y--;
        player_mark[x][y]=cnt;
        return true;
    }
    bool move_right(){
        if(y == 10 || vertical_wall[x][y]){
            return false;
        }
        player_mark[x][y]=0;
        y++;
        player_mark[x][y]=cnt;
        return true;
    }
    bool move_down(){
        if(x == 10 || horizontal_wall[x][y]){
            return false;
        }
        player_mark[x][y]=0;
        x++;
        player_mark[x][y]=cnt;
        return true;
    }
    bool win(){
        if(x==5 && y==5)
            return true;
        return false;
    }
};

vector <Player*> players;

// done
string show(){
    stringstream output;
    if(winner_mark_show){
        output<<"!!! Bazi be payan resid !!!";
        return output.str();
    }
    if(winner_mark)
        winner_mark_show=true;
    output<<"   ";
    for(int i=0;i<10;i++){
        output<<"  "<<i<<" ";
    }
    output<<"\n"<<"\n";
    for(int i=0;i<11;i++){
        output<<"   ";
        for(int j=0;j<11;j++){
            output<<player_mark[i][j]<<" ";
            if(vertical_wall[i][j])
                output<<"|";
            else
                output<<" ";
            output<<" ";
        }
        output<<"\n";
        if(i!=10) output<<i<<"  ";
        for(int j=0;j<11;j++){
            if(horizontal_wall[i][j])
                output<<"-";
            else
                output<<" ";
            output<<"   ";
        }
        output<<"\n";
    }

    return output.str();
}

// done
string login(){
    stringstream output;

    if(player_cnt > 4){
        output<<"Zarfiat bazi takmil ast."<<"\n";
        return output.str();
    }
    if(start_mark){
        output<<"Bazi shoro shode ast"<<"\n";
        return output.str();
    }

    if(player_cnt == 1){
        players.push_back(new Player(0,0,1));
        player_cnt++;
    }
    else if(player_cnt == 2){
        players.push_back(new Player(10,10,2));
        player_cnt++;
    }
    else if(player_cnt == 3){
        players.push_back(new Player(0,10,3));
        player_cnt++;
    }
    else if(player_cnt == 4){
        players.push_back(new Player(10,0,4));
        player_cnt++;
    }
    output << "+" << player_cnt-1 << "\n";
    return output.str();
}

// done
string start(){
    start_mark=true;
    return show();
}

// done
string move(string s, int p){
    stringstream output;
    if(!start_mark){
        output<<"Bazi shoro nashode ast."<<"\n";
        return output.str();
    }

    bool valid=true;
    
    if(p != turn+1 ){
        output<<"Nobat shoma nist."<<"\n";
        return output.str();
    }

    if(s == "up")
        valid= valid & players[p-1]->move_up();
    else if(s == "down")
        valid= valid & players[p-1]->move_down();
    
    else if(s == "left")
        valid= valid & players[p-1]->move_left();
    
    else if(s == "right")
        valid= valid & players[p-1]->move_right();
    else
        valid =false;
    if(winner_mark ||  players[p-1]->win()){
        output<<"!!! bazi be payan resid !!!"<<"\n";
        winner_mark=true;
        return output.str();
    }
    if(valid) {
        turn= (turn+1) % (player_cnt-1);
        return show();
    }
    else {
        output<<"harekat valid nemibashad"<<"\n"; 
        return output.str();
    }
}

// done
string wall(int x, int y, int p, string d){
    stringstream output;

    if(!start_mark){
        output<<"Bazi shoro nashode ast"<<"\n";
        return output.str();
    }

    bool valid =true;
    
    if(p!=turn +1){
        output<<"nobat shoma neminashad";
        return output.str();
    }
    if(d == "h"){
        if(x<0 || y<0 || x>9 || y>9 || horizontal_wall[x][y] || horizontal_wall[x][y+1])
            output<<"harekat valid nist",valid=false;
        else
            horizontal_wall[x][y]=true,
            horizontal_wall[x][y+1]=true;
    }
    else if(d == "v"){
        if(x<0 || y<0 || x>9 || y>9 || vertical_wall[x][y] || vertical_wall[x+1][y])
            output<<"harekat valid nist",valid=false;
        else
            vertical_wall[x][y]=true,
            vertical_wall[x+1][y]=true;
    }
    else 
        output<<"harekat valid nist",valid=false;
    if(winner_mark){
        output<<"harekat valid nemibashad"<<"\n";
        return output.str();
    }
    if(valid) {
        turn = (turn+1) % (player_cnt-1);
        return show();
    }
    else
        return output.str();
}





int main(){
    httplib::Server svr;

    svr.set_keep_alive_max_count(5);
    svr.set_keep_alive_timeout(3600);

    svr.Post("/login", [](const httplib::Request &req, httplib::Response &res) {
        string fnResponse = login();

        if (fnResponse[0] == '+') {
            fnResponse = fnResponse.substr(1);
            int p = stoi(fnResponse);
            int token = (rand() * rand() * 2973) * (rand() * rand());
            if(token<0) token = -token;
            tokens[token]=p;
            res.set_content(to_string(p) + ":" + to_string(token), "text/plain");
        } else {
            res.status = 400;
            res.set_content(fnResponse, "text/plain");
        }
    });

    svr.Post("/start", [](const httplib::Request &req, httplib::Response &res) {
        string fnResponse = start();
        res.set_content(fnResponse, "text/plain");
    });

    svr.Post("/wall", [](const httplib::Request &req, httplib::Response &res) {
        stringstream input(req.body);
        int x, y, p;
        string d, fnResponse;
        input >> p >> x >> y >> d;
        if(tokens.find(p) == tokens.end())
            fnResponse = "token shoma yaft nashod";
        else 
            fnResponse = wall(x, y, tokens[p], d);
        res.set_content(fnResponse, "text/plain");
    });

    svr.Post("/move", [](const httplib::Request &req, httplib::Response &res) {
        stringstream input(req.body);
        int p;
        string s,fnResponse;
        input >> p >> s;
        if(tokens.find(p) == tokens.end())
            fnResponse = "token shoma yaft nashod";
        else 
            fnResponse = move(s, tokens[p]);
        res.set_content(fnResponse, "text/plain");
    });

    svr.Get("/show", [](const httplib::Request &req, httplib::Response &res) {
        string fnResponse = show();
        res.set_content(fnResponse, "text/plain");
    });

    svr.Get("/turn", [](const httplib::Request &req, httplib::Response &res) {
        res.set_content(to_string(turn + 1), "text/plain");
    });

    svr.Get("/start_mark", [](const httplib::Request &req, httplib::Response &res) {
        string test = start_mark? "1":"0";
        res.set_content(test, "text/plain");
    });


    svr.set_exception_handler([](const auto& req, auto& res, std::exception &e) {
      res.status = 500;
      res.set_content(e.what(), "text/plain");
    });

    svr.listen("0.0.0.0", 8888);
}