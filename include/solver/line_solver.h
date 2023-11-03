#ifndef LINE_SOLVER_H
#define LINE_SOLVER_H

#include "puzzle/description.h"
#include "puzzle/line.h"

class LineSolver {
	Description& d;

	bool fix0(Line& s, int i, int j, Byte remain);
	bool fix1(Line& s, int i, int j, Byte remain);
	bool matchSigma(Line& s, int i, int j);

	void paintP(Line& s, int i, int j, Byte remain);
	void paint0(Line& s, int i, int j, Byte remain);
	void paint1(Line& s, int i, int j, Byte remain);
	static void merge(Line& s, Line& t, int i);

   public:
	LineSolver(Description& clue) : d{clue} {}

	void paint(Line& s, int i, int j, Byte remain);
	bool fix(Line& s, int i, int j, Byte remain);
};

#endif
