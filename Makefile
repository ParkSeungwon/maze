CFLAG = -c -std=c++11 -lpthread -g -fmax-errors=3
CC = g++
SRC = $(wildcard *.cc)
OBJ = $(patsubst %.cc, %.o, $(SRC))
EXE = $(patsubst %.cc, %.x, $(SRC))

all : $(OBJ)
	$(CC) -o maze $(OBJ)

%.o : %.cc
	$(CC) $< $(CFLAG)
#	./$@

clean:
	rm $(OBJ)
