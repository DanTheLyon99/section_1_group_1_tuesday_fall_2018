#include <string.h>
#include "board_generator.h"
#include <stdlib.h>


int wordChecker(struct RolledDice **game_board, char *word);
int abidesRules(int i, int j, char *word, struct RolledDice** game_board, int sub_len, int **visited);
char getLetter(int i, int j, struct RolledDice **game_board);

int test_word_checker(char **boggle, char *word);
int test_abides_rules(int i, int j, char *word, char **game_board, int sub_len, int **visited);
char test_get_letter(int i, int j, char **boggle);

int hc_word_checker(char boggle[][4], char *word);
char hc_get_letter(int i, int j, char boggle[][4]);
int hc_abides_rules(int i, int j, char *word, char boggle[][4], int sub_len, int **visited);
