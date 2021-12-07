#include "mainFunction.h"
#include "Q4.h"
#include "Q3.h"
#include <stdlib.h>
#include <stdbool.h>

/*the function find Knight Path that Covering All Board*/
chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree)
{
	chessPosList* List_cover_all_board;
	chessPosCell* curr;

	List_cover_all_board = (chessPosList*)malloc(sizeof(chessPosList));
	checkAllocation(List_cover_all_board);
	makeEmptyList(List_cover_all_board);

	List_cover_all_board->head = findList(path_tree->node, 1);   /*finds a path*/

	if (List_cover_all_board->head == NULL)       /*if there is no path that cover all board*/
	{
		free(List_cover_all_board);
		List_cover_all_board = NULL;
	}
	else                        /*if there is path that cover all board*/
		findTail(List_cover_all_board);           /*find tail, and save it in List->tail */

	return List_cover_all_board;
}

/* Making a new empty chessPosList*/
void makeEmptyList(chessPosList* lst)
{
	lst->head = lst->tail = NULL;
}

/*Recursive function that finds a path that cover all board and make list of the path.
input - node from the tree, level (range- 1 to BOARD_COLS*BOARD_ROWS)
output -head of list */
chessPosCell* findList(treeNode* node, int level)
{
	chessPosCell* cell;
	treeNodeListCell* curr = node->next_possible_positions;

	cell = createNewListNode(node->position, NULL);      /*make new list node*/

	if (level == BOARD_COLS * BOARD_ROWS) /* if We finished - We reached level BOARD_COLS*BOARD_ROWS in tree, i.e we covered the entire board*/
		return cell;

	else
	{
		while (curr != NULL)
		{
			cell->next = findList(curr->node, level + 1);

			if (cell->next == NULL)     /* the recursive function did not found a path.*/
				curr = curr->next;
			else                        /* the recursive function found a path*/
				return cell;
		}
		/* we did not found path */
		free(cell);
		return NULL;
	}
}

/*Finds a tail in the list, and saves it in List->tail*/
void findTail(chessPosList* List)
{
	chessPosCell* curr = List->head;

	while (curr->next != NULL)
		curr = curr->next;

	List->tail = curr;
}

/*createint new chessPosCell */
chessPosCell* createNewListNode(chessPos data, chessPosCell* next)
{
	chessPosCell* res;
	res = (chessPosCell*)malloc(sizeof(chessPosCell));
	checkAllocation(res);

	res->position[0] = data[0];
	res->position[1] = data[1];
	res->next = next;

	return res;
}


void freeQ4_Q6(chessPosList* List)      /*free list*/
{
	chessPosCell* curr;
	chessPosCell* saver;

	if (List == NULL)
		return;

	curr = List->head;

	while (curr != NULL)
	{
		saver = curr;
		curr = curr->next;
		free(saver);
	}
	free(List);
}