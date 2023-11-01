#include "solver/line_solver.h"

#include <cstdio>

bool LineSolver::fix(int i, int j, Byte remain) {
	if (i < -1)
		return false;

	if (i == 0 || i == -1) {
		if (j == 0)
			return true;
		return false;
	}

	if (i < remain)
		return false;
	return fix0(i, j, remain) || fix1(i, j, remain);
}

bool LineSolver::fix0(int i, int j, Byte remain) {
	if (s.get(i) == 0 || s.get(i) == U)
		return fix(i - 1, j, remain);
	return false;
}

bool LineSolver::fix1(int i, int j, Byte remain) {
	if (j <= 0)
		return false;
	int dj = d[j];
	if (i - dj < 0)
		return false;

	if (matchSigma(i, dj))
		return fix(i - dj - 1, j - 1, remain - dj - 1);
	return false;
}

bool LineSolver::matchSigma(int i, int dj) {
	if (i - dj < 0)
		return false;

	for (int k = 0; k < dj; k++) {
		if (s.get(i - k) == 0)
			return false;
	}
	return s.get(i - dj) != 1;
}

void LineSolver::paint(int i, int j, Byte remain) {
	if (i <= 0)
		return;
	paintP(i, j, remain);
}

void LineSolver::paintP(int i, int j, Byte remain) {
	bool f0 = fix0(i, j, remain), f1 = fix1(i, j, remain);
	if (f0 && !f1) {
		paint0(i, j, remain);
	} else if (!f0 && f1) {
		paint1(i, j, remain);
	} else {
		Line t = Line(s);
		LineSolver solverT = LineSolver(t, d);

		solverT.paint0(i, j, remain);
		this->paint1(i, j, remain);
		merge(s, t, i);
	}
}

void LineSolver::paint0(int i, int j, Byte remain) {
	s.set(i, 0);
	paint(i - 1, j, remain);
}

void LineSolver::paint1(int i, int j, Byte remain) {
	int dj = d[j];
	for (int k = 0; k < dj; k++) {
		s.set(i - k, 1);
	}
	s.set(i - dj, 0);
	paint(i - dj - 1, j - 1, remain - dj - 1);
}

void LineSolver::merge(Line& s, Line& t, int i) {
	for (int k = 1; k <= i; k++) {
		if (s.get(k) != t.get(k))
			s.set(k, U);
	}
}
