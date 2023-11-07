#ifndef BOARD_SOLVER_H
#define BOARD_SOLVER_H

#include "puzzle/board.h"
#include "puzzle/description.h"

using namespace std;

class BoardSolver {
	Description *clues;

	void fp1(Board &g);
	PixelSet propagate(Board &g);

	int probe(Board &g, Byte x, Byte y);
	PixelSet probeG(Board &gp, Byte x, Byte y, Byte c);
	void pickPixel(Board &g, Byte &i, Byte &j);

   public:
	BoardSolver(Description *d);

	void solve(Board &g);
};

#endif
