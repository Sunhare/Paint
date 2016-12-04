paint.out: paint.o board.o draw.o user_interface.o
	gcc -g -Wall -Werror -o paint.out paint.o board.o draw.o user_interface.o
	
paint.o: paint.c board.h draw.h 
	gcc -g -Wall -Werror -c -o paint.o paint.c

board.o: board.c board.h draw.h
	gcc -g -Wall -Werror -c -o board.o board.c
	
draw.o: draw.c draw.h board.h
	gcc -g -Wall -Werror -c -o draw.o draw.c

user_interface.o: user_interface.c user_interface.h
	gcc -g -Wall -Werror -c -o user_interface.o user_interface.c
	
clean:
	rm -f *.o *.out

