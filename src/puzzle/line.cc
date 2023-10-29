#include "puzzle/line.h"

#include <cstdio>

Line::Line() {
	Line(1);
}

Line::Line(int i) {
	index = i;
	bits = (1LL << 52) - 1;
	bits -= 0b11;
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
		if (get(i + 1) == U)
			buffer[i * 2] = 'U';
		else
			buffer[i * 2] = get(i + 1) + '0';
	}
	printf("%s", buffer);
}
