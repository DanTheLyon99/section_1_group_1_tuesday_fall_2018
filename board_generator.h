#ifndef BOARD_GEN
#define BOARD_GEN

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/* Author: Daniel Lyon 
   Date: 10/09/2018
   Description: Contains all function protocols
   and structs for the board_generator.h program
*/

// The pre-set dice which keep their values between games.
typedef struct preset_dice {
	char *configurations;
	int position;
} PresetDice;

// The rolled dice which do not keep their values between games.
typedef struct rolled_dice {
	char character;
	int position;
} RolledDice;


void initialize_preset_dice(struct preset_dice* input_array_of_dice);
void roll_but_not_shuffle_dice(struct rolled_dice* game_dice,
		struct preset_dice* input_array_of_dice);

void shuffle_rolled_dice_positions(struct rolled_dice* game_dice);
void print_game_board(struct rolled_dice** game_board);
void roll_dice(struct rolled_dice** game_board,
		struct preset_dice* input_array_of_dice);

void convert_to_board(char *letters, char ***board);
void print_hc_board(char boggle[][4]);

#endif
