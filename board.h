#ifndef BOARD_H
	#define BOARD_H
		int max(int a, int b);
		void make_board(char*** board, int num_rows, int num_cols);
		void print_board(char** board, int num_rows, int num_cols);

		void more_rows(char*** board, int num_rows, int num_cols, int rows_new, int cols_new);
		void more_cols(char*** board, int num_rows, int num_cols, int rows_new, int cols_new);

		void less_rows(char*** board, int num_rows, int num_cols, int rows_new, int cols_new);
		void less_cols(char*** board, int num_rows, int num_cols, int rows_new, int cols_new);


		void add_single_row(char* command, char*** board, int num_rows, int num_cols);
		void add_single_col(char* command, char*** board, int num_rows, int num_cols);

		void delete_single_row(char* command, char*** board, int num_rows, int num_cols);
		void delete_single_col(char* command, char*** board, int num_rows, int num_cols);
		
		void resize_board(char* command, char*** board, int num_rows, int num_cols);
		void destroy_board(char** board, int num_rows);

#endif 
