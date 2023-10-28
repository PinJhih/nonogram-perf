INCdir=../../include
FLAGS=-O2 -I$(INCdir)
OBJ=line_solver.o

all: $(OBJ)

%.o: %.cc
	g++ $^ -c $(FLAGS) -o $@

.PHONY: clean
clean:
	-rm -rf *.o
