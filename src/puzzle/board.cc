#include "puzzle/board.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>

using namespace std;

inline short hashIndex(Byte i, Byte j) {
	return i * 100 + j;
}

inline void toIndex(short p, Byte& i, Byte& j) {
	i = p / 100, j = p % 100;
}

Board::Board() {
	state = INCOMPLETE;
	for (Byte i = 0; i < BOARD_SIZE * 2; i++) {
		g[i] = Line(i + 1);
	}

	for (Byte i = 1; i <= BOARD_SIZE; i++) {
		for (Byte j = 1; j <= BOARD_SIZE; j++) {
			unpainted.insert(hashIndex(i, j));
		}
	}

	memset(paintedInRow, 0, sizeof(Byte) * BOARD_SIZE);
	memset(paintedInCol, 0, sizeof(Byte) * BOARD_SIZE);
}

Board::Board(const Board& h) {
	*this = h;
}

Board& Board::set(Byte i, Byte j, Byte c) {
	if (i > BOARD_SIZE)
		return set(j, i - BOARD_SIZE, c);

	short p = hashIndex(i, j);
	if (unpainted.count(p) != 0) {
		paintedInRow[i]++, paintedInCol[j]++;
		g[i - 1].set(j, c);
		g[j + 24].set(i, c);

		unpainted.erase(p);
		if (unpainted.empty())
			state = SOLVED;
	}
	return *this;
}

bool Board::isPainted(Byte i, Byte j) {
	if (i > BOARD_SIZE)
		return isPainted(j, i - BOARD_SIZE);
	short p = hashIndex(i, j);
	return unpainted.count(p) == 0;
}

void Board::pickUnpainted(Byte& i, Byte& j) {
	short p = *(unpainted.begin());
	toIndex(p, i, j);
}

const vector<pair<short, Byte>> Board::unpaintedPixels() {
	vector<pair<short, Byte>> pixels;
	for (short p : unpainted) {
		Byte i, j;
		toIndex(p, i, j);
		pixels.push_back({p, paintedInRow[i] + paintedInCol[j]});
	}

	auto cmp = [](const pair<short, Byte>& a, const pair<short, Byte>& b) {
		return a.second > b.second;
	};
	sort(pixels.begin(), pixels.end(), cmp);
	return pixels;
}

void Board::print() {
	for (Byte i = 0; i < BOARD_SIZE; i++) {
		g[i].print();
	}
}

Board& Board::operator=(const Board& h) {
	state = h.state;
	unpainted = h.unpainted;
	memcpy(g, h.g, sizeof(Line) * BOARD_SIZE * 2);
	memcpy(paintedInRow, h.paintedInRow, sizeof(Byte) * BOARD_SIZE);
	memcpy(paintedInCol, h.paintedInCol, sizeof(Byte) * BOARD_SIZE);
	return *this;
}
