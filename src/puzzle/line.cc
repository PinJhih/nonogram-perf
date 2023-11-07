#include "puzzle/line.h"

#include <cstdio>

Line::Line() {
	Line(1);
}

Line::Line(int i) {
	index = i;
	bits = (1LL << 50) - 1;
	bits <<= 2;
}

Line::Line(const Line& l) {
	bits = l.bits;
	index = l.index;
}

void Line::print() {
	static char buffer[] =
		"U U U U U U U U U U U U U "
		"U U U U U U U U U U U U\n";

	for (int i = 0; i < 25; i++) {
		Byte c = get(i + 1);
		if (c == U)
			buffer[i * 2] = 'U';
		else
			buffer[i * 2] = c + '0';
	}
	printf("%s", buffer);
}
