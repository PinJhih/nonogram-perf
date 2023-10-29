#ifndef BOARD_H
#define BOARD_H

#include <unordered_set>
typedef std::unordered_set<short> PixelSet;

#include "puzzle/line.h"

class Board {
	Line g[BOARD_SIZE * 2];
	State state;
	PixelSet unpainted;

   public:
	Board();
	Board(const Board& h);

	void print();
	Byte get(int i, int j);
	Board& set(int i, int j, Byte c);
	Line getLine(int i);

	State getState();
	void setState(State s);
	bool finished();
	bool conflict();
	bool solved();
	bool painted();

	bool isPainted(int i, int j);
	void pickUnpainted(int& i, int& j);
	const PixelSet& unpaintedPixels();

	Board& operator=(const Board& h);
};

#endif
