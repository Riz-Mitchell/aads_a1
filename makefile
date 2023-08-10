dict1: data.o list.o
	gcc -Wall -g -o dict1 main.o data.o list.o
main.o: main.c
	gcc -Wall -g -c main.c
data.o: data.h data.c
	gcc -Wall -g -c data.c
list.o: list.h list.c
	gcc -Wall -g -c list.c