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

















void get_command(char** board, int num_rows, int num_cols){
	char** command;

	command = read_user_input();
	// printf("Size of Command: %lu\n", sizeof(command));

	// printf("Your command:\n");

	// int i=0;
	// int count= 0;

	//Counts how many elements of command there are
	// while(command[i] != NULL){
	// 	count+= 1;
	// 	i++;
	// }


	// for(int i = 0; i<count; i++){
	// 	printf("%s", command[i]);
	// }
	// printf("\n");

	// printf("Command at [0][0] : %c\n", command[0][0]);
	// printf("Command at 1      : %s\n", command[1]);
	// printf("Command at 2      : %s\n", command[2]);
	// printf("Command at 3      : %s\n", command[3]);
	// printf("Command at 4      : %s\n", command[4]);


	if(command[0][0] == 'q'){
		// printf("Entered Quit\n");
		destroy_board(board, num_rows);
		exit(0);
	}
	else if(command[0][0] == 'h'){
		// printf("Entered Help\n");
		print_help();
		get_command(board, num_rows, num_cols);

	}
	else if(command[0][0] == 'w'){
		// printf("Entered Write\n");
		write_line(command, board, num_rows, num_cols);
		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);

	}
	else if(command[0][0] == 'e'){
		// printf("Entered Erase\n");
		erase_point(command, board, num_rows, num_cols);
		print_board(board, num_rows, num_cols);
		get_command(board, num_rows, num_cols);

	}
	else if(command[0][0] == 'r'){
		// printf("Entered Resize\n");
		resize_board(command, board, num_rows, num_cols);
		// printf("Before the atoi\n");
		num_rows = atoi(command[1]);
		num_cols = atoi(command[2]);
		// printf("After the atoi\n");

		// printf("Before the print_board\n");
		print_board(board, num_rows, num_cols);
		// printf("After the print_board\n");

		
		get_command(board, num_rows, num_cols);

	}

	else if(command[0][0] == 'a'){
		if(command[1][0] == 'r'){
			// printf("Entered Add Row\n");
			add_single_row(command, board, num_rows, num_cols);
			num_rows = num_rows + 1;
			print_board(board, num_rows, num_cols);
		}
		else if(command[1][0] == 'c'){
			// printf("Entered Add Column\n");
			add_single_col(command, board, num_rows, num_cols);
			num_cols = num_cols + 1;
			print_board(board, num_rows, num_cols);
		}
		get_command(board, num_rows, num_cols);
	}

	else if(command[0][0] == 'd'){
		if(command[1][0] == 'r'){
			// printf("Entered Delete Row\n");
			delete_single_row(command, board, num_rows, num_cols);
			num_rows = num_rows - 1;
			print_board(board, num_rows, num_cols);
		}
		else if(command[1][0] == 'c'){
			// printf("Entered Delete Column\n");
			delete_single_col(command, board, num_rows, num_cols);
			num_cols = num_cols - 1;
			print_board(board, num_rows, num_cols);
		}
		get_command(board, num_rows, num_cols);

	}

	else if(command[0][0] == 's'){
		// printf("Entered Save\n");
		save_file(board, num_rows, num_cols, command[1]);

	}
	// else if(command[0] == 'l'){

	// }

}

