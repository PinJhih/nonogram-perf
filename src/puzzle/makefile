INCdir=../../include
FLAGS=-O2 -I$(INCdir)
OBJ=description.o line.o board.o

all: $(OBJ)

%.o: %.cc
	g++ $^ -c $(FLAGS) -o $@

.PHONY: clean
clean:
	-rm -rf *.o
