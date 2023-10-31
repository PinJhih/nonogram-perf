#ifndef BOARD_H
#define BOARD_H

#include <unordered_set>
#include <vector>
typedef std::unordered_set<short> PixelSet;

#include "puzzle/line.h"

class Board {
	Line g[BOARD_SIZE * 2];
	State state;
	PixelSet unpainted;
	Byte paintedInRow[BOARD_SIZE], paintedInCol[BOARD_SIZE];

   public:
	Board();
	Board(const Board& h);

	void print();
	Board& set(int i, int j, Byte c);

	inline Byte get(int i, int j) {
		if (i == 0 || j == 0)
			return 0;
		return g[i - 1].get(j);
	}

	inline Line getLine(int i) {
		return Line(g[i - 1]);
	}

	inline State getState() {
		return state;
	}

	inline void setState(State s) {
		state = s;
	}

	inline bool finished() {
		return state == CONFLICT || state == SOLVED;
	}

	inline bool conflict() {
		return state == CONFLICT;
	}

	inline bool solved() {
		return state == SOLVED;
	}

	inline bool painted() {
		return state == PAINTED;
	}

	bool isPainted(int i, int j);
	void pickUnpainted(int& i, int& j);
	const std::vector<std::pair<short, Byte>> unpaintedPixels();

	Board& operator=(const Board& h);
};

#endif
