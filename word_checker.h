#include <string.h>
#include "board_generator.h"
#include <stdlib.h>

/* Author: Daniel Lyon 
   Date: 10/09/2018
   Description: Contains all function protocols
   for the word_checker.c program
*/

int word_checker(struct rolled_dice **game_board, char *word);
int abides_rules(int i, int j, char *word, struct rolled_dice** game_board, int sub_len, int **visited);
// returns the gameboard character at the specefied index
char get_letter(int i, int j, struct rolled_dice **game_board);

int test_word_checker(char **boggle, char *word);
int test_abides_rules(int i, int j, char *word, char **game_board, int sub_len, int **visited);
char test_get_letter(int i, int j, char **boggle);

int hc_word_checker(char boggle[][4], char *word);
char hc_get_letter(int i, int j, char boggle[][4]);
int hc_abides_rules(int i, int j, char *word, char boggle[][4], int sub_len, int **visited);



