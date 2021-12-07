#ifndef __Q2_H
#define __Q2_H

#include "mainFunction.h"


void display(chessPosList* lst);
void putZeroInArray(int arr[][BOARD_COLS], int SizeOfRow, int SizeOfCol);
void deleteNodeFromList(chessPosList* lst, chessPosCell* node, chessPosCell* lastCurr);
void PrintBoard(int table[][BOARD_COLS], int SizeOfRow, int SizeOfCol);



#endif