#ifndef SAVE_H
	#define SAVE_H
		#include <stdio.h>
		int save_file(char** board, int num_rows, int num_cols, char* file_name);
		void fprint_board(FILE * fp, char** board, int num_rows, int num_cols);
#endif 
