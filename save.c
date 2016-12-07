#include "save.h"
#include "board.h"
#include <stdio.h>
#include <string.h>

//Might need to add command to change file name
int save_file(char** board, int num_rows, int num_cols, char* file_name){

  FILE * fp;

  fp = fopen(file_name, "w+");

  fprint_board(fp, board, num_rows, num_cols);

  fclose (fp);

  return 0;
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