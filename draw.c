#include "draw.h"
#include "board.h"
#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write_line(char** command, char** board, int num_rows, int num_cols){
	int row1 = atoi(command[1]);
	int row2 = atoi(command[3]);
	int col1 = atoi(command[2]);
	int col2 = atoi(command[4]);

	if(row1 == row2){
		draw_hor(command, board, num_rows, num_cols);

	}else if(col1 == col2){
		draw_ver(command, board, num_rows, num_cols);
	}else if(((row1 > row2) && (col1 < col2)) || ((row1 < row2) && (col1 > col2))){
		//left to right neg slope
		draw_zig(command, board, num_rows, num_cols);
	}else{
		draw_zag(command, board, num_rows, num_cols);
	}
}
void erase_point(char** command, char** board, int num_rows, int num_cols){
	int row = atoi(command[1]);
	int col = atoi(command[2]);
	if(board[row][col] != '*'){
		board[row][col] = '*';
	}
}

//Draws a point or a horizontal line
void draw_hor(char** command, char** board, int num_rows, int num_cols){
	// printf("Entered Horiz\n");
	int i;
	int row = atoi(command[1]);
	int col1 = atoi(command[2]);
	int col2 = atoi(command[4]);

	if(col1 <= col2){ 
		for(i = col1; i <= col2; ++i){
			if(board[row][i] == '-'){
				board[row][i] = '-';
			}else if(board[row][i] != '*'){
				board[row][i] = '+';
			}else{
				board[row][i] = '-';	
			}
		}
	}
	if(col1 > col2){ 
		for(i = col2; i <= col1; ++i){
			if(board[row][i] == '-'){
				board[row][i] = '-';
			}else if(board[row][i] != '*'){
				board[row][i] = '+';
			}else{
				board[row][i] = '-';	
			}
		}
	}
}

//Draws a vertical line
void draw_ver(char** command, char** board, int num_rows, int num_cols){
	// printf("Entered Ver\n");
	int i;
	int col = atoi(command[2]);
	int row1 = atoi(command[1]);
	int row2 = atoi(command[3]);

	if(row1 <= row2){ 
		for(i = row1; i <= row2; ++i){
			if(board[i][col] == '|'){
				board[i][col] = '|';
			}else if(board[i][col] != '*'){
				board[i][col] = '+';
			}else{
				board[i][col] = '|';	
			}
		}
	}

	if(row1 > row2){ 
		for(i = row2; i <= row1; ++i){
			if(board[i][col] == '|'){
				board[i][col] = '|';
			}else if(board[i][col] != '*'){
				board[i][col] = '+';
			}else{
				board[i][col] = '|';	
			}
		}
	}
}

//Draws a left to right negative slope line
void draw_zig(char** command, char** board, int num_rows, int num_cols){
	// printf("Entered Zig\n");
	int i;
	int row1 = atoi(command[1]) ;
	//int row2 = command[3] ;
	int col1 = atoi(command[2]) ;
	int col2 = atoi(command[4]) ;
	if(col1 < col2){
		for(i = col1; i <= col2; ++i){
			if(board[row1][i] == '\\'){
				board[row1][i] = '\\';
			}else if(board[row1][i] != '*'){
				board[row1][i] = '+';
			}else{
				board[row1][i] = '\\';
			}
			row1--;
		}
	}else{
		for(i = col1; i >= col2; --i){
			if(board[row1][i] == '\\'){
				board[row1][i] = '\\';
			}else if(board[row1][i] != '*'){
				board[row1][i] = '+';
			}else{
				board[row1][i] = '\\';
			}
			row1++;
		}
	}
}

//Draws a left to right positive slope line
void draw_zag(char** command, char** board, int num_rows, int num_cols){
	// printf("Entered Zag\n");
	int i;
	int row1 = atoi(command[1]) ;
	int row2 = atoi(command[3]);
	int col1 = atoi(command[2]) ;
	int col2 = atoi(command[4]) ;

	if(row1 < row2){
		for(i = col1; i <= col2; ++i){
			if(board[row1][i] == '/'){
				board[row1][i] = '/';
			}else if(board[row1][i] != '*'){
				board[row1][i] = '+';
			}else{
				board[row1][i] = '/';
			}
			row1++;
		}
	}else{
		for(i = col1; i >= col2; --i){
			if(board[row1][i] == '/'){
				board[row1][i] = '/';
			}else if(board[row1][i] != '*'){
				board[row1][i] = '+';
			}else{
				board[row1][i] = '/';
			}
			row1--;
		}
	}
}