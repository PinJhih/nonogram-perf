#include "puzzle/description.h"

#include <cstdio>

Description::Description() {
	length = 0;
	sum = 0;
}

Description::Description(const char* str) {
	sum = 0;
	length = 0;

	Byte num = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '\t' || str[i] == '\n') {
			sum += num;
			d[length] = num, num = 0;
			length++;
		} else if ('0' <= str[i] && str[i] <= '9') {
			num *= 10, num += str[i] - '0';
		}
	}

	if (num != 0) {
		sum += num;
		d[length] = num;
		length++;
	}
	sum += length - 1;
}

void Description::print() {
	printf("(%2d %2d):", length, sum);
	for (int i = 0; i < length; i++) {
		printf(" %2d", d[i]);
	}
	printf("\n");
}
