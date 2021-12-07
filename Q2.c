#define _CRT_SECURE_NO_WARNINGS

#include "mainFunction.h"
#include "Q2.h"
#include "Q3.h"
#include <stdlib.h>
#include <stdio.h>

/* This function get a list of positions on the board,
the function delete the position from the list repetitive positions,
and print a board with the positions from the list according
their location at the list */
void display(chessPosList* lst)
{
	int counter = 0, row, col;
	int arr[BOARD_ROWS][BOARD_COLS];
	chessPosCell* curr = lst->head;
	chessPosCell* lastCurr = NULL;

	/* Here we puts zero all over the board */
	putZeroInArray(arr, BOARD_ROWS, BOARD_COLS);

	while (curr != NULL)
	{
		getTheRealRowAndColNumbers(&row, &col, curr->position[0], curr->position[1]);

		/* We check if this position is repetitive */
		if (arr[row][col] == 0)
		{
			counter++;
			arr[row][col] = counter;
			lastCurr = curr;
			curr = curr->next;
		}
		else
		{
			deleteNodeFromList(lst, curr, lastCurr);
			curr = lastCurr->next;
		}
	}

	PrintBoard(arr, BOARD_ROWS, BOARD_COLS);
}

/* This function puts zero all over the board */
void putZeroInArray(int arr[][BOARD_COLS], int SizeOfRow, int SizeOfCol)
{
	int i, j;
	for (i = 0; i < SizeOfRow; i++)
		for (j = 0; j < SizeOfCol; j++)
			arr[i][j] = 0;

}

/* This function delete node from the list */
void deleteNodeFromList(chessPosList* lst, chessPosCell* node, chessPosCell* lastCurr)
{
	chessPosCell* curr = lastCurr;

	if (lst->tail == node) /* or node->next == NULL */
	{
		lst->tail = lastCurr;
		lst->tail->next = NULL;
	}
	else
		lastCurr->next = node->next;

	free(node);
}

/* This function print the board */
void PrintBoard(int table[][BOARD_COLS], int SizeOfRow, int SizeOfCol)
{
	int i, j, k;
	int capital = 'A';

	/* Print the first row */
	for (k = 0; k <= BOARD_ROWS; k++)
		printf("----+");
	printf("\n");

	/* Print the cols number
	(1 2 3 ... 8) */
	for (k = 0; k <= BOARD_COLS; k++)
	{
		if (k != 0)
			printf("|%3d ", k);
		else
			printf("|   ");
	}
	printf("|\n");


	for (i = 0; i < BOARD_ROWS; i++)
	{
		/* Print the line between the values */
		for (k = 0; k <= BOARD_ROWS; k++)
			printf("----+");
		printf("\n");

		/* Print the correct letter of the row
		(A B C ... H) */
		printf("|%2c |", capital);
		for (j = 0; j < BOARD_COLS; j++) /* Print the table values */
			if (table[i][j] == 0)
				printf("    |");
			else
				printf("%3d |", table[i][j]);
		printf("\n");
		capital++;
	}

	/* Print the last line */
	for (k = 0; k <= BOARD_ROWS; k++)
		printf("----+");
	printf("\n");
}

