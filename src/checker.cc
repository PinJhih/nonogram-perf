#include <cstdio>
#include <cstring>

#include "puzzle/description.h"

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

bool check(char b[25][64], Description* d) {
	for (int i = 0; i < 25; i++) {
		int m = 0, n = 0;
		Byte row[15], col[15];
		Byte r = 0, c = 0;

		for (int j = 0; j < 25; j++) {
			if (b[i][j * 2] == '1') {
				r++;
			}
			if (r != 0 && (b[i][j * 2] == '0' || j == 24)) {
				row[m] = r, r = 0;
				m++;
			}

			if (b[j][i * 2] == '1') {
				c++;
			}
			if (c != 0 && (b[j][i * 2] == '0' || j == 24)) {
				col[n] = c, c = 0;
				n++;
			}
		}

		for (int k = 0; k < d[i].size(); k++) {
			if (row[k] != d[i][k + 1])
				return false;
		}

		for (int k = 0; k < d[i + 25].size(); k++) {
			if (col[k] != d[i + 25][k + 1])
				return false;
		}
	}

	return true;
}

int main() {
	int t;
	double time, total = 0;
	char state[16];
	char board[25][64];
	FILE* file = fopen("input.txt", "r");
	while (scanf("\nCase %d: %s.\n", &t, state) != EOF) {
		fgets(board[0], sizeof(char) * 50, stdin);
		for (int i = 0; i < 25; i++) {
			fgets(board[i], sizeof(char) * 64, stdin);
		}
		scanf("\nRunning Time: %lf sec.", &time);
		total += time;

		printf(YEL_BOLD "\nCase %d", t);
		printf(RESET ": %s\n", state);
		for (int i = 0; i < 25; i++) {
			printf("%s", board[i]);
		}

		Description d[50];
		readPuzzle(file, d);
		printf("Check Answer: ");
		if (check(board, d)) {
			printf(GRN_BOLD "AC\n" RESET);
		} else {
			printf(RED_BOLD "WA\n" RESET);
		}
		printf("Running Time: %.3lf s.\n", time);
	}

	printf("\nTotal Running Time: %.4lf s.\n", total);
}
