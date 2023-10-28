#include "puzzle/board.h"

#include <cstring>

Board::Board() {
	state = INCOMPLETE;
	for (int i = 0; i < BOARD_SIZE * 2; i++) {
		g[i] = Line(i + 1);
	}
	memset(painted, 0, sizeof(bool) * BOARD_SIZE * BOARD_SIZE);
}

Board::Board(const Board& h) {
	state = h.state;
	for (int i = 0; i < BOARD_SIZE * 2; i++) {
		g[i] = Line(h.g[i]);
	}
	memset(painted, 0, sizeof(bool) * BOARD_SIZE * BOARD_SIZE);
}

Byte Board::get(int i, int j) {
	if (i == 0 || j == 0)
		return 0;
	return g[i - 1].get(j);
}

Board& Board::set(int i, int j, Byte c) {
	if (i > 25)
		return set(j, i - 25, c);
	if (!painted[i - 1][j - 1]) {
		g[i - 1].set(j, c);
		g[j + 24].set(i, c);

		painted[i - 1][j - 1] = true;
		countPainted++;

		if (countPainted == BOARD_SIZE * BOARD_SIZE)
			state = SOLVED;
	}
	return *this;
}

Line Board::getLine(int i) {
	return Line(g[i - 1]);
}

State Board::getState() {
	return state;
}

void Board::setState(State s) {
	state = s;
}

bool Board::isPainted(int i, int j) {
	if (i > 25)
		return painted[j - 1][i - 25 - 1];
	return painted[i - 1][j - 1];
}

void Board::print() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		g[i].print();
	}
	printf("\n");
}
