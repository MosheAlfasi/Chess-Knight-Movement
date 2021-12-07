#ifndef __Q1_H
#define __Q1_H


#include "mainFunction.h"

chessPosArray*** validKnightMoves();
void insertPosToArray(chessPos* position, int i, int row, int col);
void freeQ1(chessPosArray*** arr);








#endif