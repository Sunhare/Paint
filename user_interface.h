#ifndef USER_INTERFACE_H
	#define USER_INTERFACE_H
		void read_args(int argc, char** argv, int* num_rows, int* num_cols);
		void print_help();
		void get_command(char** board, int num_rows, int num_cols);
		char** read_user_input();
#endif 
