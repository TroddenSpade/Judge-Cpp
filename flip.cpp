#define row 8
#define column 8

///////////////////////////////////////////////////////////////////////////
/////////////////////// Valid Moves Function //////////////////////////////
int abs(int num){
    return num>=0 ? num : -num;
}

int isInTable(int x,int y){
    if(x < 8 && x>=0 && y<8 && y>=0)    return 1;
    else    return 0;
}

int validNorth(int x0,int y0 ,int x ,int y, const int table[row][column],int player){    ////
    y-=1;
    if(!isInTable(x,y))  return -1;

    if(table[y][x]== 0) return -1;
    else if(table[y][x]== player){
        if (abs(x-x0)==1 || abs(y-y0)==1 )    return -1;
        else    return x0+y0*8;
    }
    else    return  validNorth(x0,y0,x,y,table,player);
}

int validSouth(int x0,int y0 ,int x ,int y, const int table[row][column],int player){    ////
    y+=1;
    if(!isInTable(x,y))  return -1;

    if(table[y][x]== 0) return -1;
    else if(table[y][x]== player){
        if (abs(x-x0)==1 || abs(y-y0)==1 )    return -1;
        else    return x0+y0*8;
    }
    else    return  validSouth(x0,y0,x,y,table,player);
}

int validWest(int x0,int y0 ,int x ,int y, const int table[row][column],int player){     ////
    x-=1;
    if(!isInTable(x,y))  return -1;

    if(table[y][x]== 0) return -1;
    else if(table[y][x]== player){
        if (abs(x-x0)==1 || abs(y-y0)==1 )    return -1;
        else    return x0+y0*8;
    }
    else    return  validWest(x0,y0,x,y,table,player);
}

int validEast(int x0,int y0 ,int x ,int y, const int table[row][column],int player){     ////
    x+=1;
    if(!isInTable(x,y))  return -1;

    if(table[y][x]== 0) return -1;
    else if(table[y][x]== player){
        if (abs(x-x0)==1 || abs(y-y0)==1 )    return -1;
        else    return x0+y0*8;
    }
    else    return  validEast(x0,y0,x,y,table,player);
}

int validNW(int x0,int y0 ,int x ,int y, const int table[row][column],int player){       ////
    y-=1;   x-=1;
    if(!isInTable(x,y))  return -1;

    if(table[y][x]== 0) return -1;
    else if(table[y][x]== player){
        if (abs(x-x0)==1 || abs(y-y0)==1 )    return -1;
        else    return x0+y0*8;
    }
    else    return  validNW(x0,y0,x,y,table,player);
}

int validNE(int x0,int y0 ,int x ,int y, const int table[row][column],int player){
    y-=1;   x+=1;
    if(!isInTable(x,y))  return -1;

    if(table[y][x]== 0) return -1;
    else if(table[y][x]== player){
        if (abs(x-x0)==1 || abs(y-y0)==1 )    return -1;
        else    return x0+y0*8;
    }
    else    return  validNE(x0,y0,x,y,table,player);
}

int validSW(int x0,int y0 ,int x ,int y, const int table[row][column],int player){
    y+=1;   x-=1;
    if(!isInTable(x,y))  return -1;

    if(table[y][x]== 0) return -1;
    else if(table[y][x]== player){
        if (abs(x-x0)==1 || abs(y-y0)==1 )    return -1;
        else    return x0+y0*8;
    }
    else    return  validSW(x0,y0,x,y,table,player);
}

int validSE(int x0,int y0 ,int x ,int y, const int table[row][column],int player){
    y+=1;   x+=1;
    if(!isInTable(x,y))  return -1;

    if(table[y][x]== 0) return -1;
    else if(table[y][x]== player){
        if (abs(x-x0)==1 || abs(y-y0)==1 )    return -1;
        else    return x0+y0*8;
    }
    else    return  validSE(x0,y0,x,y,table,player);
}

///////////////////////////////   Flip    //////////////////////////////////////

int flipNorth(int x ,int y, int table[row][column],int player){    ////
    if (validNorth(x,y,x,y,table,player)== -1)  return 0;
    table[y][x] =player;
    y-=1;
    while(table[y][x] == 3 - player){
        table[y][x]= player;
        y-=1;
    }
    return 1;
}

int flipSouth(int x ,int y, int table[row][column],int player){    ////
    if (validSouth(x,y,x,y,table,player)== -1)  return 0;
    table[y][x] =player;
    y+=1;
    while(table[y][x] == 3 - player){
        table[y][x]= player;
        y+=1;
    }
    return 1;
}

int flipWest(int x ,int y, int table[row][column],int player){     ////
    if (validWest(x,y,x,y,table,player)== -1)  return 0;
    table[y][x] = player;
    x-=1;
    while(table[y][x] == 3 - player){
        table[y][x]= player;
        x-=1;
    }
    return 1;
}

int flipEast(int x ,int y, int table[row][column],int player){     ////
    if (validEast(x,y,x,y,table,player)== -1)  return 0;
    table[y][x] = player;
    x+=1;
    while(table[y][x] == 3 - player){
        table[y][x]=player;
        x+=1;
    }
    return 1;
}

int flipNW(int x ,int y, int table[row][column],int player){       ////
    if (validNW(x,y,x,y,table,player)== -1)  return 0;
    table[y][x] = player;
    y-=1;   x-=1;
    while(table[y][x] == 3 - player){
        table[y][x]= player;
        y-=1;   x-=1;
    }
    return 1;
}

int flipNE(int x ,int y, int table[row][column],int player){
    if (validNE(x,y,x,y,table,player)== -1)  return 0;
    table[y][x] = player;
    y-=1;   x+=1;
    while(table[y][x] == 3 - player){
        table[y][x]= player;
        y-=1;   x+=1;
    }
    return 1;
}

int flipSW(int x ,int y, int table[row][column],int player){
    if (validSW(x,y,x,y,table,player)== -1)  return 0;
    table[y][x] = player;
    y+=1;   x-=1;
    while(table[y][x] == 3 - player){
        table[y][x]= player;
        y+=1;   x-=1;
    }
    return 1;
}

int flipSE(int x ,int y, int table[row][column],int player){
    if (validSE(x,y,x,y,table,player)== -1)  return 0;
    table[y][x] = player;
    y+=1;   x+=1;
    while(table[y][x] == 3 - player){
        table[y][x]= player;
        y+=1;   x+=1;
    }
    return 1;
}

int doFlip(int x ,int y, int table[row][column],int player){
    int result = 1;
    result *=flipNorth(x ,y,table,player);
    result *=flipSouth(x ,y,table,player);
    result *=flipEast(x ,y,table,player);
    result *=flipWest(x ,y,table,player);
    result *=flipNE(x ,y,table,player);
    result *=flipNW(x ,y,table,player);
    result *=flipSE(x ,y,table,player);
    result *=flipSW(x ,y,table,player);
    return result;
}