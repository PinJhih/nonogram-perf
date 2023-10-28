#ifndef BOARD_SOLVER_H
#define BOARD_SOLVER_H

#include "puzzle/board.h"
#include "puzzle/description.h"

using namespace std;

class BoardSolver {
	Description *clues;

   public:
	BoardSolver(Description *d);

	PixelSet propagate(Board &g);
};

#endif
