#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#include "board_generator.h"
#include "word_checker.h"
#include "scoreboard.h"

#define MAX_LINE 100

/**
 - set up board,
 - set up dictionary,
 **/

void increment_total_score(int *user_score, char *word);

void free_and_reset_board(struct rolled_dice** game_board,
		struct preset_dice* input_array_of_dice) {

	for (int i = 0; i < 4; i++) {
		free(game_board[i]);
	}
	roll_dice(game_board, input_array_of_dice);
}


char *convert_to_upper(char **upper){
	char *upper_deref = *upper;

	for(int i = 0; upper_deref[i]; i++){
	  upper_deref[i] = toupper(upper_deref[i]);
	}
	return upper_deref;
}

char *convert_to_upper2(char (*upper)[]){
	char *upper_deref = *upper;

	for(int i = 0; upper_deref[i]; i++){
	  upper_deref[i] = toupper(upper_deref[i]);
	}
	return upper_deref;
}

void increment_total_score(int *user_score, char *word){
	int word_len = strlen(word);
	fprintf(stdout, "word_len: %d\n",word_len );
	if(word_len == 3 || word_len == 4){
		*user_score+=1;
	}else if(word_len == 5){
		*user_score+=2;
	}else if(word_len == 6){
		*user_score+=3;
	}else if(word_len == 7){
		*user_score+=5;
	}else if(word_len >= 8){
		*user_score+=11;
	}
}


int main (int argc, char ** argv) {
	int i, points = 0, test_points = 0, invalid_size = 0;
	char input_word[100];
	char original_input_word[100];

	FILE *input_FP;
	char line [MAX_LINE];
	char *file_name;
 	
 	const char * dict_name = "EnglishWords.txt";
	DNode* check_english;
	DNode* check_submitted;
	static DNode* english_dictionary [BIG_HASH_SIZE];
	static DNode* guessed_words [SMALL_HASH_SIZE];

	int current_score = 0;
	int turn_count = 0;

	User* head = NULL;
	head = (User*)malloc(sizeof(User));

	PresetDice global_dice[16];
	RolledDice *game_board[4];

	FILE *output_FP;
	char read_line[MAX_LINE]; 


	if(!(input_FP = fopen ( dict_name , "r" )))    {
        fprintf(stderr,"Could not open file \"%s\" for reading dictionary words\n", dict_name);
        return 1;
    }

	while( fgets (line, MAX_LINE, input_FP)!=NULL ) {
		line[strcspn(line, "\r\n")] = '\0';  //trim new line characters
		insert (english_dictionary, BIG_HASH_SIZE, convert_to_upper2(&line));
	}	
	fclose (input_FP);


	if (argc == 1){
		fprintf(stdout, "playing in normal mode\n\n");

		system("clear");

		initialize_preset_dice(global_dice);

		roll_dice(game_board, global_dice);

		while (turn_count >= 0) {
			strcpy(original_input_word, input_word);

			convert_to_upper2(&input_word);

			User *thisUser;
			char input_name[100];

			if (strcmp(original_input_word, "q") == 0) {
				// "q" is the input, print scoreboard and exit game
				print_scoreboard(head);
				break;
			}
			// "n" is the input, adds user to/changes user in linked list and
			// resets game
			if (strcmp(original_input_word, "n") == 0) {

				print_scoreboard(head);
				fprintf(stdout, "Your current score: %d \n", current_score);
				fprintf(stdout, "What is your name? \n");
				scanf("%s", input_name);

				if (user_is_in_list(head, input_name) == 0){
					add_node(head, input_name, current_score);
				}
				else {
					update_node_with_name(head, input_name, current_score);
				}

				current_score = 0;

				strcpy(input_word, "");

				free_and_reset_board(game_board, global_dice);
				turn_count = 0;
				system("clear");
				continue;
			}

			print_game_board(game_board);

			check_english = lookup (english_dictionary, BIG_HASH_SIZE, input_word);			
			
			if (check_english != NULL) {
				check_submitted = lookup (guessed_words, SMALL_HASH_SIZE, input_word);
				
				if (check_submitted == NULL) {
					if(strlen(input_word) > 2){
						if(word_checker(game_board, input_word)){
							insert (guessed_words, SMALL_HASH_SIZE, input_word);
							increment_total_score(&current_score, input_word);
							fprintf (stdout, "Correct! You current score is now: %d \n", current_score);
					
						}else{
							fprintf (stderr, "The submitted word: \'%s\'' does not abide game rules. Try again!\n", original_input_word);
						}
					}else{
						fprintf (stderr, "The submitted word: \'%s\'' must be at least 3 letters long. Try again!\n", original_input_word);
					}

				}else{
					fprintf (stderr, "You have already submitted the word: \'%s\'' Try again!\n", original_input_word);
				}

		 	}else if (turn_count > 0){
		 		fprintf (stderr, "Incorrect word: \'%s\' is not in the English Dictionary. Try again!\n", original_input_word);
			}
			fprintf(stdout, "Submit a word you found:\n");
	       	scanf("%s", input_word);
	        turn_count++;
	        system("clear");
   		}
		for (int i = 0; i < 4; i++) {
			free(game_board[i]);
		}
		free_all(head);

	}else if (argc == 2){
				file_name =  argv[1];
		fprintf(stdout, "playing in test mode with file: %s\n", file_name);
		FILE *test_file_FP;
		char test_line [MAX_LINE];
		char *test_words;
		char **test_board;
		int file_line_counter = 1;
		int i,j;
		DNode* test_result;
		int begin = 0;

		// (1) read first line which is the board
		if(!(test_file_FP = fopen ( file_name , "r" )))    {
		    fprintf(stderr,"Could not open test file \'%s\' for reading\n", file_name);
		    return 1;
		}else if(!(output_FP = fopen("result.txt", "w" ))){
	   	 fprintf(stderr,"Could not open result file \'%s\' for writing\n", "result.txt");
		    return 1;
		}

		while (fgets (test_line, MAX_LINE, test_file_FP)!=NULL ) {
			test_line[strcspn(test_line, "\r\n")] = '\0';  //trim new line characters

			if(file_line_counter == 1){
					convert_to_board(test_line, &test_board);

					// this can be removed, its just for testing purposes
					for (i = 0; i < 4; i++) {
						for (j = 0; j < 4; j++) {
							if (j != 3) {
								fprintf(stdout, "%c \t", test_board[i][j] );
							}else {
								fprintf(stdout, "%c \n", test_board[i][j] );
							
							}
						}
					
					}
			
			}else if (file_line_counter >= 2){
				for (char *p = strtok(test_line,","); p != NULL; p = strtok(NULL, ",")){
					check_english = lookup (english_dictionary, BIG_HASH_SIZE, convert_to_upper(&p));
						
					if (check_english != NULL) {
						check_submitted = lookup (guessed_words, SMALL_HASH_SIZE, p);
						
						if (check_submitted == NULL) {
							if(test_word_checker(test_board, p)){
								insert (guessed_words, SMALL_HASH_SIZE, p);
								increment_total_score(&test_points, p);
								fprintf(stdout,"Correct! You total score is now: %d \n",test_points );
						
							}else{
								if(begin == 0){								
									fprintf(output_FP, "%s", p );
									begin++;
								}else{
									fprintf(output_FP, ",%s", p );
								}
								
								fprintf(stderr,"The submitted word: \'%s\'' does not abide game rules. Try again!\n", p);								
							}

						}else{
								if(begin == 0){								
									fprintf(output_FP, "%s", p );
									begin++;
								}else{
									fprintf(output_FP, ",%s", p );
								}
							fprintf(stderr,"You have already submitted the word: \'%s\'' Try again!\n", p);
						}

			
				 	}else{
						if(begin == 0){								
							fprintf(output_FP, "%s", p );
							begin++;
						}else{
							fprintf(output_FP, ",%s", p );
						}

				 		fprintf(stderr,"Incorrect word: \'%s\'' is not in the English Dictionary. Try again!\n", p);
					}
				}
			}
			file_line_counter++;
		}

		fprintf(output_FP, "\n");
		fprintf(output_FP, "%d\n", test_points);

		fclose (test_file_FP);

		for (int i = 0; i < 4; i++) {
			free(test_board[i]);
		}
		free(test_board);

		fclose(output_FP);

	}

	free_dictionary(english_dictionary, BIG_HASH_SIZE);
	free_dictionary(guessed_words, SMALL_HASH_SIZE);

	return 0;
}
