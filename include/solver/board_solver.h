#ifndef BOARD_SOLVER_H
#define BOARD_SOLVER_H

#include "puzzle/board.h"
#include "puzzle/description.h"

using namespace std;

class BoardSolver {
	Description *clues;

	void fp1(Board &g);
	PixelSet propagate(Board &g);

	PixelSet probe(Board &g, int x, int y);
	PixelSet probeG(Board &gp, int x, int y, Byte c);
	void pickPixel(Board &g, int &i, int &j);

   public:
	BoardSolver(Description *d);

	void solve(Board &g);
};

#endif
