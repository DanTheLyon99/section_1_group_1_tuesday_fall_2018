#ifndef GAMEHEADER
#define GAMEHEADER
#include <stdbool.h>
#include <time.h>

time_t timeStart,timeNow;

int initialOpen;

int flags,questions,moves;
double timePassed;
bool isIdle;
int boom;


struct DETONATIONS {
    int row;
    int col;
}detonations[4];
enum State{
    playing,won,lost
}gameState;

void printTitleAscii(); 
void printWonAscii();   
void printLostAscii();  
bool inRange(int maximum, int input); 
bool validAction(char input); 
void clearScreen(void); 
void* idleTimer(void *para); 
void checkWin(); 
void openEmptyCell(int row, int col); 
void openCell(int row, int col); 
void flagCell(int row, int col); 
void questionCell(int row, int col); 
void unmarkCell(int row, int col); 
void win (); 
void lose(); 
void play(double,int); 
void Game(); 
void save(); 
void load(); 
void textColor(char * ForeColor, char* BackColor); 

#endif
