#ifndef __Q4_H
#define __Q4_H

#include "mainFunction.h"
#include "Q3.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
void makeEmptyList(chessPosList* lst);
chessPosCell* findList(treeNode* node, int level);
void findTail(chessPosList* List);
chessPosCell* createNewListNode(chessPos data, chessPosCell* next);
void freeQ4_Q6(chessPosList* List);

#endif