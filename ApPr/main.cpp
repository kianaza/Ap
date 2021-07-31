#include<bits/stdc++.h>
using namespace std;
const int Maxn=13;
int player_mark[Maxn][Maxn],player_cnt= 1;
int wall_mark[Maxn][Maxn];
bool start_mark;
int turn = 0;

struct Player {
    int x, y, cnt;
    string name;
    Player(int _x = 0, int _y = 0, int _cnt = 0, string _name = ""): x(_x), y(_y), cnt(_cnt), name(_name) {
        player_mark[_x][_y]=cnt;
        cout<<"Mohre shomareye "<< cnt <<" afzoode shod"<<endl;
    }

    bool move_up(){
        if(x == 0){
            return false;
        }
        player_mark[x][y]=0;
        x--;
        player_mark[x][y]=cnt;
        return true;
    }
    bool move_left(){
        if(y == 0){
            return false;
        }
        player_mark[x][y]=0;
        y--;
        player_mark[x][y]=cnt;
        return true;
    }
    bool move_right(){
        if(y == 10){
            return false;
        }
        player_mark[x][y]=0;
        y++;
        player_mark[x][y]=cnt;
        return true;
    }
    bool move_down(){
        if(x == 10){
            return false;
        }
        player_mark[x][y]=0;
        x++;
        player_mark[x][y]=cnt;
        return true;
    }
};
vector <Player*> players;
void login(){
    
    if(player_cnt > 4){
        cout<<"Zarfiat bazi takmil ast."<<endl;
        return;
    }
    if(start_mark){
        cout<<"Bazi shoro shode ast"<<endl;
        return;
    }
    string name;
    cin>>name;
    if(player_cnt == 1){
        players.push_back(new Player(0,0,1,name));
        player_cnt++;
    }
    else if(player_cnt == 2){
        players.push_back(new Player(10,10,2,name));
        player_cnt++;
    }
    else if(player_cnt == 3){
        players.push_back(new Player(0,10,3,name));
        player_cnt++;
    }
    else if(player_cnt == 4){
        players.push_back(new Player(10,0,4,name));
        player_cnt++;
    }
}
void start(){
    start_mark=true;
}
void move(){
    if(!start_mark){
        cout<<"Bazi shoro nashode ast.";
        return;
    }
    bool valid=true;
    int p;
    string s;
    cin>>s>>p;
    if(p != turn+1 ){
        cout<<"Nobat shoma nist.";
        return;
    }
    if(s == "up")
        valid= valid & players[p-1]->move_up();
    
    if(s == "down")
        valid= valid & players[p-1]->move_down();
    
    if(s == "left")
        valid= valid & players[p-1]->move_left();
    
    if(s == "right")
        valid= valid & players[p-1]->move_right();
    if(valid)
        turn= (turn+1) % player_cnt ;
    else
        cout<<"harekat valid nemibashad"; 
}
void show(){
    for(int i=0;i<11;i++){
        for(int j=0;j<11;j++){
            cout<<player_mark[i][j]<<" ";
            if(vertical_wall[i][j])
                cout<<"|";
            else
                cout<<"  "
            cout<<" ";
        }
        cout<<endl;
        for(int j=0;j<11;j++){
            cout<<"-"<<"   ";
        }
        cout<<endl;
    }
}
int main(){
    while(true){
        string func;
        
        if(start_mark){
            cout<<"nobat shomare: "<<turn+1<<endl;
        }

        cin>> func;
        if(func == "login"){
            login();
        } 
        if(func == "start"){
            start();
        }
        if(func == "move"){
            move();
        }
        show();
    }
}