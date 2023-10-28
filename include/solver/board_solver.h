#ifndef BOARD_SOLVER_H
#define BOARD_SOLVER_H

#include "puzzle/board.h"
#include "puzzle/description.h"

using namespace std;

class BoardSolver {
	Description *clues;

	PixelSet probe(Board &g, int x, int y);
	PixelSet probeG(Board &gp, int x, int y, Byte c);

   public:
	BoardSolver(Description *d);

	PixelSet propagate(Board &g);
	void fp1(Board &g);
};

#endif
