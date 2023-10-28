#ifndef CONSTANT_H
#define CONSTANT_H

#define BOARD_SIZE 25
#define D_LEN 15
#define U 2

#include <unordered_set>

typedef char Byte;
typedef std::unordered_set<short> PixelSet;
enum State { CONFLICT, SOLVED, INCOMPLETE, PAINTED };

#endif
