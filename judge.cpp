#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cstring>

#include "flip.cpp"

#define NoTeams 3

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

void printBoardToFile(const int board[row][column],FILE *fptr){
    fprintf(fptr,"%s","   0 1 2 3 4 5 6 7\n");
    string str[column];
    for(int i=0;i<row;i++){
        fprintf(fptr,"%d",i);
        fprintf(fptr,"%s"," :");
        for(int j=0;j<8;j++){
            fprintf(fptr,"%d",board[i][j]);
            fprintf(fptr,"%s"," ");
        }
        // str[i]="i :"+intArrayToString(array,column)+"\n";
        // char stri[str[i].size() + 1];
	    // strcpy(stri, str[i].c_str());
        fprintf(fptr,"%s","\n");
    }
}


void play(string black,string white,int board[][column],int player,int *result){
    
    string argv = boardToArgv(board);

    if(player == 1)
        argv ="./codes/" + black + argv + "1";
    else
        argv ="./codes/" + white + argv + "2";

    string value = exec(argv);

    int x = value[0] - 48;
    int y = value[2] - 48;

    FILE *fptr;
    string name ="./logs/" + black + " - " + white+".txt";
    char nameChar[name.size() + 1];
	strcpy(nameChar, name.c_str());
    fptr = fopen(nameChar,"a");
    if(doFlip(x,y,board,player) && isInTable(x,y)){
        string str;
        string xStr = to_string(x);
        string yStr = to_string(y);
        string playerStr = to_string(player);
        str = "-Player: "+playerStr+"  -Move :"+xStr+","+yStr+"\n";
        char stri[str.size() + 1];
	    strcpy(stri, str.c_str());
        fprintf(fptr,"%s",stri);
        
        // cout<<"-Player: "<<player<<"  -Move :"<<x<<","<<y<<endl ;
        *result = 0;
        
    }else{
        string str;
        string xStr = to_string(x);
        string yStr = to_string(y);
        string playerStr = to_string(player);
        str = "-Player: "+playerStr+" Cant Move/Invalid Move !: "+xStr+","+yStr+"\n";
        char stri[str.size() + 1];
	    strcpy(stri, str.c_str());
        fprintf(fptr,"%s",stri);

        // cout<< "-Player: "<<player<<" Cant Move/Invalid Move !: "<<x<<","<<y<<endl;
        *result+=1;
    }
    printBoardToFile(board,fptr);
    // printBoard(board);
    fprintf(fptr,"%s","-----------------------\n");
    // cout<<"-----------------------"<<endl;
    fclose(fptr);
}

int game(string black,string white,int board1[][column]){
    int result = 0;
    int count =0;
    int board[row][column];
    copyBoard(board1,board);

    FILE *fgame;
    fgame=fopen("games.txt","a");

    while(1){
        play(black,white,board,count%2+1,&result);
        if(result == 2) break;
        count ++;
    }

    if(winner(board)==1){
        string str = black + " > " + white+"\n";
        char stri[str.size() + 1];
	    strcpy(stri, str.c_str());
        fprintf(fgame,"%s",stri);

        cout << black << " > " << white;
        return 1;
    }else if(winner(board)==2){
        string str = black + " > " + white+"\n";
        char stri[str.size() + 1];
	    strcpy(stri, str.c_str());
        fprintf(fgame,"%s",stri);

        cout << black << " < " << white;
        return 2;
    }else if(winner(board)==0){
        string str = black + " > " + white+"\n";
        char stri[str.size() + 1];
	    strcpy(stri, str.c_str());
        fprintf(fgame,"%s",stri);

        cout << black << " = " << white;
        return 0;
    }
    fclose(fgame);
}

int main(){
    const string Team[]={
        "Force",
        "LQ",
        // "iran16",
        // "Magic_world",
        // "SSDEBF",
        // "MONOLITH",
        // "Loser",
        // "NumOne01",
        // "flipper_the_dolphin",
        // "Oftaadegaan",
        // "shift",
        "Boro_dame_khoontoon_bazi_kon",
        // "EH"
    };
    int table[NoTeams][3]={0};

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
    int result;
    for(int i =0;i<NoTeams;i++){
        for(int j=i+1;j<NoTeams;j++){
            result = game(Team[i],Team[j],board);
            if(result==1){
                table[i][0]++;
                table[j][2]++;
            }else if(result==2){
                table[j][0]++;
                table[i][2]++;
            }else if(result==0){
                table[j][1]++;
                table[i][1]++;
            }
            getchar();
            result = game(Team[j],Team[i],board);
            if(result==1){
                table[j][0]++;
                table[i][2]++;
            }else if(result==2){
                table[i][0]++;
                table[j][2]++;
            }else if(result==0){
                table[j][1]++;
                table[i][1]++;
            }
            getchar();
        }
    }
    
    FILE *fscore;
    fscore = fopen("score.txt","a");
    fprintf(fscore,"%s","Teams");
    fprintf(fscore,"%s","\t\t\t\t");
    fprintf(fscore,"%s\t%s\t%s\n","Wins","draws","Loses");
    for(int i=0;i<NoTeams;i++){
        char stri[Team[i].size() + 1];
	    strcpy(stri, Team[i].c_str());
        fprintf(fscore,"%s",stri);
        fprintf(fscore,"%s","\t\t\t\t");
        fprintf(fscore,"%d\t%d\t%d\n",table[i][0],table[i][1],table[i][2]);
    }

    fclose(fscore);

    return 0;
}