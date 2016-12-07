#ifndef USER_INTERFACE_H
	#define USER_INTERFACE_H
		void read_args(int argc, char** argv, int* num_rows, int* num_cols);
		void print_help();
		void get_command(char** board, int num_rows, int num_cols);
		char** read_user_input();
		int length_command(char** command);
		void input_incorrect(char** board, int num_rows, int num_cols, char** command, int args_needed, char* error_statement);
		void check_input_range(char** command, int num_checks, char* error_statement, int num_rows, int num_cols, char** board, int row_num, int col_num, int offset);
#endif 
