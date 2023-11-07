#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include "constants.h"

class Description {
	Byte d[D_LEN];
	Byte length;
	Byte sum;

   public:
	Description();
	Description(const char* str);

	void print();

	inline const Byte size() {
		return length;
	}

	inline const Byte operator[](Byte i) {
		return d[i - 1];
	}

	inline const Byte cost() {
		return sum;
	}
};

#endif
