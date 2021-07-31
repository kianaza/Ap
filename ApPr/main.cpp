#include<bits/stdc++.h>
using namespace std;
const int Maxn=13;
int player_mark[Maxn][Maxn],player_cnt= 1;
int wall_mark[Maxn][Maxn];
bool start_mark;
int turn = 0;
bool vertical_wall[Maxn][Maxn],horizontal_wall[Maxn][Maxn];
struct Player {
    int x, y, cnt;
    Player(int _x = 0, int _y = 0, int _cnt = 0): x(_x), y(_y), cnt(_cnt) {
        player_mark[_x][_y]=cnt;
        cout<<"Mohre shomareye "<< cnt <<" afzoode shod"<<endl;
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
};
vector <Player*> players;
void show(){
    cout<<"   ";
    for(int i=0;i<10;i++){
        cout<<"  "<<i<<" ";
    }
    cout<<"\n"<<"\n";
    for(int i=0;i<11;i++){
        cout<<"   ";
        for(int j=0;j<11;j++){
            cout<<player_mark[i][j]<<" ";
            if(vertical_wall[i][j])
                cout<<"|";
            else
                cout<<" ";
            cout<<" ";
        }
        cout<<"\n";
        if(i!=10) cout<<i<<"  ";
        for(int j=0;j<10;j++){
            if(horizontal_wall[i][j])
                cout<<"-";
            else
                cout<<" ";
            cout<<"   ";
        }
        cout<<"\n";
    }
}
void login(){
    
    if(player_cnt > 4){
        cout<<"Zarfiat bazi takmil ast."<<endl;
        return;
    }
    if(start_mark){
        cout<<"Bazi shoro shode ast"<<endl;
        return;
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
}
void start(){
    start_mark=true;
    show();
}
void move(){
    if(!start_mark){
        cout<<"Bazi shoro nashode ast."<<endl;
        return;
    }
    bool valid=true;
    int p;
    string s;
    cin>>s>>p;
    if(p != turn+1 ){
        cout<<"Nobat shoma nist."<<endl;
        return;
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
    if(valid)
        turn= (turn+1) % (player_cnt-1),show() ;
    else
        cout<<"harekat valid nemibashad"<<endl; 
}
void wall(){
    if(!start_mark){
        cout<<"Bazi shoro nashode ast"<<endl;
        return;
    }
    int x,y,p;
    string d;
    bool valid =true;
    cin>>x >>y >>d >>p ;
    if(p!=turn +1){
        cout<<"nobat shoma neminashad";
        return;
    }
    if(d == "h"){
        if(x<0 || y<0 || x>9 || y>9 || horizontal_wall[x][y] || horizontal_wall[x][y+1])
            cout<<"harekat valid nist",valid=false;
        else
            horizontal_wall[x][y]=true,
            horizontal_wall[x][y+1]=true;
    }
    else if(d == "v"){
        if(x<0 || y<0 || x>9 || y>9 || vertical_wall[x][y] || vertical_wall[x+1][y])
            cout<<"harekat valid nist",valid=false;
        else
            vertical_wall[x][y]=true,
            vertical_wall[x+1][y]=true;
    }
    else 
        cout<<"harekat valid nist",valid=false;
    
    if(valid)
        turn= (turn+1) % (player_cnt-1),show();
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
        if(func == "wall"){
            wall();
        }
    }
}