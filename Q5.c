#define _CRT_SECURE_NO_WARNINGS

#include "mainFunction.h"
#include "Q5.h"
#include "Q3.h"
#include <stdlib.h>
#include <stdio.h>
 
/*The function gets the name of a binary file and a list of places and saves them in a binary file 
according to the instructions in the exercise */
void saveListToBinFile(char* file_name, chessPosList* pos_list)   
{
	short int numOfPosition;
	FILE* fpB; 
	BYTE tempArr[3] , mask;
	int* numbersFromPositions, i, numCellTempArrWeUseWith = 0;

	fpB = fopen(file_name, "wb");
	checkFileOpen(fpB);

	numOfPosition = countLenList(pos_list);                  /*Count how many nodes are on the list*/
	fwrite(&numOfPosition, sizeof(short int), 1, fpB);        /*write that number to th file*/

	numOfPosition *= 2;                                      /*every position is 2 Letters*/

	numbersFromPositions = (int*)malloc(sizeof(int) * numOfPosition);    
	checkAllocation(numbersFromPositions);

	dataFromLstToArr(pos_list, numbersFromPositions);        /*Convert the data from list to array*/

	resetTempArr(tempArr);                                   /*reset the temp arr (with 0)*/

	for (i = 0; i < numOfPosition ; i++)
	{
		if (i % 8 == 0)                               /*cell 0 , 8 ... */
		{
			numCellTempArrWeUseWith++;
			mask = numbersFromPositions[i]; 
			mask = mask << 5;                       /* +++00000 */

			tempArr[0] = tempArr[0] | mask;           
		}

		if (i % 8 == 1)
		{
			mask = numbersFromPositions[i];
			mask = mask << 2;                      /* 000+++00 */

			tempArr[0] = tempArr[0] | mask;
		}

		if (i % 8 == 2)
		{
			numCellTempArrWeUseWith++;
			mask = numbersFromPositions[i];
			mask = mask >> 1;                      /* 000000++ */
			tempArr[0] = tempArr[0] | mask;

			mask = numbersFromPositions[i];
			mask = mask << 7;                      /* +0000000 */
			tempArr[1] = tempArr[1] | mask;
		}

		if (i % 8 == 3)
		{
			mask = numbersFromPositions[i];
			mask = mask << 4;                       /* 0+++0000 */
			 
			tempArr[1] = tempArr[1] | mask;
		}

		if (i % 8 == 4)
		{
			mask = numbersFromPositions[i];
			mask = mask << 1;                       /* 0000+++0 */

			tempArr[1] = tempArr[1] | mask;
		}

		if (i % 8 == 5)
		{
			numCellTempArrWeUseWith++;
			mask = numbersFromPositions[i];
			mask = mask >> 2;                      /* 0000000+ */
			tempArr[1] = tempArr[1] | mask;

			mask = numbersFromPositions[i];
			mask = mask << 6;                      /* ++000000 */
			tempArr[2] = tempArr[2] | mask;
		}

		if (i % 8 == 6)
		{
			mask = numbersFromPositions[i];
			mask = mask << 3;                     /* 00+++000 */

			tempArr[2] = tempArr[2] | mask;
		}

		if (i % 8 == 7)      // if i % 8 == 7, its mean that tha tempArr is full
		{
			mask = numbersFromPositions[i];       /* 00000+++ */

			tempArr[2] = tempArr[2] | mask;

			writeToFile(fpB, tempArr, numCellTempArrWeUseWith);      /*write the data from temp arr to file*/
			resetTempArr(tempArr);                                   /*reset the temp arr again*/
			numCellTempArrWeUseWith = 0;
		}

		if (!(i % 8 == 7) && (i == numOfPosition - 1))              // if we go over on all positions, and tempArr is not full
		{
			writeToFile(fpB, tempArr, numCellTempArrWeUseWith);      /*write the data from temp arr to file*/
			resetTempArr(tempArr);                                   /*reset the temp arr again*/
			numCellTempArrWeUseWith = 0;
		}
	}
	free(numbersFromPositions);
	fclose(fpB);
}

/*the function return the len of list */
short int countLenList(chessPosList* pos_list)
{
	short int count = 0;
	chessPosCell* curr;

	curr = pos_list->head;

	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}

	return count;
}

/*the function Convert the data from 'pos_list' to 'arr'*/
void dataFromLstToArr(chessPosList* pos_list, int* arr)
{
	int i = 0;
	chessPosCell* curr = pos_list->head;
	while (curr != NULL)
	{
		getTheRealRowAndColNumbers(&(arr[i]), &(arr[i + 1]), curr->position[0], curr->position[1]);
		i += 2;
		curr = curr->next;
	}
}

/*the function reset the temp arr with 0 */
void resetTempArr(BYTE tempArr[])
{
	tempArr[0] = 0; 
	tempArr[1] = 0; 
	tempArr[2] = 0;
}

/*the function write the data from tempArr to the file */
void writeToFile(FILE* fp, BYTE tempArr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		fwrite(&tempArr[i], sizeof(BYTE), 1, fp);
	}
}