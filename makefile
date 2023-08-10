dict1: main.o data.o list.o stages.o utils.o
	gcc -Wall -g -o dict1 main.o data.o list.o stages.o utils.o
main.o: main.c
	gcc -Wall -g -c main.c
data.o: data.h data.c
	gcc -Wall -g -c data.c
list.o: list.h list.c
	gcc -Wall -g -c list.c
stages.o: stages.h stages.c
	gcc -Wall -g -c stages.c
utils.o: utils.h utils.c
	gcc -Wall -g -c utils.c