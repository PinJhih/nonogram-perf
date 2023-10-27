#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include "constants.h"

class Description {
	Byte d[D_LEN];
	Byte length;

   public:
	Description();
	Description(const char* str);

	void print();

	const Byte size();
	const Byte operator[](int i);
};

#endif
