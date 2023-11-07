#ifndef LINE_H
#define LINE_H

#include "constants.h"

class Line {
	Byte index;
	long long bits;

   public:
	Line();
	Line(int i);
	Line(const Line& l);
	void print();

	inline const Byte get(int i) {
		return (bits >> (i << 1)) & 0b11;
	}

	inline void set(int i, Byte c) {
		long long mask = 0b11;
		i <<= 1;
		mask <<= i;
		bits &= ~mask;

		mask = c;
		mask <<= i;
		bits |= mask;
	}

	Byte getIndex() {
		return index;
	}
};

#endif
