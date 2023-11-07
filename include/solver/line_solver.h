#ifndef LINE_SOLVER_H
#define LINE_SOLVER_H

#include "puzzle/description.h"
#include "puzzle/line.h"

class LineSolver {
	Description& d;

	bool fix0(Line& s, Byte i, Byte j, Byte remain);
	bool fix1(Line& s, Byte i, Byte j, Byte remain);
	bool matchSigma(Line& s, Byte i, Byte j);

	void paintP(Line& s, Byte i, Byte j, Byte remain);
	void paint0(Line& s, Byte i, Byte j, Byte remain);
	void paint1(Line& s, Byte i, Byte j, Byte remain);
	static void merge(Line& s, Line& t, Byte i);

   public:
	LineSolver(Description& clue) : d{clue} {}

	void paint(Line& s, Byte i, Byte j, Byte remain);
	bool fix(Line& s, Byte i, Byte j, Byte remain);
};

#endif
