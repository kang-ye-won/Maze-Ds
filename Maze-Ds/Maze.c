#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_ARRAY_SIZE 15
#define FALSE 0
#define TRUE 1
void path(void);
typedef struct {
	short int vert;
	short int horiz;
}offset;
typedef struct {
	int row;
	int col;
	int dir;
}element;
offset move[8] = {
 {-1, 0},
 {-1, 1},
 {0, 1},
 {1, 1},
 {1, 0},
 {1, -1},
 {0, -1},
 {-1, -1}
};
element stack[MAX_STACK_SIZE];
int top = -1;
int EXIT_ROW, EXIT_COL;
int maze[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
int mark[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE];
void stackFull() {
	fprintf(stderr, "stack is full, cannot add element");
	exit(EXIT_FAILURE);
}
element stackEmpty() {
	fprintf(stderr, "stack is empty, cannot delete element");
	element empty;
	empty.row = -1; empty.col = -1; empty.dir = -1;
	return empty;
}
void push(element item) {
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}
element pop() {
	if (top == -1)
		return stackEmpty();
	return stack[top--];
}
int main() {
	int n, m, i, j, k;
	printf("Enter the row col :");
	scanf("%d", &n);
	scanf("%d", &m);
	for (i = 0; i <= m + 2; i++) {
		maze[0][i] = 1;
		maze[n + 1][i] = 1;
	}
	for (i = 0; i <= n + 2; i++) {
		maze[i][0] = 1;
		maze[i][m + 1] = 1;
	}

	printf("Enter the maze :\n");
	for (i = 1; i < n + 1; i++) {
		for (j = 1; j < m + 1; j++) {
			scanf("%d", &maze[i][j]);
		}
	}
	EXIT_ROW = n;
	EXIT_COL = m;

	for (i = 0; i < 8; i++) {
		for (j = 1; j < n + 1; j++) {
			for (k = 1; k < m + 1; k++) {
				mark[j][k] = 0;
			}
		}
		path(i);
	}
}
void path(int d) {
	int i, j, row, col, dir, nextRow, nextCol, check, found = FALSE;
	mark[1][1] = 1; top = 0; int count = 0;
	element position;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = d;
	while (top > -1 && !found) {
		position = pop(&top);
		row = position.row; col = position.col;
		dir = position.dir;
		++count;
		check = 0;
		while (dir < 8 && !found && check < 9) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
				found = TRUE;
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row; position.col = col;
				if (dir == 7) {
					dir = 0;
					position.dir = dir;
				}
				else {
					position.dir = ++dir;
				}
				push(position);
				row = nextRow; col = nextCol; dir = d;
				check = 0;
			}
			else {
				if (dir == 7) {
					dir = 0;
					++check;
				}
				else {
					++dir;
					++check;
				}
			}
		}
	}
	if (found) {
		printf("The path is (%d direction) :\n", d);
		printf("(row,col)");
		for (i = 0; i <= top; i++)
			printf("(%d,%d)", stack[i].row, stack[i].col);
		printf("(%d,%d)", row, col);
		printf("(%d,%d)\n", EXIT_ROW, EXIT_COL);
		printf("The total number of backtrack(%d direction): %d \n", d, count - 1);
		printf("\n");
	}
	else {
		printf("The maze does not have a path\n");
	}
}