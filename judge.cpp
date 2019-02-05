#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cstring>

#include "flip.cpp"

using namespace std;

string intArrayToString(int int_array[], int size_of_array) {
  string returnstring = "";
  for (int temp = 0; temp < size_of_array; temp++)
    returnstring += int_array[temp]+'0';
  return returnstring;
}

string exec(string str) {
    char cmd[str.size() + 1];
	strcpy(cmd, str.c_str());	
    char buffer[128];
    string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

string boardToArgv(int board[][column]){
    string str[column];
    for(int i=0;i<row;i++){
        int array[column];
        for(int j=0;j<8;j++){
        array[j]=board[i][j];
        }
        str[i]=intArrayToString(array,column);
    }
    string argv = " ";
    for(int i =0;i<8;i++){
        argv+= str[i];
        argv+=" ";
    }
    return argv;
}

void printBoard(int table[row][column]){
    cout<<"  ";
    for(int i=0;i<column;i++)   cout<<i<<" ";
    cout<< std::endl;
    for(int i=0;i<row;i++){
        cout<<i<<" ";
        for(int j=0;j<column;j++){
            cout<<table[i][j]<<" ";
        }
        cout<< std::endl;
    }

}

int copyBoard(const int board1[row][column],int board2[row][column]){
    for(int i=0;i<column;i++){
        for(int j=0;j<row;j++){
            board2[i][j]=board1[i][j];
        }
    }
}

int winner(const int board[row][column]){
    int p1=0;
    int p2=0;
    for(int i=0;i<column;i++){
        for(int j=0;j<row;j++){
            if(board[i][j]==1)  p1++;
            if(board[i][j]==2)  p2++;
        }
    }
    if(p1>p2)   return 1;
    if(p1==p2)  return 0;
    if(p2>p1)   return 2;
}

void play(string black,string white,int board[][column],int player,int *result){
    
    string argv = boardToArgv(board);

    if(player == 1)
        argv = black + argv + "1";
    else
        argv = white + argv + "2";

    string value = exec(argv);

    int x = value[0] - 48;
    int y = value[2] - 48;
    if(doFlip(x,y,board,player) && isInTable(x,y)){
        cout<<"-Player: "<<player<<"  -Move :"<<x<<","<<y<<endl ;
        *result = 0;
        
    }else{
        cout<< "Player: "<<player<<" Cant Move/Invalid Move !: "<<x<<","<<y<<endl;
        *result+=1;
    }
    printBoard(board);
    cout<<"-----------------------"<<endl;
}

void game(string black,string white,int board1[][column]){
    int result = 0;
    int count =0;
    int board[row][column];
    copyBoard(board1,board);
    while(1){
        play(black,white,board,count%2+1,&result);
        if(result == 2) break;
        count ++;
    }
    cout << "Finish Player : "<<winner(board)<<" Won!";
}

int main(){
    const string Team[]={
        "./mohammad",
        "./parsa"
    };
    int board[8][8]={
        {0, 0 ,0 ,0 ,0 ,0 ,0 ,0},

        {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0},

        {0, 0 ,0 ,0 ,0 ,0 ,0 ,0},

        {0 ,0 ,0 ,2 ,1 ,0 ,0 ,0},

        {0 ,0 ,0 ,1 ,2 ,0 ,0 ,0},

        {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0},

        {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0},

        {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}        
    };
    
    game(Team[0],Team[1],board);
    getchar();
    game(Team[1],Team[0],board);

    return 0;
}