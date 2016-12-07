#include "board.h"
#include "draw.h"
#include "save.h"
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





char** read_user_input(){
    // char user_command[] ="all/cows/eat";

    int size = 5;
	char* user_command = (char*)malloc(size*sizeof(char));

	int i = 0;
	int j = 0;
	// int k = 0;

	printf("Enter your command: ");

// //This code gets input until the new line character
	while (1) {
		scanf("%c", &user_command[i]);
		if (user_command[i] == '\n') {
			user_command = (char*)realloc(user_command, i*sizeof(char));

			user_command[i] = '\0';
			break;
		}
		else {
			i++;
			if(i > size){
				size *= 2;
				user_command = (char*)realloc(user_command, size*sizeof(char));
			}
		}
	}


	//This is the current parsed string
    char* curr_string = strtok (user_command, " ");
    
    //This is the 2D array that is going to get the values
    char** all_commands = (char**)malloc(6*sizeof(char*));

    while (curr_string != NULL)
    {
        all_commands[j] = curr_string;
        curr_string = strtok (NULL, " ");
        j++;
    }

    // for (i = 0; i < 3; ++i) {
    //         printf("%s\n", all_commands[i]);
    // }


    // while(all_commands[k] != NULL){
    // 	printf("%s\n", all_commands[k]);
    // 	k++;
    // }

    return all_commands;
}

int length_command(char** command){
	int i = 0;
	int count = 0;

	while(command[i] != NULL){
		count++;
		i++;
	}	
	return count;
}

void input_incorrect(char** board, int num_rows, int num_cols, char** command, int args_needed, char* error_statement){
	if(length_command(command) != args_needed){
			printf("%s\n", error_statement);
			print_board(board, num_rows, num_cols);
			get_command(board, num_rows, num_cols);
		}
}
void check_input_range(char** command, int num_checks, char* error_statement, int num_rows, int num_cols, char** board){
	int i;
	//atoi returns 0 if theres no digits remember this
	for(i = 1; i <= num_checks; i++){
		if(atoi(command[i]) > num_rows || atoi(command[i]) < 0){
			printf("%s\n", error_statement);
			print_board(board, num_rows, num_cols);
			get_command(board, num_rows, num_cols);
			i++;
		}
	}
	for(i = 2; i <= num_checks; ++i){
		if(atoi(command[i]) > num_cols || atoi(command[i]) < 0){
		printf("%s\n", error_statement);
		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);
		i++;
		}	
	}
}
void get_command(char** board, int num_rows, int num_cols){
	char** command;

	command = read_user_input();

	if(strlen(command[0] != 1)){
		printf("Unrecognized command. Type h for help.\n");
		get_command(board, num_rows, num_cols);
	}

	if(command[0][0] == 'q'){
		input_incorrect(board, num_rows, num_cols, command, 1, "Unrecognized command. Type h for help.");
		destroy_board(board, num_rows);
		exit(0);
	}
	else if(command[0][0] == 'h'){
		input_incorrect(board, num_rows, num_cols, command, 1, "Unrecognized command. Type h for help.");
		print_help();
		get_command(board, num_rows, num_cols);

	}else if(command[0][0] == 'w'){
		input_incorrect(board, num_rows, num_cols, command, 5, "Improper draw command.");
		check_input_range(command, 4, "Improper draw command.", num_rows, num_cols, board);
		write_line(command, board, num_rows, num_cols);
		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);

	}
	else if(command[0][0] == 'e'){
		input_incorrect(board, num_rows, num_cols, command, 3, "Improper erase command.");
		check_input_range(command, 2, "Improper erase command.", num_rows, num_cols, board);
		erase_point(command, board, num_rows, num_cols);
		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);
	}
	else if(command[0][0] == 'r'){
		input_incorrect(board, num_rows, num_cols, command, 3, "Improper resize command.");
		check_input_range(command, 3, "Improper resize command.", num_rows, num_cols, board);
		resize_board(command, board, num_rows, num_cols);
		num_rows = atoi(command[1]);
		num_cols = atoi(command[2]);
		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);

	}

	else if(command[0][0] == 'a'){
		input_incorrect(board, num_rows, num_cols, command, 3, "Improper add command.");
		check_input_range(command, 2, "Improper add command.", num_rows, num_cols, board);
		if(command[1][0] == 'r'){
			add_single_row(command, board, num_rows, num_cols);
			num_rows = num_rows + 1;
			print_board(board, num_rows, num_cols);
		}
		else if(command[1][0] == 'c'){
			add_single_col(command, board, num_rows, num_cols);
			num_cols = num_cols + 1;
			print_board(board, num_rows, num_cols);
		}
		get_command(board, num_rows, num_cols);
	}

	else if(command[0][0] == 'd'){
		input_incorrect(board, num_rows, num_cols, command, 3, "Improper delete command.");
		check_input_range(command, 2, "Improper delete command.", num_rows, num_cols, board);
		if(command[1][0] == 'r'){
			delete_single_row(command, board, num_rows, num_cols);
			num_rows = num_rows - 1;
			print_board(board, num_rows, num_cols);
		}
		else if(command[1][0] == 'c'){
			delete_single_col(command, board, num_rows, num_cols);
			num_cols = num_cols - 1;
			print_board(board, num_rows, num_cols);
		}
		get_command(board, num_rows, num_cols);

	}

	else if(command[0][0] == 's'){
		input_incorrect(board, num_rows, num_cols, command, 3, "Improper save command or file could not be created.");
		save_file(board, num_rows, num_cols, command[1]);
		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);
	}
	//else if(command[0] == 'l'){}
}


