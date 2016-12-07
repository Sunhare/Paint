#ifndef DRAW_H
	#define DRAW_H
		void write_line(char** command, char** board, int num_rows, int num_cols);
		void draw_hor(char** command, char** board, int num_rows, int num_cols);
		void draw_ver(char** command, char** board, int num_rows, int num_cols);
		void draw_zig(char** command, char** board, int num_rows, int num_cols);
		void draw_zag(char** command, char** board, int num_rows, int num_cols);
		void erase_point(char** command, char** board, int num_rows, int num_cols);
#endif 
