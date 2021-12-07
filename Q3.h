#ifndef __Q3_H
#define __Q3_H

#include "mainFunction.h"
#include <stdbool.h>




pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
void resetArr(bool arrFlag[][BOARD_COLS]);
void getTheRealRowAndColNumbers(int* rowNum, int* colNum, char rowChar, char colChar);
void findAllPossibleKnightPathsHelper(treeNode* node, bool arrFlag[][BOARD_COLS], chessPosArray*** validMoveFromAnyCell);
treeNode* createNewTNode(chessPos data, treeNodeListCell* NodeListCell);
treeNodeListCell* createNewListCell(treeNode* node, treeNodeListCell* next);
void freeQ3(treeNode* root);

#endif