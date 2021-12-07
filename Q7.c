#define _CRT_SECURE_NO_WARNINGS

#include "mainFunction.h"
#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"
#include "Q6.h"
#include "Q7.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


void ProgramManager()
{
	int choice = 0;                              /*user choice*/
	chessPos StartingPosition;
	pathTree tree;
	chessPosList* pathCoverAllBoard = NULL;
	bool optionsActivatedArr[5] = { false, false, false, false, false };                 /*A boolean array that keeps within which Options have been activated, optionsActivatedArr[0] is to option 1 .. optionsActivatedArr[4] is to option 5 */
	char* file_name_to_read = NULL;
	char* file_name_to_write = NULL;
	int status;

	tree.node = NULL;

	while (choice != 6)                        /*while the user does not want to exit*/
	{
		choice = Menu();                       /*print a menue and get choice from user*/

		switch (choice)
		{
		case 1:

			getStartingPosition(StartingPosition);   /* get Starting Position from user*/

			if (optionsActivatedArr[0] != false)          /*evert time that uset insert new position' we free all memory and Start from the beginning. except if this is the first time*/
				freeProject(optionsActivatedArr, tree.node, pathCoverAllBoard, file_name_to_write, file_name_to_read);

			optionsActivatedArr[0] = true;           /*Option 1 activated */
			optionsActivatedArr[1] = false;          /*Each time the user types in a new starting position, we reset the optionsActivatedArr array */
			optionsActivatedArr[2] = false;
			optionsActivatedArr[3] = false;
			optionsActivatedArr[4] = false;
			break;
		case 2:
			if (optionsActivatedArr[0] == false)             /*if we didnt get a position yet*/
			{
				printf("Please enter a location in option 1 first.\n");
			}
			else /* If we have already a position */
			{
				tree = findAllPossibleKnightPaths(&StartingPosition);
				optionsActivatedArr[1] = true;
			}
			break;

		case 3:
		case 4:
			if (optionsActivatedArr[0] == false)                                   /*if we didnt get a position yet*/
				printf("Please enter a Starting position in option 1 first.\n");

			else                                                                   /* If we already get a position*/
			{
				if (optionsActivatedArr[2] == false)                               /*If option 3 has not yet been activated */
				{
					if (optionsActivatedArr[1] == false)                           /*If option 2 has not yet been activated */
					{
						tree = findAllPossibleKnightPaths(&StartingPosition);      /*perform option 2*/
						optionsActivatedArr[1] = true;
					}

					pathCoverAllBoard = findKnightPathCoveringAllBoard(&tree);     /*perform option 3*/
					optionsActivatedArr[2] = true;
					if (pathCoverAllBoard == NULL && choice != 4)                       /* If there is no path that cover the all board */
						printf("\n\n There is no path that cover all the board \n\n");
				}

				if (choice == 4)
				{
					if (pathCoverAllBoard != NULL)                   /* If there is a path all over the board */
					{
						file_name_to_write = getName();                       /* get name of file from user */
						saveListToBinFile(file_name_to_write, pathCoverAllBoard);     /*perform option 4, save data to bin file*/
						optionsActivatedArr[3] = true;
					}
					else                   /* If there is no path that cover the all board */
						printf("\n\n There is no path that cover all the board \n\n");
				}
			}
			break;

		case 5:
			file_name_to_read = getName();                                 /* get name of file from user */
			status = checkAndDisplayPathFromFile(file_name_to_read);       /*perform option 5*/
			printMessage(status);                                  /* print a massage according to 'status' ( -1, 1, 2, 3)*/
			optionsActivatedArr[4] = true;
			break;
		}
	}
	freeProject(optionsActivatedArr, tree.node, pathCoverAllBoard, file_name_to_write, file_name_to_read);

}

/*print Menu, and get a chice*/
int Menu()
{
	char choice = '0', temp;
	printf("******************************************************\n");
	printf("* HELLO! Please select one of the options:           *\n\n");
	printf("* 1. Enter a knight's starting position.             *\n\n* 2. Create all possible knight paths.               *\n\n* 3. Find a knight path covering all board.          *\n\n* 4. Save knight path covering all board to file.    *\n\n* 5. Load and display path from file.                *\n\n* 6. Exit.                                           *");
	printf("\n");
	printf("******************************************************\n");


	while (choice < '1' || choice > '6')
	{
		fseek(stdin, 0, SEEK_END);
		printf("please enter number between 1 to 6\n");
		choice = getchar();                                  /*get the char*/
		temp = getchar();                                    /*get the next char*/

		if (temp != ' ' && temp != '\n')                      /*if the temp is not ' ' or '\n',The input is incorrect for sure */
			choice = '0';

		fseek(stdin, 0, SEEK_END);
	}

	return (int)(choice - '0');
}

/* the function get getStarting position from user */
void getStartingPosition(chessPos StartingPosition)
{
	char row, col;

	StartingPosition[0] = '\0';
	StartingPosition[1] = '\0';

	printf("please enter ROW:\n");

	while (StartingPosition[0] == '\0')
	{
		fseek(stdin, 0, SEEK_END);

		scanf("%c", &row);

		if (row < 'A' || row >((BOARD_ROWS + 'A') - 1))      /*row number not in range*/
		{
			printf("please enter valid row:\n");
		}
		else
			StartingPosition[0] = row;
	}

	printf("please enter COL:\n");
	while (StartingPosition[1] == '\0')
	{
		fseek(stdin, 0, SEEK_END);
		scanf("%c", &col);
		if (col < '1' || col >(BOARD_COLS + '0'))   /*col number not in range*/
		{
			printf("please enter valid col:\n");
		}
		else
			StartingPosition[1] = col;
	}

}


/* get name of file from user */
char* getName()
{
	char* str;
	int phz_size = 1, log_size = 0;
	char ch;

	str = (char*)malloc(sizeof(char) * phz_size);
	checkAllocation(str);
	fseek(stdin, 0, SEEK_END);

	printf("please insert the name of file: \n");
	ch = getchar();

	while (ch != ' ' && ch != '\n')
	{
		if (log_size == phz_size)
		{
			phz_size *= 2;
			str = (char*)realloc(str, phz_size);
			checkAllocation(str);
		}
		str[log_size] = ch;
		log_size++;
		ch = getchar();
	}
	str = (char*)realloc(str, log_size+1);
	checkAllocation(str);
	str[log_size] = '\0';

	return str;
}

/* print a massage according to 'status' ( -1, 1, 2, 3)*/
void printMessage(int status)
{
	if (status == -1)
	{
		printf("\nError, the file you tried to open does not exist\n");
	}
	else if (status == 1)
	{
		printf("\nThe knight's path is invalid\n");
	}
	else if (status == 2)
	{
		printf("\nThe path covers the entire board\n");
	}
	else if (status == 3)
	{
		printf("\nThe Knight's path does not cover the entire board\n");
	}
	printf("\n");
	return;
}


/* free the all project - only what is necessary */
void freeProject(bool arrStatus[], treeNode* root, chessPosList* List, char* file_name_to_write, char* file_name_to_read)
{
	if (arrStatus[1] == true)      /* case 2 - Q3FREE */
		freeQ3(root);              /* include freeQ1 */

	if (arrStatus[2] == true)      /* case 3 - Q4FREE */
		freeQ4_Q6(List);

	if (arrStatus[3] == true)
		free(file_name_to_write);

	if (arrStatus[4] == true)      /* case 5 */
		free(file_name_to_read);
}