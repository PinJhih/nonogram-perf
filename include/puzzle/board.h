#ifndef BOARD_H
#define BOARD_H

#include "puzzle/line.h"

class Board {
	Line g[BOARD_SIZE * 2];
	State state;
	bool painted[BOARD_SIZE][BOARD_SIZE];
	short countPainted = 0;

   public:
	Board() ;
	Board(const Board& h) ;

	Byte get(int i, int j);
	Board& set(int i, int j, Byte c);
	Line getLine(int i) ;

	State getState() ;
	void setState(State s);
	bool isPainted(int i, int j) ;

	void print();
};

#endif
