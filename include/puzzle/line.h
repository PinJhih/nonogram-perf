#ifndef LINE_H
#define LINE_H

#include "constants.h"

class Line {
	Byte index;
	Byte s[BOARD_SIZE];
	static char buffer[64];

   public:
	Line(int i);
	Line(const Line& l);

	Byte get(int i);
	void set(int i, Byte c);
	void print();
};

#endif
