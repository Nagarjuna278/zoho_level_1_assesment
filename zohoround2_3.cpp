#include<bits/stdc++.h>
using namespace std;
int ballx,bally;
int count1;
int ball_count;
int dir=1;
void display(vector<vector<string>> &vec){
    for(auto i:vec){
        for(auto j:i){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}
void destroyrow(vector<vector<string>> &vec,int row){
    int n=vec.size();
    for(int i=1;i<n-1;i++){
        if(vec[row][i]!=" "){
            count1--;
            vec[row][i]=" ";
        }
    }
}
void destroyneighbours(vector<vector<string>> &vec,int row,int col){
    int n=vec.size();
    for(int i=row-1;i<=row+1;i++){
        for(int j=col-1;j<=col+1;j++){
            if(vec[i][j]!=" "){
                if(i>0 && i<n-1 && j<n-1 && j>0){
                    count1--;
                    vec[i][j]=" ";
                }
            }
            
        }
    }
}
int caldigit(vector<vector<string>> &vec,int i,int j){
    int number;
    string s=" ";
    if(vec[i][j]=="1"){
        vec[i][j]=s;
        return 1;
    }
    number=stoi(vec[i][j]);
    vec[i][j]=to_string(number-1);
    return 0;
}
void firstrow(vector<vector<string>> &vec,string s,int i){
    int n=vec.size();
    if(s=="L"){
        int j;
        for(j=n-2;j>0;j--){
            if(vec[i][j]=="DE"){
                destroyrow(vec,i);
                bally=j;
                break;
            }
            else if(vec[i][j]=="DS"){
                vec[i][j]=" ";
                count1--;
                destroyneighbours(vec,i,j);
                bally=j;
                break;
            }
            else if(vec[i][j]=="B"){
                vec[i][j]=" ";
                count1--;
                vec[ballx][bally+dir]="_";
                dir=dir*-1;
                bally=j;
                break;
            }
            else if(vec[i][j]!=" "){
                count1-=(caldigit(vec,i,j));
                bally=j;
                break;
            }
        }
        if(j==0){
            bally=n/2;
        }
    }
    else{
        int j;
        for(int j=1;j<n-1;j++){
            if(vec[i][j]=="DE"){
                destroyrow(vec,i);
                bally=j;
                break;
            }
            else if(vec[i][j]=="DS"){
                vec[i][j]=" ";
                count1--;
                bally=j;
                destroyneighbours(vec,i,j);
                break;
            }
            else if(vec[i][j]=="B"){
                vec[i][j]==" ";
                count1--;
                bally=j;
                vec[ballx][bally+dir]="_";
                dir=dir*-1;
                break;
            }
            else if(vec[i][j]!=" "){
                count1-=(caldigit(vec,i,j));
                bally=j;
                break;
            }
        }
        if(j==n-1){
            bally=n/2;
        }
    }
}
void traverse(vector<vector<string>> &vec,string s){
    int temp_count=count1;
    int n=vec.size();
    if(s=="ST"){
        for(int i=ballx-1,j=bally;i>=0;i--){
            if(vec[i][j]=="DE"){
                destroyrow(vec,i);
                break;
            }
            else if(vec[i][j]=="DS"){
                vec[i][j]=" ";
                count1--;
                destroyneighbours(vec,i,j);
                break;
            }
            else if(vec[i][j]=="B"){
                vec[i][j]=" ";
                count1--;
                vec[ballx][bally+dir]="_";
                dir=dir*-1;
                break;
            }
            else if(vec[i][j]!=" "){
                count1-=(caldigit(vec,i,j));
                break;
            }
        }
    }
    else if(s=="RD"){
        int i,j;
        vec[ballx][bally]="_";
        for(i=ballx-1,j=bally+1;j<n-1;j++,i--){
            if(vec[i][j]=="DE"){
                destroyrow(vec,i);
                bally=j;
                break;
            }
            else if(vec[i][j]=="DS"){
                vec[i][j]=" ";
                count1--;
                destroyneighbours(vec,i,j);
                bally=j;
                break;
            }
            else if(vec[i][j]=="B"){
                vec[i][j]=" ";
                count1--;
                bally=j;
                vec[ballx][bally+dir]="_";
                dir=dir*-1;
                break;
            }
            else if(vec[i][j]!=" "){
                count1-=(caldigit(vec,i,j));
                bally=j;
                break;
            }
        }
        if(j==n-1){
            firstrow(vec,"L",i);
        }
    }
    else if(s=="LD"){
        int i,j;
        for(i=ballx-1,j=bally-1;j>0;j--,i--){
            if(vec[i][j]=="DE"){
                destroyrow(vec,i);
                bally=j;
                break;
            }
            else if(vec[i][j]=="DS"){
                vec[i][j]=" ";
                count1--;
                destroyneighbours(vec,i,j);
                bally=j;
                break;
            }
            else if(vec[i][j]=="B"){
                vec[i][j]==" ";
                count1--;
                bally=j;
                vec[ballx][bally+dir]="_";
                dir=dir*-1;
                break;
            }
            else if(vec[i][j]!=" "){
                count1-=caldigit(vec,i,j);
                bally=j;
                break;
            }
        }
        if(j==0){
            firstrow(vec,"R",i);
        }
    }
    if(count1==temp_count && vec[ballx][bally]=="_"){
        ball_count--;
    }
    if(vec[ballx][bally]=="G"){
        ball_count--;
        for(int p=1;p<n-1;p++){
            vec[ballx][p]="G";
        }
        vec[ballx][bally]="o";
    }
    else if(vec[ballx][bally]=="_"){
        vec[ballx][bally]="o";
    }
}

int main(){
    int n;
    cout<<"Enter the size of the NxN matrix : ";
    cin>>n;
    vector<vector<string>> vec(n);
    string temp=" ";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(j==0 || j==n-1 || i==0){
                vec[i].push_back("W");
            }
            else if(i==n-1){
                vec[i].push_back("G");
            }
            else{
                vec[i].push_back(temp);
            }
        }
    }
    vec[n-1][(n/2)]="o";
    ballx=n-1;
    bally=n/2;
    int x,y;
    string s;
    count1=0;
    char c='Y';
    while(c=='Y'){
        cout<<"Enter the brick's position and the brick type: ";
        cin>>x>>y>>s;
        vec[x][y]=s;
        count1++;
        cout<<"Do you want to continue(Y or N)?";
        cin>>c;
    }
    cout<<"Enter the ball count : ";
    cin>>ball_count;
    display(vec);
    
    while(ball_count>0 && count1>0){
        cout<<"Ball count is "<<ball_count<<endl;
        cout<<"Enter the direction in which the ball need to traverse : ";
        string tra;
        cin>>tra;
        traverse(vec,tra);
        display(vec);
    }
    if(count1==0){
        cout<<"you win HURRAY..!!"<<endl;
    }
    else{
        cout<<"you lose GAME OVER..!!"<<endl;
    }
}