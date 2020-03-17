#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <queue>
#include <map>
#include <fstream>
#include <string.h>
#include <math.h> 
#include <stdlib.h>

using namespace std;
typedef long long LL;
typedef long double LD;
 
#define inf 999999999999;
#define FOR(i,n,m) for(LL i = n; i < m; i++)
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define sz(x) (x).size()
#define all(v) (v).begin(),(v).end()
template<typename T> void PV(T v) {
	for(const auto e : v) cout<<e<<" "; cout<<endl;
}

using namespace std;

/*
 
      |     |
   0  |  1  |  2
 _ _ _|_ _ _|_ _ _
      |     |  
   3  |  4  |  5
 _ _ _|_ _ _|_ _ _ 
      |     |  
   6  |  7  |  8
      |     |


        X -> 1  (true)
        O -> -1 (false)
*/

int getInt(){
    int a;
    cin>>a;
    if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"  : ";
        return 0;
    }
}

void boxString(string text){
    int wb = text.size();
    wb += 6;
    cout<<"   ";
    FOR(i,0,wb+2) cout<<"_";
    cout<<endl<<"  |";
    FOR(i,0,wb+2) cout<<" ";
    cout<<"|"<<endl<<"  | ";
    FOR(i,0,wb/2-text.size()/2) cout<<" ";
    cout<<text;
    FOR(i,0,wb/2-text.size()/2) cout<<" ";
    cout<<" |"<<endl<<"  |";
    FOR(i,0,wb+2) cout<<"_";
    cout<<"|"<<endl;
}   

void startScreen(){
    system("CLS");
    boxString("Welcome to TicTacToe");
    cout<<endl;
    cout<<"  For 1p,  type 1"<<endl;
    cout<<"  For 2p,  type 2"<<endl;
    cout<<"  To quit, type -1"<<endl;
    cout<<endl<<"  : ";
}

void drawGrid(vector<int> grid){
    string r1 = "         |     |     \n";
    string r2 = "      %c  |  %c  |  %c  \n";
    string r3 = "    _ _ _|_ _ _|_ _ _\n";
    vector<char> c;
    for(auto v : grid){
        switch (v){
        case 1:
            c.pb('X');
            break;
        case -1:
            c.pb('O');
            break;
        
        default:
            c.pb(' ');
            break;
        }
    }
    printf((r1+r2+r3).data(),c[0],c[1],c[2]);
    printf((r1+r2+r3).data(),c[3],c[4],c[5]);
    printf((r1+r2+r1).data(),c[6],c[7],c[8]);
}

int win(vector<int> g){
    FOR(i,0,3) if(g[i] != 0) if(g[i]==g[i+3] && g[i]==g[i+6]) return g[i];
    FOR(i,0,3) if(g[i*3] != 0) if(g[i*3]==g[i*3+1] && g[i*3]==g[i*3+2]) return g[i*3];
    if(g[0] != 0) if(g[0]==g[4] && g[0]==g[8]) return g[0];
    if(g[2] != 0) if(g[2]==g[4] && g[2]==g[6]) return g[2];
    return 0;
}

bool tie(vector<int> g){
    FOR(i,0,9)if(!g[i]) return false;
    if(win(g)) return false;
    return true;
}

int takeInput(){
    int r, c;
    cout<<"   Row: ";
    r = getInt();
    cout<<"   Collum: ";
    c = getInt();
    r--; c--;
    return r*3+c;
}

void drawgame(vector<int> grid, int p){
    system("CLS");
    boxString(" TicTacToe ");
    cout<<endl<<endl;
    drawGrid(grid);
    cout<<endl<<"   "<<(p ? 'X' : 'O')<<" to move"<<endl;
}

bool validPlace(int i, vector<int> grid){
    if(i < 0 || i > 8) return false;
    if(grid[i]) return false;
    return true;
}

void endScreen(bool p, bool t){
    system("CLS");

    if(!t){
        if(p)boxString("X won the game");
        else boxString("O won the game");
    }else{
        boxString("It was a tie");
    }

    cout<<endl;
    cout<<"  To go again,  type 1"<<endl;
    cout<<"  To go to start screen,  type 2"<<endl;
    cout<<"  To quit, type -1"<<endl;
    cout<<endl<<"  : ";
}

int play2player(){
    vector<int> grid(9);
    bool p = true;
    while(!win(grid) && !tie(grid)){
        drawgame(grid,p);
        int pd;
        do{
            pd = takeInput();
        }while(validPlace(pd,grid) == false);
        grid[pd] = (p ? 1 : -1);
        p = !p;
    }
    int value;
    do{
        endScreen(!p, tie(grid));
        value = getInt();
    }while(value!=1 && value!=2 && value != -1);

    switch (value){
    case 1:
        return 2;
        break;
    case 2:
        return 0;
        break;
    case -1:
        return -1;
        break;
    }
    
}

int compMove2(int p, vector<int> grid){
    if(win(grid)) return win(grid);
    if(tie(grid)) return 0;
    
    int best = p ? -10 : 10;

    if(p){
        FOR(i,0,9) if(!grid[i]){
            grid[i] = p ? 1 : -1;
            auto pt = compMove2(!p,grid);
            grid[i] = 0;
            best = max(best,pt);
        }
    }else{
        FOR(i,0,9) if(!grid[i]){
            grid[i] = p ? 1 : -1;
            auto pt = compMove2(!p,grid);
            grid[i] = 0;
            best = min(best,pt);
        }
    }
    
    return best;
}

int compMove1(int c, vector<int> grid){
    //PV(grid);
    FOR(i,0,9) if(!grid[i]){
        grid[i] = c ? 1 : -1;
        //cout<<i<<" "<<compMove2(!c,grid)<<endl;
        grid[i] = 0;
    }
    FOR(i,0,9) if(!grid[i]){
        grid[i] = c ? 1 : -1;
        auto pt = compMove2(!c,grid);
        if(pt == 1 &&  c) return i;
        if(pt == -1 && !c) return i;
        grid[i] = 0;
    }
    //cout<<"hi boiz"<<endl;
    FOR(i,0,9) if(!grid[i]){
        grid[i] = c ? 1 : -1;
        if(compMove2(!c,grid) == 0) return i;
        grid[i] = 0;
    }
    FOR(i,0,9) if(!grid[i]) return i;
}

int play1player(){
    system("CLS");
    boxString("Do you want to start?");
    cout<<endl;
    cout<<"   Type 1 to start"<<endl;
    cout<<"   Type 2 otherwise"<<endl;
    cout<<endl;
    int value;
    vector<int> grid(9);
    bool p = true;
    bool c = false;
    do{
        cout<<"   : ";
        value = getInt();
    }while(value != 1 && value != 2);
    if(value == 2) c = true;
    
    // grid[0] = 1;
    // grid[1] = -1;
    // grid[2] = 1;
    // grid[3] = -1;

    while(!win(grid) && !tie(grid)){
        drawgame(grid,!c);
        if(p == c){
            auto pt = compMove1(c,grid);
            cout<<pt<<endl;
            grid[pt] = (p ? 1 : -1);
        }
        else{
            int pd;
            do{
                pd = takeInput();
            }while(validPlace(pd,grid) == false);
            grid[pd] = (p ? 1 : -1);
        }
        p = !p;
    }
    
    do{
        endScreen(!p, tie(grid));
        value = getInt();
    }while(value!=1 && value!=2 && value != -1);

    switch (value){
    case 1:
        return 1;
        break;
    case 2:
        return 0;
        break;
    case -1:
        return -1;
        break;
    }
}

int main(){
    int value, winner;
    do{
        startScreen();
        value = getInt();
    }while(value!=1 && value!=2 && value != -1 );
    do{
        if(value == 2){
            value = play2player();
        }else if(value == 1){
            value = play1player();
        }else if(value == 0){
            do{
                startScreen();
                value = getInt();
            }while(value!=1 && value!=2 && value != -1);
        }
        if(value != 1 && value != 2 && value != 0) value = -1;
    }while(value != -1);
}