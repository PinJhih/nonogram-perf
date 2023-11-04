#include "solver/board_solver.h"

#include <cstdio>
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
	while (!lines.empty()) {
		//* retrieve a line
		Line &s = lines.front();
		int i = s.getIndex();

		//! check if fixable
		Description &d = clues[i - 1];
		LineSolver solver = LineSolver(d);
		if (not solver.fix(s, BOARD_SIZE, d.size(), d.cost())) {
			g.setState(CONFLICT);
			break;
		}

		//* paint the line
		solver.paint(s, BOARD_SIZE, d.size(), d.cost());
		for (int k = 1; k <= BOARD_SIZE; k++) {
			//* collect updated pixels
			Byte c = s.get(k);
			if (c == U || g.isPainted(i, k))
				continue;

			g.set(i, k, c);
			if (i <= BOARD_SIZE) {
				lines.push(g.getLine(k + 25));
				int p = i * 100 + k;
				updated.insert(p);
			} else {
				int p = k * 100 + (i - 25);
				lines.push(g.getLine(k));
				updated.insert(p);
			}
		}
		lines.pop();
	}
	return updated;
}

PixelSet BoardSolver::probeG(Board &gp, int x, int y, Byte c) {
	gp.set(x, y, c);
	return propagate(gp);
}

PixelSet BoardSolver::probe(Board &g, int x, int y) {
	Board gp0 = Board(g);
	Board gp1 = Board(g);
	PixelSet set0 = probeG(gp0, x, y, 0);
	PixelSet set1 = probeG(gp1, x, y, 1);

	if (gp0.conflict() && gp1.conflict()) {
		g.setState(CONFLICT);
		return PixelSet();
	}

	PixelSet pi;
	Board *src;
	if (gp0.conflict()) {
		src = &gp1;
		pi = set1;
		pi.insert(x * 100 + y);
	} else if (gp1.conflict()) {
		src = &gp0;
		pi = set0;
		pi.insert(x * 100 + y);
	} else {
		for (auto p : set0) {
			int a = p / 100, b = p % 100;
			if (gp0.get(a, b) == gp1.get(a, b)) {
				pi.insert(p);
			}
		}

		for (auto p : set1) {
			int a = p / 100, b = p % 100;
			if (gp0.get(a, b) == gp1.get(a, b)) {
				pi.insert(p);
			}
		}
		src = &gp0;
	}

	if (!pi.empty()) {
		g.setState(PAINTED);
		for (auto p : pi) {
			int a = p / 100, b = p % 100;
			g.set(a, b, src->get(a, b));
		}
	} else {
		g.setState(INCOMPLETE);
	}

	return pi;
}

void BoardSolver::fp1(Board &g) {
	while (true) {
		PixelSet pi = propagate(g);
		if (g.finished())
			return;

		for (auto p : g.unpaintedPixels()) {
			int i = p.first / 100, j = p.first % 100;
			if (pi.empty())
				pi = probe(g, i, j);
			else
				probe(g, i, j);

			if (g.finished())
				return;
			if (g.painted())
				break;
		}

		if (pi.empty())
			break;
		if (g.painted())
			g.setState(INCOMPLETE);
	}
}

void expand(BoardSolver &solver, Board &g, int i, int j, Byte c) {
	Board gp = Board(g);
	gp.set(i, j, c);
	solver.solve(gp);
	if (gp.solved()) {
		g = gp;
		return;
	}
}

void BoardSolver::pickPixel(Board &g, int &i, int &j) {
	int maxM = -1;
	int x, y;
	for (auto p : g.unpainted) {
		x = p / 100, y = p % 100;

		int m = g.paintedInRow[x] + g.paintedInCol[y];
		if (m > maxM) {
			i = x, j = y;
			maxM = m;
		}
	}
}

void BoardSolver::solve(Board &g) {
	fp1(g);
	if (g.finished())
		return;

	int i, j;
	pickPixel(g, i, j);

	expand(*this, g, i, j, 0);
	if (g.solved())
		return;
	expand(*this, g, i, j, 1);
}
