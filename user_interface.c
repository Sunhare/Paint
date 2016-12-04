#include "board.h"
#include "draw.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_args(int argc, char** argv, int* num_rows, int* num_cols){
	if(argc == 3){
		*num_rows = atoi(argv[1]);
		*num_cols = atoi(argv[2]);
	}else{
		*num_rows = 10;
		*num_cols = 10;
	}
}
void print_help(){

	printf("Commands:\n");
	printf("Help: h\n");
	printf("Quit: q\n");
	printf("Draw line: w row_start col_start row_end col_end\n");
	printf("Resize: r num_rows num_cols\n");
	printf("Add row or column: a [r | c] pos\n");
	printf("Delete row or column: d [r | c] pos\n");
	printf("Erase: e row col\n");
	printf("Save: s file_name\n");
	printf("Load: l file_name\n");
}

void get_command(char*** board, int num_rows, int num_cols){
	char command[10];
	printf("Enter your command: ");\
	scanf("%s", command);
	
	if(command[0] == 'q'){
		destroy_board(*board, num_rows);
		exit(0);
	}else if(command[0] == 'h'){
		print_help();
	}else if(command[0] == 'w'){
		write_line(command, board, num_rows, num_cols);
		print_board(*board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);
	}else if(command[0] == 'e'){
		erase_point(command, *board, num_rows, num_cols);
		print_board(*board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);
	}else if(command[0] == 'r'){
		resize_board(command, board, num_rows, num_cols);
		print_board(*board, command[1]-'0', command[2] - '0');
		get_command(board, num_rows, num_cols);
	}
	else if(command[0] == 'a'){
		if(command[1] == 'r'){
			add_single_row(command, board, num_rows, num_cols);
			print_board(*board, num_rows + 1, num_cols);
		}
		else{
			add_single_col(command, board, num_rows, num_cols);
			print_board(*board, num_rows, num_cols + 1);
		}
		get_command(board, num_rows, num_cols);

	}
	else if(command[0] == 'd'){
		if(command[1] == 'r'){
			delete_single_row(command, board, num_rows, num_cols);
			print_board(*board, num_rows-1, num_cols);
		}
		else{
			delete_single_col(command, board, num_rows, num_cols);
			print_board(*board, num_rows, num_cols-1);
		}
		get_command(board, num_rows, num_cols);

	}
	// else if(command[0] == 's'){

	// }else if(command[0] == 'l'){

	// }

}

