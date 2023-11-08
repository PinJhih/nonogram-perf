#include <cstdio>
#include <ctime>

#include "solver/board_solver.h"

#define GRN_BOLD "\x1b[;32;1m"
#define YEL_BOLD "\x1b[;33;1m"
#define RED_BOLD "\x1b[;31;1m"
#define RESET "\x1b[0;m"

int readPuzzle(FILE* input, Description d[BOARD_SIZE * 2]) {
	int t;
	if (fscanf(input, "$%d\n", &t) == EOF)
		return -1;

	char buffer[64];
	for (int i = BOARD_SIZE; i < 2 * BOARD_SIZE; i++) {
		fgets(buffer, sizeof(buffer), input);
		d[i] = Description(buffer);
	}

	for (int i = 0; i < BOARD_SIZE; i++) {
		fgets(buffer, sizeof(buffer), input);
		d[i] = Description(buffer);
	}
	return t;
}

bool check(Board& g, Description* d) {
	for (int i = 1; i <= BOARD_SIZE; i++) {
		Byte m = 0, n = 0;
		Byte row[15], col[15];
		Byte r = 0, c = 0;

		for (int j = 1; j <= BOARD_SIZE; j++) {
			if (g.get(i, j) == 1)
				r++;
			if (r != 0 && (j == 25 || g.get(i, j) == 0)) {
				row[m] = r, r = 0;
				m++;
			}

			if (g.get(j, i) == 1)
				c++;
			if (c != 0 && (j == 25 || g.get(j, i) == 0)) {
				col[n] = c, c = 0;
				n++;
			}
		}

		if (m != d[i - 1].size() || n != d[i + 24].size())
			return false;

		for (int k = 1; k <= d[i - 1].size(); k++) {
			if (row[k - 1] != d[i - 1][k])
				return false;
		}

		for (int k = 1; k <= d[i + 24].size(); k++) {
			if (col[k - 1] != d[i + 24][k])
				return false;
		}
	}
	return true;
}

int main(int argc, char* argv[]) {
	const char* path = nullptr;
	if (argc == 1) {
		path = "input.txt";
	} else if (argc == 2) {
		path = argv[1];
	} else {
		fprintf(stderr, "Error: Unknow usage\n");
		return 1;
	}

	FILE* file = fopen(path, "r");
	while (true) {
		Description d[BOARD_SIZE * 2];
		int t = readPuzzle(file, d);
		if (t == -1)
			break;

		Board g = Board();
		BoardSolver solver = BoardSolver(d);
		clock_t start = clock();
		solver.solve(g);
		clock_t end = clock();

		printf(YEL_BOLD "Case " RESET);
		printf("%d: ", t);
		switch (g.getState()) {
			case INCOMPLETE:
				printf("Incomplete...\n");
				break;
			case SOLVED:
				printf("Solved.\n");
				break;
			default:
				printf("Conflict!\n");
		}
		g.print();

		if (check(g, d))
			printf(GRN_BOLD "AC" RESET);
		else
			printf(RED_BOLD "WA" RESET);

		double runningTime = (double)(end - start) / CLOCKS_PER_SEC;
		printf(" - %.4f sec.\n\n", runningTime);
	}
	return 0;
}
