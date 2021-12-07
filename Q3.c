#define _CRT_SECURE_NO_WARNINGS

#include "mainFunction.h"
#include "Q1.h"
#include "Q3.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


/* The function make tree from all possible knight paths from startingPosition
input -starting position
output - pathTree */
pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
	chessPosArray*** validMoveFromAnyCell = validKnightMoves();     /*get all movef from any cell from validKnightMoves function (Q1)*/
	pathTree pathOfTree;
	bool arrFlag[BOARD_ROWS][BOARD_COLS];                           /*bool array. size - BOARD_ROWS*BOARD_COLS */
	resetArr(arrFlag);                                              /*puts false in any cell of arrFlag */

	pathOfTree.node = createNewTNode(*startingPosition, NULL);      /* create New treeNode*/

	findAllPossibleKnightPathsHelper(pathOfTree.node, arrFlag, validMoveFromAnyCell);  /*helper that make tree from all possible knight paths from startingPosition */

	freeQ1(validMoveFromAnyCell);

	return pathOfTree;
}

/* The function reset all the cell in the array to be FALSE */
void resetArr(bool arrFlag[][BOARD_COLS])
{
	int i, j;

	for (i = 0; i < BOARD_ROWS; i++)
		for (j = 0; j < BOARD_COLS; j++)
			arrFlag[i][j] = false;
}

/* Get the real row numberand and col number of the node*/
void getTheRealRowAndColNumbers(int* rowNum, int* colNum, char rowChar, char colChar)
{
	*rowNum = (int)(rowChar - 'A');
	*colNum =(int)( colChar - '1');
}

/*Recursive function that  make tree from all possible knight paths from starting Position
input - starting Position, arrFlag, validMoveFromAnyCell array*/
void findAllPossibleKnightPathsHelper(treeNode* node, bool arrFlag[][BOARD_COLS], chessPosArray*** validMoveFromAnyCell)
{
	int rowNum, colNum;
	int numOFPotentialChildren;
	int i;
	treeNodeListCell* saver = NULL;

	getTheRealRowAndColNumbers(&rowNum, &colNum, node->position[0], node->position[1]);  /* Get the real row numberand and col number of the node*/

	numOFPotentialChildren = (validMoveFromAnyCell[rowNum][colNum])->size; /* Get the number of possible steps from the node */

	arrFlag[rowNum][colNum] = true;  /*put true in arrFlag[rowNum][colNum] - because we stepped on a cell*/

	for (i = 0; i < numOFPotentialChildren; i++)  /*Go through all the Potential children*/
	{
		int rowNumP, colNumP;

		getTheRealRowAndColNumbers(&rowNumP, &colNumP, validMoveFromAnyCell[rowNum][colNum]->position[i][0], validMoveFromAnyCell[rowNum][colNum]->position[i][1]);

		if (arrFlag[rowNumP][colNumP] == false)  /* we dont stepped on the cell*/
		{
			treeNodeListCell* newListCell;
			treeNode* newNode;

			newNode = createNewTNode(validMoveFromAnyCell[rowNum][colNum]->position[i], NULL);
			newListCell = createNewListCell(newNode, NULL);

			if (saver == NULL)          /* Check if we builded the first move fron node */
				node->next_possible_positions = newListCell;
			else
				saver->next = newListCell;   /*connect the newListCell to the list*/

			saver = newListCell;

			findAllPossibleKnightPathsHelper(newNode, arrFlag, validMoveFromAnyCell);     /*recursive call*/
		}
	}
	arrFlag[rowNum][colNum] = false;  /* put false in arrFlag[rowNum][colNum] so as not to block other bath */
}

/*create new treeNode */
treeNode* createNewTNode(chessPos data, treeNodeListCell* NodeListCell)
{
	treeNode* res;
	res = (treeNode*)malloc(sizeof(treeNode)); 
	checkAllocation(res);
	res->position[0] = data[0];
	res->position[1] = data[1];
	res->next_possible_positions = NodeListCell;
	return res;
}

/*create new treeNodeListCell */
treeNodeListCell* createNewListCell(treeNode* node, treeNodeListCell* next)
{
	treeNodeListCell* res;
	res = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkAllocation(res);

	res->node = node;
	res->next = next;

	return res;
}

/*free to Q3*/
void freeQ3(treeNode* root)
{
	if (root->next_possible_positions == NULL)    /*end of tree*/
	{
		free(root);
		return;
	}
	else
	{
		treeNodeListCell* curr = root->next_possible_positions;
		treeNodeListCell* saver;

		while (curr != NULL)                         /*go through every treeNodeListCell*/
		{
			freeQ3(curr->node);                /*recursive call*/
			saver = curr;            
			curr = curr->next;  
			free(saver);        
		}
		free(root);
	} 
}

