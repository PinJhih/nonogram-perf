#include <cstdio>
#include <ctime>

#include "solver/board_solver.h"

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
		double runningTime = (double)(end - start) / CLOCKS_PER_SEC;

		printf("Case %d: ", t);
		switch (g.getState()) {
			case INCOMPLETE:
				printf("Incomplete...\n");
				g.print();
				break;
			case SOLVED:
				printf("Solved.\n");
				g.print();
				break;
			default:
				printf("Conflict!\n\n");
		}
		printf("Running Time: %.4f sec.\n\n", runningTime);
	}

	return 0;
}
