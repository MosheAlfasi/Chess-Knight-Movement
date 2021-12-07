#ifndef __Q5_H
#define __Q5_H

#include "mainFunction.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef unsigned char BYTE;

void saveListToBinFile(char* file_name, chessPosList* pos_list);
short int countLenList(chessPosList* pos_list);
void dataFromLstToArr(chessPosList* pos_list, int* arr);
void resetTempArr(BYTE tempArr[]);
void writeToFile(FILE* fp, BYTE tempArr[]);





#endif