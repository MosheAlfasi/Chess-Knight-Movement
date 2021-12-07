#include "mainFunction.h"

#include <stdio.h>
#include <stdlib.h>


/* This function check if there is allocation */
void checkAllocation(void* p)
{
	if (p == NULL)
	{
		printf("Allocation Falied");
		exit(1);
	}
}

/* This function tests the success of opening a file  */
void checkFileOpen(FILE* fp)
{
	if (fp == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}
}