#ifndef LINE_SOLVER_H
#define LINE_SOLVER_H

#include "puzzle/description.h"
#include "puzzle/line.h"

class LineSolver {
	Line& s;
	Description& d;

	bool fix0(int i, int j, Byte remain);
	bool fix1(int i, int j, Byte remain);
	bool matchSigma(int i, int j);

	void paintP(int i, int j, Byte remain);
	void paint0(int i, int j, Byte remain);
	void paint1(int i, int j, Byte remain);
	static void merge(Line& s, Line& t, int i);

   public:
	LineSolver(Line& line, Description& clue) : s{line}, d{clue} {}

	void paint(int i, int j, Byte remain);
	bool fix(int i, int j, Byte remain);
};

#endif
