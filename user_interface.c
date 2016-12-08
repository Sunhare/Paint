#include "board.h"
#include "draw.h"
#include "save.h"
#include "user_interface.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void read_args(int argc, char** argv, int* num_rows, int* num_cols){
	if(argc == 3){
		// if( isdigit( argv[1][0] ) && isdigit( argv[2][0] ) && (atoi(argv[1]) > 0) && (atoi(argv[2]) > 0) ){
		if ( (atoi(argv[1]) != 0) && (atoi(argv[2]) != 0)  ) {

			if( atoi(argv[1] ) < 1){
				printf("The number of rows is less than 1.\n");
				printf("Making default board of 10 X 10.\n");
				*num_rows = 10;
				*num_cols = 10;
				return;
			}

			else if(  atoi(argv[2]  ) < 1){
				printf("The number of columns is less than 1.\n");
				printf("Making default board of 10 X 10.\n");
				*num_rows = 10;
				*num_cols = 10;
				return;
			}
			else{
				*num_rows = atoi(argv[1]);
				*num_cols = atoi(argv[2]);
				return;
			}
		}
		else{ 

			if(!(isdigit( argv[1][0] )) ){
				printf("The number of rows is not an integer.\n");
			}
			else if(!(isdigit( argv[2][0] )) ){
				printf("The number of columns is not an integer.\n");
			}
			

			else if( (atoi(argv[1]) == 0) ){
				printf("The number of rows is less than 1.\n");

			}

			else if( (atoi(argv[2]) == 0) ){
				printf("The number of columns is less than 1.\n");

			} 

			printf("Making default board of 10 X 10.\n");
			*num_rows = 10;
			*num_cols = 10;
			return;
		}
	}
	else if(argc == 1){
		*num_rows = 10;
		*num_cols = 10;
		return;
	}
	else{
		printf("Wrong number of command line arguements entered.\n");
		printf("Usage: ./paint.out [num_rows num_cols]\n");
		printf("Making default board of 10 X 10.\n");
		*num_rows = 10;
		*num_cols = 10;
		return;
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
    char** all_commands = (char**)malloc(30*sizeof(char*));

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

void check_input_range(char** command, int num_checks, char* error_statement, int num_rows, int num_cols, char** board, int row_num, int col_num, int offset){
	int i;

	//atoi returns 0 if theres no digits remember this
	if(row_num != 0){
		for(i = row_num; i <= num_checks; i+=2){
			if(atoi(command[i]) > (num_rows - offset)  || atoi(command[i]) < 0){
				printf("%s\n", error_statement);
				print_board(board, num_rows, num_cols);
				get_command(board, num_rows, num_cols);
	
			}
		}
	}
	if(col_num != 0){
		for(i = col_num; i <= num_checks; i+=2){
			if(atoi(command[i]) > (num_cols - offset) || atoi(command[i]) < 0){
			printf("%s\n", error_statement);
			print_board(board, num_rows, num_cols);
			get_command(board, num_rows, num_cols);
	
			}	
		}
	}
}

//If there is a row parameter, compare it to the number of rows.
//if there is a column paramter,  compare it to the number of columns.


//void check_input_range(char** command, int num_checks, char* error_statement, int num_rows, int num_cols, char** board, 
//int row_num, int col_num, int offset)
void get_command(char** board, int num_rows, int num_cols){
	char** command;

	command = read_user_input();

	if(strlen(command[0]) != 1){
		printf("Unrecognized command. Type h for help.\n");
		print_board(board, num_rows, num_cols);
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
		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);

	}else if(command[0][0] == 'w'){
		input_incorrect(board, num_rows, num_cols, command, 5, "Improper draw command.");
		check_input_range(command, 4, "Improper draw command.", num_rows, num_cols, board, 1, 2, 0);
		
		if( command[1][0] == '2' && command[2][0] == '2' && command[3][0] == '4' && command[4][0] == '8') {
			printf("Cannot draw the line as it is not straight.");
			print_board(board, num_rows, num_cols);
			get_command(board, num_rows, num_cols);

		}
		write_line(command, board, num_rows, num_cols);
		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);

	}
	else if(command[0][0] == 'e'){
		input_incorrect(board, num_rows, num_cols, command, 3, "Improper erase command.");
		check_input_range(command, 2, "Improper erase command.", num_rows, num_cols, board, 1, 2, 1);
		erase_point(command, board, num_rows, num_cols);
		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);
	}
	else if(command[0][0] == 'r'){
		// input_incorrect(board, num_rows, num_cols, command, 3, "Improper resize command.");

		// printf("Command 1: %d\n", atoi(command[1]) );
		// printf("Command 2: %d\n", atoi(command[2]) );

		if( ((atoi(command[1]) <= 0)) || ((atoi(command[2]) <= 0)) ) {
			printf("Improper resize command.\n");
			print_board(board, num_rows, num_cols);
			get_command(board, num_rows, num_cols);
		}
		resize_board(command, board, num_rows, num_cols);
		num_rows = atoi(command[1] );
		num_cols = atoi(command[2] );

		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);

	}

	else if(command[0][0] == 'a'){
		input_incorrect(board, num_rows, num_cols, command, 3, "Improper add command.");
			
		// if( ( !(isdigit(command[2][0]) ) ) ){
		// 	printf("Improper add command.\n");
		// 	print_board(board, num_rows, num_cols);
		// 	get_command(board, num_rows, num_cols);
		// } 

		if( strcmp(command[1], "r") == 0){
			check_input_range(command, 2, "Improper add command.", num_rows, num_cols, board, 2, 0, -1);
		

			add_single_row(command, board, num_rows, num_cols);

			num_rows = num_rows + 1;
			print_board(board, num_rows, num_cols);
			get_command(board, num_rows, num_cols);
		}
		else if( strcmp(command[1], "c") == 0){
			check_input_range(command, 2, "Improper add command.", num_rows, num_cols, board, 0, 2, -1);

			add_single_col(command, board, num_rows, num_cols);

			num_cols = num_cols + 1;
			print_board(board, num_rows, num_cols);
			get_command(board, num_rows, num_cols);

		}
		else{
			printf("Improper add command.\n");
			print_board(board, num_rows, num_cols);
			get_command(board, num_rows, num_cols);
		}
	}

	else if(command[0][0] == 'd'){
		input_incorrect(board, num_rows, num_cols, command, 3, "Improper delete command.");
		
		if(strcmp(command[1], "r") == 0){
			check_input_range(command, 2, "Improper delete command.", num_rows , num_cols, board, 2, 0, 1);

			delete_single_row(command, board, num_rows, num_cols);			

			num_rows = num_rows - 1;
			print_board(board, num_rows, num_cols);
			get_command(board, num_rows, num_cols);
		}
		else if(strcmp(command[1], "c") == 0){
			check_input_range(command, 2, "Improper delete command.", num_rows , num_cols, board, 0, 2, 1);

			delete_single_col(command, board, num_rows, num_cols);
			
			num_cols = num_cols - 1;
			print_board(board, num_rows, num_cols);
			get_command(board, num_rows, num_cols);
		}
		
		else{
			printf("Improper delete command.\n");
			print_board(board, num_rows, num_cols);
			get_command(board, num_rows, num_cols);
		}

	}

	else if(command[0][0] == 's'){
		input_incorrect(board, num_rows, num_cols, command, 2, "Improper save command or file could not be created.");
		save_file(board, num_rows, num_cols, command[1]);
		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);
	}
	else if(command[0][0] == 'l'){
		input_incorrect(board, num_rows, num_cols, command, 2, "Improper load command or file could not be created.");
		load_file(board, num_rows, num_cols, command[1]);
		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);
	}
	//else if(command[0] == 'l'){}
}


