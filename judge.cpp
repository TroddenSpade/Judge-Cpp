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

void boardToArgv(int board[][10],string str[]){
    for(int i=1;i<9;i++){
        int array[8];
        for(int j=1;j<9;j++){
        array[j-1]=board[i][j];
        }
        str[i-1]=intArrayToString(array,8);
    }
}

string play(string black,string white,int board[][column],int turn){
    
}

void printTable(int table[row][column]){
    cout<<"   ";
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


int main(){
    const string Team[]={
        "./fitgirl",
        "./othello"
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

    // play(Team[1],Team[2],board,turn);

    return 0;
}