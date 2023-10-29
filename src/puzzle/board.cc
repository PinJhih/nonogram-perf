#include "puzzle/board.h"

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
}

Board::Board(const Board& h) {
	state = h.state;
	unpainted = h.unpainted;
	for (int i = 0; i < BOARD_SIZE * 2; i++) {
		g[i] = Line(h.g[i]);
	}
}

Byte Board::get(int i, int j) {
	if (i == 0 || j == 0)
		return 0;
	return g[i - 1].get(j);
}

Board& Board::set(int i, int j, Byte c) {
	if (i > BOARD_SIZE)
		return set(j, i - BOARD_SIZE, c);

	short p = hashIndex(i, j);
	if (unpainted.count(p) != 0) {
		g[i - 1].set(j, c);
		g[j + 24].set(i, c);

		unpainted.erase(p);
		if (unpainted.empty())
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

bool Board::finished() {
	return state == CONFLICT || state == SOLVED;
}

bool Board::conflict() {
	return state == CONFLICT;
}

bool Board::solved() {
	return state == SOLVED;
}

bool Board::painted() {
	return state == PAINTED;
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

const PixelSet& Board::unpaintedPixels() {
	return unpainted;
}

void Board::print() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		g[i].print();
	}
}
