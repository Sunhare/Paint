#include "board.h"
#include "draw.h"
#include "user_interface.h"
#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv){
	char** board;
	int num_rows = 10;
	int num_cols = 10;
	
	read_args(argc, argv, &num_rows, &num_cols);
	make_board(&board, num_rows, num_cols);

	print_board(board, num_rows, num_cols);
	get_command(board, num_rows, num_cols);
	
	destroy_board(board, num_rows);
	return 0;
}