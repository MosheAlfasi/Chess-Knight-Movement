#include "mainFunction.h"
#include "Q1.h"
#include <stdlib.h>

/* This function build and return a two dimensional array,
every cabin in the array is a pointer of array that include
the possible steps of a knight from this position*/
chessPosArray*** validKnightMoves()
{
	chessPosArray*** ValidKnightMovesFromAnyCell;
	int col, row, i, j, logZise;

	ValidKnightMovesFromAnyCell = (chessPosArray***)malloc(sizeof(chessPosArray**) * BOARD_ROWS);
	checkAllocation(ValidKnightMovesFromAnyCell); 

	for (col = 0; col < BOARD_ROWS; col++)
	{
		ValidKnightMovesFromAnyCell[col] = (chessPosArray**)malloc(sizeof(chessPosArray*) * BOARD_COLS); 
		checkAllocation(ValidKnightMovesFromAnyCell[col]);
	}

	for (row = 0; row < BOARD_ROWS; row++)
		for (col = 0; col < BOARD_COLS; col++)
		{
			chessPosArray* validKnightMoves;
			validKnightMoves = (chessPosArray*)malloc(sizeof(chessPosArray));  
			checkAllocation(validKnightMoves);

			validKnightMoves->size = 8;
			validKnightMoves->position = (chessPos*)malloc((validKnightMoves->size) * sizeof(chessPos));
			checkAllocation(validKnightMoves->position);
			logZise = 0;

			/* 2 LEFT, 1 DOWN (possible 1) */
			i = row + 1; j = col - 2;
			if (i >= 0 && i <= BOARD_ROWS - 1 && j >= 0 && j <= BOARD_COLS - 1)
			{
				insertPosToArray(validKnightMoves->position, logZise, i, j);
				logZise++;
			}

			/* 1 LEFT, 2 DOWN (possible 2) &
			1 RIGHT, 2 DOWN (possible 3)	*/
			i = row + 2;
			for (j = col - 1; j <= col + 1; j = j + 2)
				if (i >= 0 && i <= BOARD_ROWS - 1 && j >= 0 && j <= BOARD_COLS - 1)
				{
					insertPosToArray(validKnightMoves->position, logZise, i, j);
					logZise++;
				}

			/* 2 RIGHT, 1 DOWN (possible 4) &
			2 RIGHT, 1 UP (possible 5) */
			j = col + 2;
			for (i = row + 1; i >= row - 1; i = i - 2)
				if (i >= 0 && i <= BOARD_ROWS - 1 && j >= 0 && j <= BOARD_COLS - 1)
				{
					insertPosToArray(validKnightMoves->position, logZise, i, j);
					logZise++;
				}

			/* 1 RIGHT, 2 UP (possible 6) &
			1 LEFT, 2 UP (possible 7) */
			i = row - 2;
			for (j = col + 1; j >= col - 1; j = j - 2)
				if (i >= 0 && i <= BOARD_ROWS - 1 && j >= 0 && j <= BOARD_COLS - 1)
				{
					insertPosToArray(validKnightMoves->position, logZise, i, j);
					logZise++;
				}

			/* 2 LEFT, 1 UP (possible 8) */
			i = row - 1; j = col - 2;
			if (i >= 0 && i <= BOARD_ROWS - 1 && j >= 0 && j <= BOARD_COLS - 1)
			{
				insertPosToArray(validKnightMoves->position, logZise, i, j);
				logZise++;
			}

			validKnightMoves->position = (chessPos*)realloc(validKnightMoves->position, logZise * sizeof(chessPos));
			validKnightMoves->size = logZise;

			ValidKnightMovesFromAnyCell[row][col] = validKnightMoves;
		}

	return ValidKnightMovesFromAnyCell;
}

/* This function insert possible position to the array */
void insertPosToArray(chessPos* position, int i, int row, int col)
{
	position[i][0] = 'A' + row;
	position[i][1] = '1' + col;
}


void freeQ1(chessPosArray*** arr)
{
	int i, j, k;

	for (i = 0; i < BOARD_ROWS; i++)       
	{
		for (j = 0; j < BOARD_COLS; j++)
		{
			free(arr[i][j]->position);    /*free every position in any cell*/
			free(arr[i][j]);             /* Free every struct in any cel */
		}
	}

	for (i = 0; i < BOARD_ROWS; i++)        /*free ROWS*/
	{
		free(arr[i]);
	}

	free(arr);                 /*free arr*/
}




