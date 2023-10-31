BIN=../bin
INCdir=../include
FLAGS=-I$(INCdir) -O2
SUBdir=puzzle solver

.PHONY: all $(SUBdir)
all: nonogram

nonogram: $(SUBdir)
	mkdir -p ../bin
	g++ nonogram.cc */*.o $(FLAGS) -o $(BIN)/nonogram
	g++ checker.cc puzzle/description.o $(FLAGS) -o $(BIN)/checker

$(SUBdir):
	$(MAKE) -C $@

clean:
	$(MAKE) -C puzzle clean
	$(MAKE) -C solver clean
