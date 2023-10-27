#ifndef LINE_SOLVER_H
#define LINE_SOLVER_H

#include "puzzle/description.h"
#include "puzzle/line.h"

class LineSolver {
	Line& s;
	Description& d;

	bool fix0(int i, int j);
	bool fix1(int i, int j);
	bool matchSigma(int i, int j);

	void paintP(int i, int j);
	void paint0(int i, int j);
	void paint1(int i, int j);
	static void merge(Line& s, Line& t, int i);

   public:
	LineSolver(Line& line, Description& clue) : s{line}, d{clue} {}

	void paint(int i, int j);
	bool fix(int i, int j);
};

#endif
