//comment here
#include "board.h"
#include "draw.h"
#include "save.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// typedef Board_Struct{
// 	char** the_board;
// 	int num_rows;
// 	int num_cols;
// } Board;



int max(int a, int b){
	return a > b ? a : b;
}

void make_board(char*** board, int num_rows, int num_cols){
	int i, j;
	*board = (char**)malloc(num_rows*sizeof(char*));
	
	for(i = 0; i < num_rows; i++){
		(*board)[i] = (char*)malloc(num_cols*sizeof(char));
		for(j = 0; j < num_cols; j++){
			(*board)[i][j] = '*';
		}
	}
}


//BStruct board -> dp_board

void print_board(char** board, int num_rows, int num_cols){
	// printf("Entered Print Board\n");
	int i,j;
	int padding = 0;
	char str_num[10];
	// printf("Num Rows: %d", num_rows);
	
	sprintf(str_num, "%d", num_rows);
	padding = strlen(str_num);
	sprintf(str_num, "%d", num_cols);
	padding = max(padding, strlen(str_num));

	// printf("Right before the for loop to display the board\n");
	//display the board
	for(i = num_rows - 1; i >= 0; i--){
		// printf("Made it into the for loop\n");
		printf("%*d ", padding, i);
		// printf("Past the for loop for padding\n");
		for(j =0; j < num_cols; j++){
			// printf("2ndL ");
			// printf("j: %d", j);
			printf("%*c ", padding, board[i][j]); 
		}
		printf("\n");
	}
	// printf("Right after the for loop to display the board\n");
	
	printf("%*c ", padding, ' ');
	for(i = 0; i < num_cols; i++){
		printf("%*d ", padding, i);
	}
	printf("\n");

	// printf("Exited Print Board\n");


}



void more_rows(char** board, int num_rows, int num_cols, int rows_new, int cols_new){
	// printf("Entered More Rows\n");
	// printf("Num Rows: %d\n", num_rows);
	// printf("Rows New: %d\n", rows_new);
	//int rows_added = rows_new - num_rows;
	int i,j;

	board = (char**)realloc(board, rows_new * sizeof(char*));

	for(i = num_rows; i < rows_new; i++){

		board[i] = (char*)realloc(board[i], num_cols * sizeof(char));

		for(j = 0; j < num_cols; j++){
			board[i][j] = '*';
		}
	}

	// printf("Exited More Rows\n");
}




void more_cols(char** board, int num_rows, int num_cols, int rows_new, int cols_new){
	// printf("Entered More Cols\n");
	//int cols_added = cols_new - num_cols;
	int i, j;

	for(i = 0; i < num_rows; i++){

		board[i] = (char*)realloc(board[i], cols_new * sizeof(char));

		for(j = num_cols; j < cols_new; j++){
			board[i][j] = '*';
		}
	}
	// printf("Exited More Cols\n");
}


void less_rows(char** board, int num_rows, int num_cols, int rows_new, int cols_new){
	// printf("Entered Less Rows\n");
	board = (char**)realloc(board, rows_new * sizeof(char*));
	// printf("Exited Less Rows\n");
}

void less_cols(char** board, int num_rows, int num_cols, int rows_new, int cols_new){
	// printf("Entered Less Cols\n");
	int i;
	for(i = 0; i < num_rows; i++){
		board[i] = realloc(board[i], cols_new * sizeof(char));
	}
	// printf("Exited Less Cols\n");
}



void add_single_row(char** command, char** board, int num_rows, int num_cols){
	// printf("Entered Add Single Row\n");
	int i, j;
	more_rows(board, num_rows, num_cols, num_rows + 1, num_cols);

	for(i = num_rows; i > atoi(command[2]); i--){
		for(j = 0; j < num_cols; j++){
			board[i][j] = board[i-1][j];
		}
	}
	for(j = 0; j < num_cols; ++j){
		board[atoi(command[2])][j] = '*';
	}
	// printf("Exited Add Single Row\n");

}


void delete_single_row(char** command, char** board, int num_rows, int num_cols){
	// printf("Entered Delete Single Row\n");
	int i, j;
	//d r 0
	//i = 0 i < 9
	for(i = atoi(command[2]); i < num_rows - 1; i++){
		for(j = 0; j < num_cols; j++){
			board[i][j] = board[i+1][j];
		}
	}
	less_rows(board, num_rows, num_cols, num_rows - 1, num_cols);

	// printf("Exited Delete Single Row\n");

}
void delete_single_col(char** command, char** board, int num_rows, int num_cols){
	// printf("Entered Delete Single Col\n");
	int i, j; 

	for(j = atoi(command[2]); j < num_cols - 1; j++){
		for(i = 0; i < num_rows; i++){
			board[i][j] = board[i][j+1];
		}
	}
	less_cols(board, num_rows, num_cols, num_rows, num_cols - 1);
	// printf("Exited Delete Single Col\n");
}




void add_single_col(char** command, char** board, int num_rows, int num_cols){
	// printf("Entered Add Single Col\n");
	int i, j;
	more_cols(board, num_rows, num_cols, num_rows, num_cols+1);

	for(j = num_cols; j > atoi(command[2]); j--){
		for(i = 0; i <num_rows; i++){
			board[i][j] = board[i][j-1]; 
		}
	}
	for(i=0; i< num_rows; i++){
		board[i][atoi(command[2])] = '*';
	}
	// printf("Exited Add Single Col\n");
}




void resize_board(char** command, char** board, int num_rows, int num_cols){
	int rows_new = atoi(command[1]);
	int cols_new = atoi(command[2]);

	// printf("Entered the function Resize Board\n");
	// printf("Command 1 Rows New: %s\n", command[1]);
	// printf("Command 2 Cols New: %s\n", command[2]);
	// printf("Num_rows: %d\n", num_rows);
	// printf("Num_cols: %d\n", num_cols);

	if(rows_new > num_rows){
		// more_rows(board, num_rows, num_cols, rows_new, cols_new);

	}if(cols_new > num_cols){
		more_cols(board, num_rows, num_cols, rows_new, cols_new);
	}if(rows_new < num_rows){
		less_rows(board, num_rows, num_cols, rows_new, cols_new);
	}if(cols_new < num_cols){
		less_cols(board, num_rows, num_cols, rows_new, cols_new);
	}
	// printf("Exited the function Resize Board\n");
}







void destroy_board(char** board, int num_rows){
	int i;
	for(i = 0; i < num_rows; i++){
		free(board[i]);
	}
	free(board);
}
