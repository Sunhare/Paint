#ifndef SAVE_H
	#define SAVE_H
		#include <stdio.h>
		void save_file(char** board, int num_rows, int num_cols, char* file_name);
		void fprint_board(FILE * fp, char** board, int num_rows, int num_cols);
		char* read_line(FILE* fp);
		void read_lines(FILE* fp, char*** lines, int* num_lines);
		void load_file(char** board, int num_rows, int num_cols, char* file_name);
#endif 
