#include "solver/line_solver.h"

#include <cstdio>

bool LineSolver::fix(Line& s, Byte i, Byte j, Byte remain) {
	if (i < -1)
		return false;

	if (i <= 0) {
		if (j == 0)
			return true;
		return false;
	}

	if (i < remain)
		return false;
	return fix0(s, i, j, remain) || fix1(s, i, j, remain);
}

bool LineSolver::fix0(Line& s, Byte i, Byte j, Byte remain) {
	if (s.get(i) != 1)
		return fix(s, i - 1, j, remain);
	return false;
}

bool LineSolver::fix1(Line& s, Byte i, Byte j, Byte remain) {
	if (j <= 0)
		return false;
	int dj = d[j];
	if (i - dj < 0)
		return false;

	if (matchSigma(s, i, dj))
		return fix(s, i - dj - 1, j - 1, remain - dj - 1);
	return false;
}

bool LineSolver::matchSigma(Line& s, Byte i, Byte dj) {
	if (i - dj < 0)
		return false;

	for (Byte k = i - dj + 1; k <= i; k++) {
		if (s.get(k) == 0)
			return false;
	}
	return s.get(i - dj) != 1;
}

void LineSolver::paint(Line& s, Byte i, Byte j, Byte remain) {
	if (i <= 0)
		return;
	paintP(s, i, j, remain);
}

void LineSolver::paintP(Line& s, Byte i, Byte j, Byte remain) {
	bool f0 = fix0(s, i, j, remain), f1 = fix1(s, i, j, remain);
	if (f0 && !f1) {
		paint0(s, i, j, remain);
	} else if (!f0 && f1) {
		paint1(s, i, j, remain);
	} else {
		Line t = Line(s);
		paint0(s, i, j, remain);
		paint1(t, i, j, remain);
		merge(s, t, i);
	}
}

void LineSolver::paint0(Line& s, Byte i, Byte j, Byte remain) {
	s.set(i, 0);
	paint(s, i - 1, j, remain);
}

void LineSolver::paint1(Line& s, Byte i, Byte j, Byte remain) {
	int dj = d[j];
	for (Byte k = 0; k < dj; k++) {
		s.set(i - k, 1);
	}
	s.set(i - dj, 0);
	paint(s, i - dj - 1, j - 1, remain - dj - 1);
}

void LineSolver::merge(Line& s, Line& t, Byte i) {
	for (Byte k = 1; k <= i; k++) {
		if (s.get(k) != t.get(k))
			s.set(k, U);
	}
}
