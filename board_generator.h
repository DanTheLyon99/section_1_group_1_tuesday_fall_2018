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

// initializes individual potential chars for each dice
void initialize_preset_dice(struct preset_dice* input_array_of_dice);

// Rolls the dice to be used at the start of each game. Puts the rolled dice in
// game_dice. Does not shuffle the dice. Helper function.
void roll_but_not_shuffle_dice(struct rolled_dice* game_dice,
		struct preset_dice* input_array_of_dice);

// Shuffles an array of rolled dice. Helper function.
void shuffle_rolled_dice_positions(struct rolled_dice* game_dice);

// Prints a visualization of the input array of rolled_dice.
void print_game_board(struct rolled_dice** game_board);

// Rolls the dice to be used at the start of the game and shuffles them, putting
// the dice into the 2D array game_dice. Call once at the start of every game.
void roll_dice(struct rolled_dice** game_board,
		struct preset_dice* input_array_of_dice);
//Converts board from a string version to 2D array. Used in test mode
void convert_to_board(char *letters, char ***board);
//takes in a 2D character array to print out the board
void print_hc_board(char boggle[][4]);

#endif
