# Define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# Define libraries to be linked (for example -lm)
LDLIBS = 

# Define sets of source files and object files
SRC = main.c data.c list.c query.c utils.c stages.c array.c quicksort.c binarysearch.c
# OBJ is the same as SRC, just replace .c with .o
OBJ = $(SRC:.c=.o)
 
# Define the executable name(s)
EXE = dict1

# The first target:
$(EXE): $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LIB)

# Other targets specify how to get the .o files

clean:
	rm -f $(OBJ) $(EXE)
