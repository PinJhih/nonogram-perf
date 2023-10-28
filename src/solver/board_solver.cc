#include "solver/board_solver.h"

#include <cstring>
#include <queue>

#include "solver/line_solver.h"

using namespace std;

BoardSolver::BoardSolver(Description *d) {
	clues = d;
}

PixelSet BoardSolver::propagate(Board &g) {
	//* init set-PI, list-G
	PixelSet updated;
	queue<Line> lines;
	for (int i = 1; i <= BOARD_SIZE * 2; i++) {
		lines.push(g.getLine(i));
	}

	//* iteration
	int counter = 0;
	while (!lines.empty()) {
		//* retrieve a line
		Line s = lines.front();
		int i = s.getIndex();
		lines.pop();

		//! check if fixable
		Description d = clues[i - 1];
		LineSolver solver = LineSolver(s, d);
		if (not solver.fix(BOARD_SIZE, d.size())) {
			g.setState(CONFLICT);
			break;
		}

		//* paint the line
		solver.paint(BOARD_SIZE, d.size());
		for (int k = 1; k <= BOARD_SIZE; k++) {
			//* collect updated pixels
			Byte c = s.get(k);
			if (c == U || g.isPainted(i, k))
				continue;

			g.set(i, k, c);
			if (i <= BOARD_SIZE) {
				lines.push(g.getLine(k + 25));
				updated.insert(i * 100 + k);
			} else {
				lines.push(g.getLine(k));
				updated.insert((k - 25) * 100 + i);
			}
		}
		counter++;
	}
	return updated;
}
