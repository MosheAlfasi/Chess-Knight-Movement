#ifndef __Q6_H
#define __Q6_H

#include "mainFunction.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"

#include <stdbool.h>


int checkAndDisplayPathFromFile(char* fileName);
void readFromFileToArr(FILE* fpOfPosition, chessPosArray* arr);
chessPosList* makeListFromArray(chessPosArray* arr);
bool isLegalPath(chessPosList* List);
bool isLegalStep(chessPosCell* step, chessPosCell* nextStep);
bool checkIfPathCoverAllBoard(chessPosCell* head);
void insertDataToEndList(chessPosList* lst, chessPos data);
void insertNodeToEndList(chessPosList* lst, chessPosCell* tail);
bool isEmptyList(chessPosList* lst);
int checkFileOpenQ6(FILE* fp);



#endif