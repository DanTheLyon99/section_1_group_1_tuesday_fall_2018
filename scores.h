#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED

struct Player{
    char name[33];
    int score;
}topPlayer[10];

void getScore(); 
void insertScore(char* playerName,int score,int i);
long getName (int); 
void saveTopPlayers(); 
void loadTopPlayers(); 
void displayLeaderboard(int); 
void clearLeaderboard(); 
void changeTextColor(char * ForeColor, char* BackColor); 
#endif // SCORE_H_INCLUDED
