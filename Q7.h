
#ifndef __Q7_H
#define __Q7_H

#include "mainFunction.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void ProgramManager();
void getStartingPosition(chessPos StartingPosition);
int Menu();
void printMessage(int status);
char* getName();
void freeProject(bool arrStatus[], treeNode* root, chessPosList* List, char* file_name_to_write, char* file_name_to_read);





#endif