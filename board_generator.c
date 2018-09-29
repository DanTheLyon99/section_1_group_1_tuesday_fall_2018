#include "board_generator.h"

// Initializes the dice in the list of pre-set dice. Call once at program start.
void initialize_preset_dice(struct preset_dice* input_array_of_dice) {
	for (int i = 0; i < 16; i++) {
		input_array_of_dice[i].position = 0;
	}

	// initializes individual potential chars for each dice
	input_array_of_dice[0].configurations = "RIFOBX";
	input_array_of_dice[1].configurations = "IFEHEY";
	input_array_of_dice[2].configurations = "DENOWS";
	input_array_of_dice[3].configurations = "UTOKND";
	input_array_of_dice[4].configurations = "HMSRAO";
	input_array_of_dice[5].configurations = "LUPETS";
	input_array_of_dice[6].configurations = "ACITOA";
	input_array_of_dice[7].configurations = "YLGKUE";
	input_array_of_dice[8].configurations = "QBMJOA";
	input_array_of_dice[9].configurations = "EHISPN";
	input_array_of_dice[10].configurations = "VETIGN";
	input_array_of_dice[11].configurations = "BALIYT";
	input_array_of_dice[12].configurations = "EZAVND";
	input_array_of_dice[13].configurations = "RALESC";
	input_array_of_dice[14].configurations = "UWILRG";
	input_array_of_dice[15].configurations = "PACEMD";
}

// Rolls the dice to be used at the start of each game. Puts the rolled dice in
// game_dice. Does not shuffle the dice. Helper function.
void roll_but_not_shuffle_dice(struct rolled_dice* game_dice,
		struct preset_dice* input_array_of_dice) {

	srand(time(NULL));
	for (int i = 0; i < 16; i++) {
		int r = rand()%6;
		game_dice[i].character = input_array_of_dice[i].configurations[r];
	}
}

// Shuffles an array of rolled dice. Helper function.
void shuffle_rolled_dice_positions(struct rolled_dice* game_dice) {

	struct rolled_dice new_game_dice[16];

	int r = 0;
	for (int i = 0; i < 16; i++) {

		srand(time(NULL));
		// this is somewhat inefficient. Using it for now.
		while (game_dice[r].position == -1) {
			r = (int) (rand()%16);
		}
		new_game_dice[i] = game_dice[r];
		game_dice[r].position = -1;
	}

	for (int i = 0; i < 16; i++) {
		game_dice[i] = new_game_dice[i];
		game_dice[i].position = i+1;
	}
}


// Rolls the dice to be used at the start of the game and shuffles them, putting
// the dice into the 2D array game_dice. Call once at the start of every game.
void roll_dice(struct rolled_dice** game_board,
		struct preset_dice* input_array_of_dice){

	game_board[0] = malloc(sizeof(struct rolled_dice) * 4);
	game_board[1] = malloc(sizeof(struct rolled_dice) * 4);
	game_board[2] = malloc(sizeof(struct rolled_dice) * 4);
	game_board[3] = malloc(sizeof(struct rolled_dice) * 4);

	// temporary array of structs to contain adjusted 1D array of dice.
	struct rolled_dice adjusted_dice_array[16];

	roll_but_not_shuffle_dice(adjusted_dice_array, input_array_of_dice);
	shuffle_rolled_dice_positions(adjusted_dice_array);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			game_board[i][j] = adjusted_dice_array[i*4 + j];
		}
	}
}
// Prints a visualization of the input array of rolled_dice.
void print_game_board(struct rolled_dice** game_board) {

	for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (j != 3) {
					printf("%c \t", game_board[i][j].character);
				}
				else {
					printf("%c \n", game_board[i][j].character);

				}
			}
		}
}

void print_hc_board(char boggle[][4]) {

	for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (j != 3) {
					printf("%c \t", boggle[i][j]);
				}
				else {
					printf("%c \n", boggle[i][j]);

				}
			}
		}
}

/** Converts board from a string version to 2D array. Used in test mode**/
void convert_to_board(char *letters, char ***board){
	// allocate space for boggle board on heap in order to access it in main. 
	char *word;
	int i, j, t = 0;

	*board = malloc(sizeof(char * ) * 4);
	char **board_deref = *board;

	board_deref[0] = malloc(sizeof(char) * 4);
	board_deref[1] = malloc(sizeof(char) * 4);
	board_deref[2] = malloc(sizeof(char) * 4);
	board_deref[3] = malloc(sizeof(char) * 4);

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			if (j != 3) {
				board_deref[i][j] = letters[t];
				t++;
				
			}
			else {
				board_deref[i][j] = letters[t];
				t++;
			}
		}
	}
}
