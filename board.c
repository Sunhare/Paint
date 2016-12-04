//comment here
#include "board.h"
#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void print_board(char** board, int num_rows, int num_cols){
	int i,j;
	int padding = 0;
	char str_num[10];
	
	sprintf(str_num, "%d", num_rows);
	padding = strlen(str_num);
	sprintf(str_num, "%d", num_cols);
	padding = max(padding, strlen(str_num));
	
	//display the board
	for(i = num_rows - 1; i >= 0; i--){
		printf("%*d ", padding, i);
		for(j =0; j < num_cols; j++){
			printf("%*c ", padding,  board[i][j]); 
		}
		printf("\n");
	}
	
	printf("%*c ", padding, ' ');
	for(i = 0; i < num_cols; i++){
		printf("%*d ", padding, i);
	}
	printf("\n");


}



void more_rows(char*** board, int num_rows, int num_cols, int rows_new, int cols_new){
	//int rows_added = rows_new - num_rows;
	int i,j;
	*board = (char**)realloc((*board), rows_new * sizeof(char*));

	for(i = num_rows; i < rows_new ; i++){
		(*board)[i] = (char*)realloc((*board)[i], num_cols * sizeof(char));
		for(j = 0; j < num_cols; j++){
			(*board)[i][j] = '*';
		}
	}
}




void more_cols(char*** board, int num_rows, int num_cols, int rows_new, int cols_new){
	//int cols_added = cols_new - num_cols;
	int i, j;
	for(i = 0; i < num_rows; i++){
		(*board)[i] = (char*)realloc((*board)[i], cols_new * sizeof(char));
		for(j = num_cols; j < cols_new; j++){
			(*board)[i][j] = '*';
		}
	}
}


void less_rows(char*** board, int num_rows, int num_cols, int rows_new, int cols_new){
	(*board) = (char**)realloc((*board), rows_new * sizeof(char*));
}

void less_cols(char*** board, int num_rows, int num_cols, int rows_new, int cols_new){
	int i;
	for(i = 0; i < num_rows; i++){
		(*board)[i] = realloc((*board)[i], cols_new * sizeof(char));
	}
}



void add_single_row(char* command, char*** board, int num_rows, int num_cols){
	int i, j;
	more_rows(board, num_rows, num_cols, num_rows + 1, num_cols);

	for(i = num_rows; i > (command[2]-'0'); i--){
		for(j = 0; j < num_cols; j++){
			(*board)[i][j] = (*board)[i-1][j];
		}
	}
	for(j = 0; j < num_cols; ++j){
		(*board)[(command[2]-'0')][j] = '*';
	}

}


void delete_single_row(char* command, char*** board, int num_rows, int num_cols){
	int i, j;
	
	for(i = (command[2] - '0') - 1; i < num_rows - 1; i++){
		for(j = 0; j < num_cols; j++){
			(*board)[i][j] = (*board)[i+1][j];
		}
	}
	less_rows(board, num_rows, num_cols, num_rows - 1, num_cols);

}
void delete_single_col(char* command, char*** board, int num_rows, int num_cols){
	int i, j; 

	for(j = (command[2] - '0') - 1; j < num_cols - 1; j++){
		for(i = 0; i < num_rows; i++){
			(*board)[i][j] = (*board)[i][j+1];
		}
	}
	less_cols(board, num_rows, num_cols, num_rows, num_cols - 1);
}




void add_single_col(char* command, char*** board, int num_rows, int num_cols){
	int i, j;
	more_cols(board, num_rows, num_cols, num_rows, num_cols+1);

	for(j = num_cols; j > (command[2]-'0'); j--){
		for(i = 0; i <num_rows; i++){
			(*board)[i][j] = (*board)[i][j-1]; 
		}
	}
	for(i=0; i< num_rows; i++){
		(*board)[i][(command[2]-'0')] = '*';
	}

}




void resize_board(char* command, char*** board, int num_rows, int num_cols){
	int rows_new = command[1] - '0';
	int cols_new = command[2] - '0';
	if(rows_new > num_rows){
		more_rows(board, num_rows, num_cols, rows_new, cols_new);
	}if(cols_new > num_cols){
		more_cols(board, num_rows, num_cols, rows_new, cols_new);
	}if(rows_new < num_rows){
		less_rows(board, num_rows, num_cols, rows_new, cols_new);
	}if(cols_new < num_cols){
		less_cols(board, num_rows, num_cols, rows_new, cols_new);
	}
}







void destroy_board(char** board, int num_rows){
	int i;
	for(i = 0; i < num_rows; i++){
		free(board[i]);
	}
	free(board);
}
