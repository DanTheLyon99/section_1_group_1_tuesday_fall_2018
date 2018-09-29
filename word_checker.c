#include <stdio.h>
#include <string.h>
#include "word_checker.h"
#include <ctype.h>

char get_letter(int i, int j, struct rolled_dice **game_board){
    return game_board[i][j].character;
}

int abides_rules(int i, int j, char *word, struct rolled_dice** game_board, int sub_len, int **visited){
	int adj_cell;
	char current_letter = word[sub_len];
	int ans = (sub_len == (strlen(word)-1));


	if(sub_len == (strlen(word)-1)){
		return 1;
	}

	// right, digUpRight, up, digUpLeft, left, digDownLeft, down, digDownRight
	int all_x[] = {0, -1, -1, -1, 0, 1, 1, 1};
	int all_y[] = {1, 1, 0, -1, -1, -1, 0, 1};

		int new_x;
		int new_y;
	
		char find_letter;
			  find_letter = word[sub_len + 1];
			int result = 0;

			for(adj_cell = 0; adj_cell < 8; adj_cell++){
				int new_x = i + all_x[adj_cell];
				int new_y = j + all_y[adj_cell];
				if((new_x >= 0) && (new_x < 4) && (new_y >=0) && (new_y < 4) && toupper(find_letter) == get_letter(new_x, new_y, game_board) && !visited[new_x][new_y]){
					visited[new_x][new_y] = 1;
					++sub_len;
					result = abides_rules(new_x, new_y, word, game_board, sub_len, visited);
				if(result){
					return 1;
				}else{
				--sub_len;
				}
						
				}
			
		}
	
		return 0;
}


int word_checker(struct rolled_dice **game_board, char *word){
	
	int row, letter, col, m, n;
	int **visited;
	visited = malloc(sizeof(int * ) * 4);

	visited[0] = malloc(sizeof(int) * 4);
	visited[1] = malloc(sizeof(int) * 4);
	visited[2] = malloc(sizeof(int) * 4);
	visited[3] = malloc(sizeof(int) * 4);

	for(m = 0; m < 4; m++){
		for(n = 0; n < 4; n++){
			if(m == 0 && n == 0){
				visited[m][n] = 1;
			}else{
			visited[m][n] = 0;
			}
		}
	}

		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				if(abides_rules(row, col, word, game_board, 0, visited)){
						free(visited[0]);
						free(visited[1]);
						free(visited[2]);
						free(visited[3]);
					return 1;

				}
			}
			
		}
	
	free(visited[0]);
	free(visited[1]);
	free(visited[2]);
	free(visited[3]);

	return 0;

}

char test_get_letter(int i, int j, char **boggle){

	return boggle[i][j];
}



int test_abides_rules(int i, int j, char *word, char **game_board, int sub_len, int **visited){
		int adj_cell;
	// use sub_len as index to see what letter to find
	char current_letter = word[sub_len];
	int ans = (sub_len == (strlen(word)-1));
	if(sub_len == (strlen(word)-1)){
		return 1;
	}

	int all_x[] = {0, -1, -1, -1, 0, 1, 1, 1};
	int all_y[] = {1, 1, 0, -1, -1, -1, 0, 1};

		int new_x;
		int new_y;
	
		char find_letter;
			if(toupper(current_letter) == 'Q' && toupper(word[sub_len + 2]) == test_get_letter(i,j,game_board)){
				 find_letter = word[sub_len + 3];
				 sub_len++;
				 sub_len++;
				 current_letter = word[sub_len];
			}else{
				find_letter = word[sub_len + 1];
			}
			int result = 0;

			for(adj_cell = 0; adj_cell < 8; adj_cell++){
				int new_x = i + all_x[adj_cell];
				int new_y = j + all_y[adj_cell];
				if((new_x >= 0) && (new_x < 4) && (new_y >=0) && (new_y < 4) 
					&& toupper(find_letter) == test_get_letter(new_x, new_y, game_board) 
					&& !visited[new_x][new_y]){
					visited[new_x][new_y] = 1;
					++sub_len;
					result = test_abides_rules(new_x, new_y, word, game_board, sub_len, visited);
						if(result){
						return 1;
						}else{
						--sub_len;
						}
				}
		}
		return 0;
}


int test_word_checker(char **boggle, char *word){
	int row, letter, col, m, n;
	int **visited;
	visited = malloc(sizeof(int * ) * 4);

	visited[0] = malloc(sizeof(int) * 4);
	visited[1] = malloc(sizeof(int) * 4);
	visited[2] = malloc(sizeof(int) * 4);
	visited[3] = malloc(sizeof(int) * 4);

	for(m = 0; m < 4; m++){
		for(n = 0; n < 4; n++){
			if(m == 0 && n == 0){
				visited[m][n] = 1;
			}else{
			visited[m][n] = 0;
			}
		}
	}
		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				if(test_abides_rules(row, col, word, boggle, 0, visited)){
						free(visited[0]);
						free(visited[1]);
						free(visited[2]);
						free(visited[3]);
					return 1;

				}
			}
			
		}

	free(visited[0]);
	free(visited[1]);
	free(visited[2]);
	free(visited[3]);

	return 0;


}

int hc_word_checker(char boggle[][4], char *word){

	int row, letter, col, m, n;
	int **visited;
	visited = malloc(sizeof(int * ) * 4);

	visited[0] = malloc(sizeof(int) * 4);
	visited[1] = malloc(sizeof(int) * 4);
	visited[2] = malloc(sizeof(int) * 4);
	visited[3] = malloc(sizeof(int) * 4);

	for(m = 0; m < 4; m++){
		for(n = 0; n < 4; n++){
			if(m == 0 && n == 0){
				visited[m][n] = 1;
			}else{
			visited[m][n] = 0;
			}
		}
	}

		for (int row = 0; row < 4; row++) {
			for (int col = 0; col < 4; col++) {
				if(hc_abides_rules(row, col, word, boggle, 0, visited)){
						free(visited[0]);
						free(visited[1]);
						free(visited[2]);
						free(visited[3]);
					return 1;

				}
			}
			
		}

	free(visited[0]);
	free(visited[1]);
	free(visited[2]);
	free(visited[3]);

	return 0;

}


int hc_abides_rules(int i, int j, char *word, char boggle[][4], int sub_len, int **visited){
	int adj_cell;
	char current_letter = word[sub_len];
	int ans = (sub_len == (strlen(word)-1));
	if(sub_len == (strlen(word)-1)){
		return 1;
	}

	int all_x[] = {0, -1, -1, -1, 0, 1, 1, 1};
	int all_y[] = {1, 1, 0, -1, -1, -1, 0, 1};
		int new_x;
		int new_y;
	
		char find_letter;
			if(toupper(current_letter) == 'Q' && toupper(word[sub_len + 2]) == hc_get_letter(i,j,boggle)){
				 find_letter = word[sub_len + 3];
				 sub_len++;
				 sub_len++;
				 current_letter = word[sub_len];
		
			}else{
				find_letter = word[sub_len + 1];
			}
			int result = 0;

			for(adj_cell = 0; adj_cell < 8; adj_cell++){
				int new_x = i + all_x[adj_cell];
				int new_y = j + all_y[adj_cell];
				if((new_x >= 0) && (new_x < 4) && (new_y >=0) && (new_y < 4) 
					&& toupper(find_letter) == hc_get_letter(new_x, new_y, boggle) 
					&& !visited[new_x][new_y]){
						visited[new_x][new_y] = 1;
						++sub_len;
						result = hc_abides_rules(new_x, new_y, word, boggle, sub_len, visited);

						if(result){
							return 1;
						}else{
							--sub_len;
						}
						
				}
			
		}
	
		return 0;
	}



char hc_get_letter(int i, int j, char boggle[][4]){

	return boggle[i][j];
}
