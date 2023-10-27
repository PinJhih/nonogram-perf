#include "solver/line_solver.h"

bool LineSolver::fix(int i, int j) {
	if (i < -1)
		return false;

	if (i == 0 || i == -1) {
		if (j == 0)
			return true;
		return false;
	}

	return fix0(i, j) || fix1(i, j);
}

bool LineSolver::fix0(int i, int j) {
	if (s.get(i) == 0 || s.get(i) == U)
		return fix(i - 1, j);
	return false;
}

bool LineSolver::fix1(int i, int j) {
	if (j <= 0)
		return false;
	int dj = d[j];
	if (i - dj < 0)
		return false;

	if (matchSigma(i, dj))
		return fix(i - dj - 1, j - 1);
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

void LineSolver::paint(int i, int j) {
	if (i <= 0)
		return;
	paintP(i, j);
}

void LineSolver::paintP(int i, int j) {
	bool f0 = fix0(i, j), f1 = fix1(i, j);
	if (f0 && !f1) {
		paint0(i, j);
	} else if (!f0 && f1) {
		paint1(i, j);
	} else {
		Line t = Line(s);
		LineSolver solverT = LineSolver(t, d);

		solverT.paint0(i, j);
		this->paint1(i, j);
		merge(s, t, i);
	}
}

void LineSolver::paint0(int i, int j) {
	s.set(i, 0);
	paint(i - 1, j);
}

void LineSolver::paint1(int i, int j) {
	int dj = d[j];
	for (int k = 0; k < dj; k++) {
		s.set(i - k, 1);
	}
	s.set(i - dj, 0);
	paint(i - dj - 1, j - 1);
}

void LineSolver::merge(Line& s, Line& t, int i) {
	for (int k = 1; k <= i; k++) {
		if (s.get(k) != t.get(k))
			s.set(k, U);
	}
}
