#ifndef BOARD_GEN
#define BOARD_GEN

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/* Author: Daniel Lyon 
   Date: 29/10/2018
   Description: Contains all function protocols
   and structs for the board_generator.c program
*/

/* The pre-set dice which keep their values between games*/
typedef struct presetDice 
{
	char *configurations;
	int position;
} PresetDice;

/*The rolled dice which do not keep their values between games*/
typedef struct rolledDice 
{
	char character;
	int position;
} RolledDice;

/* initializes individual potential chars for each dice*/
void initializePresetDice( struct presetDice* inputArrayOfDice );

/* Rolls the dice to be used at the start of each game. Puts the rolled dice in
   gameDice. Does not shuffle the dice. Helper function*/
void rollButNotShuffleDice( struct rolledDice* gameDice,
							struct presetDice* inputArrayOfDice );

/* Shuffles an array of rolled dice. Helper function*/
void shuffleRolledDicePositions( struct rolledDice* gameDice );

/* Prints a visualization of the input array of rolledDice*/
void printGameBoard( struct rolledDice** gameBoard );

/* Rolls the dice to be used at the start of the game and shuffles them, putting
   the dice into the 2D array gameDice. Call once at the start of every game*/
void rollDice( struct rolledDice** gameBoard,
			   struct presetDice* inputArrayOfDice );

/* Converts board from a string version to 2D array. Used in test mode*/
void convertToBoard( char *letters, char ***board );

#endif
