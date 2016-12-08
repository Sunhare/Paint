#include "save.h"
#include "board.h"
#include "user_interface.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//Might need to add command to change file name
void save_file(char** board, int num_rows, int num_cols, char* file_name){

  FILE * fp;

  fp = fopen(file_name, "w+");

  fprint_board(fp, board, num_rows, num_cols);

  fclose (fp);


}

void fprint_board(FILE * fp, char** board, int num_rows, int num_cols){
	int i,j;
	int padding = 0;
	char str_num[10];
	
	sprintf(str_num, "%d", num_rows);
	padding = strlen(str_num);
	sprintf(str_num, "%d", num_cols);
	padding = max(padding, strlen(str_num));
	
	//display the board
	for(i = num_rows - 1; i >= 0; i--){
		fprintf(fp, "%*d ", padding, i);
		for(j =0; j < num_cols; j++){
			fprintf(fp, "%*c ", padding,  board[i][j]); 
		}
		fprintf(fp, "\n");
	}
	
	fprintf(fp, "%*c ", padding, ' ');
	for(i = 0; i < num_cols; i++){
		fprintf(fp, "%*d ", padding, i);
	}
	fprintf(fp, "\n");


}













char* read_line(FILE* fp){

	char* line = NULL;
	int line_len = 0;
	char c;
	
	do{
	
		fscanf(fp, "%c", &c);
		
		if(feof(fp)){
			break;
		}
		
		line_len++;
		line = realloc(line, line_len * sizeof(char));
		line[line_len - 1] = c;
	}while(c != '\n');
	
	if(line_len > 0){
		//add in the null character
		line_len++;
		line = realloc(line, line_len * sizeof(char));
		line[line_len - 1] = '\0';
	}
	
	return line;
}

void read_lines(FILE* fp, char*** lines, int* num_lines){
	/*
		read all of the lines in fp
		@fp: a file pointer opened in read mode
		@lines: a pointer indicating where the lines should be placed. If there are no lines in a fill NULL is retured
		@num_lines: a pointer to the number of lines. set to the number of lines contained within lines
		@modifies: lines, num_lines
	*/

	char* cur_line;
	
	*lines = NULL;
	*num_lines = 0;
	
	while((cur_line = read_line(fp))){
		(*num_lines)++;
		*lines = realloc(*lines, *num_lines * sizeof(char*));
		(*lines)[*num_lines - 1] = cur_line;
	}
}

void load_file(char** board, int num_rows, int num_cols, char* file_name){
	FILE* fp;
	fp = fopen(file_name, "r+");

	char** lines;
	char** load_board;

	int n = 0;

	int num_lines;

	if(fp == NULL){
		printf("Failed to open file: %s\n", file_name);
		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);
		
	}

	read_lines(fp, &lines, &num_lines);

	fseek(fp , 0 , SEEK_SET );
	while (fgetc(fp) != EOF) {
		n++;
	}

	fseek(fp, n-3, SEEK_SET);

	num_rows = lines[0][1] - '0';
	num_cols = fgetc(fp);

	make_board(&load_board, num_rows, num_cols);

	for(int i = 0; i < num_rows; i++){
		for(int j = 0; j < num_cols; j++){
			load_board[i][j] = lines[i][j];
		}
	}

	fclose(fp);
	return;
	// print_board(board, num_rows, num_cols);
	// get_command(board, num_rows, num_cols);

}