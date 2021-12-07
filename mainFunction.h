#ifndef __MAIN_H
#define __MAIN_H

#include <stdlib.h>
#include <stdio.h>

typedef char chessPos[2];

typedef struct _chessPosArray {    //Array of cells.
	unsigned int size;
	chessPos* position;
} chessPosArray;


typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;


typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;

struct treeNode;

typedef struct _treeNodeListCell
{
	struct treeNode* node;
	struct _treeNodeListCell* next;
}treeNodeListCell;

typedef struct treeNode
{
	chessPos position;
	treeNodeListCell* next_possible_positions;
}treeNode;

typedef struct _pathTree
{
	treeNode* node;
}pathTree;

typedef struct _cellHistory
{
	int size;
	char** code;
}cellHistory;

#define BOARD_ROWS 5
#define BOARD_COLS 5

void checkAllocation(void* p);
void checkFileOpen(FILE* fp);

#endif
