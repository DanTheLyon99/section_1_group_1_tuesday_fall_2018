#ifndef CELLSHEADER
#define CELLSHEADER

int r,c,mines; 

struct Cell{
    int discovered;
    int mined;
    int number;
    int flagged;
    int question;
    char show;
}grid[30][30];

void getSize(); 
void gridInit(); 
void draw(); 
void putBlank(int row, int col); 
void putMines(); 
void putNumbers(); 
void colorPrintChar(char c); 
#endif
