#define _CRT_SECURE_NO_WARNINGS

#include "mainFunction.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"
#include "Q6.h"

#include <stdbool.h>
#include <stdio.h>

/* The function get binari file with positions and return integer number :
-1 - file does'nt existent.
1 - illegal path.
2 - if the path cover the all board.
3 - if the path doesn't cover the all board.
the function delete repetitive positions and print board with the path.
*/
int checkAndDisplayPathFromFile(char* fileName)
{
	FILE* fpOfPosition;
	chessPosArray arr;
	chessPosList* List;
	short int tempS;

	fpOfPosition = fopen(fileName, "rb");
	if (checkFileOpenQ6(fpOfPosition) == -1)
		return -1;

	fread(&tempS, sizeof(short int), 1, fpOfPosition);
	arr.size = (unsigned int)tempS;

	arr.position = (chessPos*)malloc(arr.size * sizeof(chessPos));
	checkAllocation(arr.position);

	readFromFileToArr(fpOfPosition, &arr);

	fclose(fpOfPosition);

	List = makeListFromArray(&arr);

	free(arr.position);

	if (!(isLegalPath(List)))
	{
		freeQ4_Q6(List);
		return 1;
	}

	display(List);

	if (checkIfPathCoverAllBoard(List->head))
	{
		freeQ4_Q6(List);
		return 2;
	}

	freeQ4_Q6(List);
	return 3;
}

/* The function read the positions from the file to array. */
void readFromFileToArr(FILE* fpOfPosition, chessPosArray* arr)
{
	BYTE data[3];
	int indArr = 0;

	BYTE mask1 = 0xE0;	//11100000  byte 1 (most significant byte - the left most one)
	BYTE mask2 = 0x1C;	//00011100  byte 1
	BYTE mask3a = 0x03, mask3b = 0x80;	//0000001110000000 bytes 1+2 
	BYTE mask4 = 0x70;	//01110000  byte 2
	BYTE mask5 = 0x0E;	//00001110  byte 2
	BYTE mask6a = 0x01, mask6b = 0xC0;	//0000000111000000 bytes 2+3
	BYTE mask7 = 0x38;	//00111000  byte 3 (least significant byte)
	BYTE mask8 = 0x07;	//00000111	byte 3 

	int i, numOfBYTE;

	for (i = arr->size; i > 0; i -= 4)
	{

		if (i >= 4)
			fread(data, sizeof(BYTE), 3, fpOfPosition);
		else
		{
			numOfBYTE = (((i * 2) * 3) / 8) + 1;
			fread(data, sizeof(BYTE), numOfBYTE, fpOfPosition);
		}

		if (i >= 1)
		{
			arr->position[indArr][0] = ((data[0] & mask1) >> 5) + 'A';
			arr->position[indArr][1] = ((data[0] & mask2) >> 2) + '1';
			indArr++;
		}
		if (i >= 2)
		{
			arr->position[indArr][0] = (((data[0] & mask3a) << 1) | ((data[1] & mask3b) >> 7)) + 'A';
			arr->position[indArr][1] = ((data[1] & mask4) >> 4) + '1';
			indArr++;
		}
		if (i >= 3)
		{
			arr->position[indArr][0] = ((data[1] & mask5) >> 1) + 'A';
			arr->position[indArr][1] = (((data[1] & mask6a) << 2) | ((data[2] & mask6b) >> 6)) + '1';
			indArr++;
		}
		if (i >= 4)
		{
			arr->position[indArr][0] = ((data[2] & mask7) >> 3) + 'A';
			arr->position[indArr][1] = (data[2] & mask8) + '1';
			indArr++;
		}
	}
}

/* make array of possitions to list of possitions */
chessPosList* makeListFromArray(chessPosArray* arr)
{
	chessPosList* lst;
	int i;

	lst = (chessPosList*)malloc(sizeof(chessPosList));
	checkAllocation(lst);
	makeEmptyList(lst);

	for (i = 0; i < arr->size; i++)
	{
		insertDataToEndList(lst, arr->position[i]);
	}

	return lst;
}

/* the function check if the path is legal
true - legal
false - illegal
*/
bool isLegalPath(chessPosList* List)
{
	chessPosCell* curr;
	int Row, Col;
	bool legal = true;
	curr = List->head;

	getTheRealRowAndColNumbers(&Row, &Col, curr->position[0], curr->position[1]);

	if (!(Row >= 0 && Row <= BOARD_ROWS - 1 && Col >= 0 && Col <= BOARD_COLS - 1))      //check the first position
		legal = false;
	while (curr->next != NULL && legal == true)
	{
		legal = isLegalStep(curr, curr->next);
		curr = curr->next;
	}
	return legal;
}

/* the function check if the step is legal
true - legal
false - illegal
*/
bool isLegalStep(chessPosCell* step, chessPosCell* nextStep)
{
	int Row, Col, nextRow, nextCol;
	getTheRealRowAndColNumbers(&Row, &Col, step->position[0], step->position[1]);
	getTheRealRowAndColNumbers(&nextRow, &nextCol, nextStep->position[0], nextStep->position[1]);

	if ((nextRow >= 0 && nextRow <= BOARD_ROWS - 1 && nextCol >= 0 && nextRow <= BOARD_COLS - 1)
		&& ((Row == nextRow + 2) && ((Col == nextCol + 1) || (Col == nextCol - 1)))
		|| ((Row == nextRow - 2) && ((Col == nextCol + 1) || (Col == nextCol - 1)))
		|| ((Col == nextCol + 2) && ((Row == nextRow + 1) || (Row == nextRow - 1)))
		|| ((Col == nextCol - 2) && ((Row == nextRow + 1) || (Row == nextRow - 1))))
		return true;
	return false;
}

/* The function get list of positions (chessPosCell*)
and check if the path cover the all board  */
bool checkIfPathCoverAllBoard(chessPosCell* head)
{
	chessPosCell* curr;
	int row, col, count = 0;

	curr = head;

	while (curr != NULL && count != BOARD_ROWS * BOARD_COLS)
	{
		curr = curr->next;
		count++;
	}

	if (count == BOARD_ROWS * BOARD_COLS)
		return true;
	return false;

}

/* The function insert data to the end of the list */
void insertDataToEndList(chessPosList* lst, chessPos data)
{
	chessPosCell* newTail;
	newTail = createNewListNode(data, NULL);
	insertNodeToEndList(lst, newTail);
}

/* The function insert data to the end of the list */
void insertNodeToEndList(chessPosList* lst, chessPosCell* tail)
{
	if (isEmptyList(lst) == true)
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

/* The function check if the list is empty
true - empty.
false - not empty.
*/
bool isEmptyList(chessPosList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}

/* The function check if the file of Q6 is open.
true - open.
-1 not open.
*/
int checkFileOpenQ6(FILE* fp)
{
	if (fp == NULL)
	{
		return -1;
	}
}



