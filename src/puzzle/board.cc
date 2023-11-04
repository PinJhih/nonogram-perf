#include "puzzle/board.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>

using namespace std;

short hashIndex(int i, int j) {
	return i * 100 + j;
}

void toIndex(short p, int& i, int& j) {
	i = p / 100, j = p % 100;
}

Board::Board() {
	state = INCOMPLETE;
	for (int i = 0; i < BOARD_SIZE * 2; i++) {
		g[i] = Line(i + 1);
	}

	for (int i = 1; i <= BOARD_SIZE; i++) {
		for (int j = 1; j <= BOARD_SIZE; j++) {
			unpainted.insert(hashIndex(i, j));
		}
	}

	memset(paintedInRow, 0, sizeof(Byte) * BOARD_SIZE);
	memset(paintedInCol, 0, sizeof(Byte) * BOARD_SIZE);
}

Board::Board(const Board& h) {
	*this = h;
}

Board& Board::set(int i, int j, Byte c) {
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

bool Board::isPainted(int i, int j) {
	if (i > BOARD_SIZE)
		return isPainted(j, i - BOARD_SIZE);
	short p = hashIndex(i, j);
	return unpainted.count(p) == 0;
}

void Board::pickUnpainted(int& i, int& j) {
	short p = *(unpainted.begin());
	toIndex(p, i, j);
}

const vector<pair<short, Byte>> Board::unpaintedPixels() {
	vector<pair<short, Byte>> pixels;
	for (short p : unpainted) {
		int i, j;
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
	for (int i = 0; i < BOARD_SIZE; i++) {
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
