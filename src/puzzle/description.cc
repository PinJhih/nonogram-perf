#include "puzzle/description.h"

#include <cstdio>

Description::Description() {
	length = 0;
}

Description::Description(const char* str) {
	length = 0;

	Byte num = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '\t' || str[i] == '\n') {
			d[length] = num, num = 0;
			length++;
		} else if('0' <= str[i] && str[i] <= '9') {
			num *= 10, num += str[i] - '0';
		}
	}

	if (num != 0) {
		d[length] = num;
		length++;
	}
}

void Description::print() {
	printf("(%2d):", length);
	for (int i = 0; i < length; i++) {
		printf(" %2d", d[i]);
	}
	printf("\n");
}

const Byte Description::size() {
	return length;
}

const Byte Description::operator[](int i) {
	return d[i - 1];
}
