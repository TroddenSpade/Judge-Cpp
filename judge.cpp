#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cstring>

using namespace std;

string int_array_to_string(int int_array[], int size_of_array) {
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
        str[i-1]=int_array_to_string(array,8);
    }
}



int main(){

    int board[10][10]={
        {0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },

        {0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },

        {0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },

        {0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },

        {0, 0 ,0 ,0 ,1 ,2 ,0 ,0 ,0 ,0 },

        {0, 0 ,0 ,0 ,1 ,2 ,0 ,0 ,0 ,0 },

        {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },

        {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },

        {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 },
        
        {0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}
    };

    string str[8];
    boardToArgv(board,str);

    cout << str[4];
    
}