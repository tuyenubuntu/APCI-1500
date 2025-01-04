/**
* Demonstrates how to use the counters of the board
* Also use the trigger functionality of the counter
**/
#include "stdafx.h"

int _tmain ( int /*argc*/, _TCHAR* /*argv[]*/ )
{
	INT returnValue = 0;
	HANDLE boardHandle = NULL;
	WORD reloadValue = 100;
	int doContinue = 1;

	/* call the util method to open a board */
	returnValue = OpenBoard(&boardHandle);
	if (returnValue != 0)
	{
		printf("Error while opening the board : %d \n", (int) returnValue);
		_getch();
		return -1;
	}

	/* display some useful informations */
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	printf("* Counter with trigger sample. \n");
	printf("* This sample uses the first counter of the board with a reload value \n");
	printf("* of 100. It doesn't use interrupt. You can exit this sample with 'Esc' \n");
	printf("* and trigger the counter with 't'.\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n\n");

	/* init the counter */
	returnValue = i_PCI1500_InitTimerCounter1(boardHandle,
		PCI1500_COUNTER,
		reloadValue,
		1,	/* after having reach 0, continue */
		0);	/* disable interrupt */
	if ( returnValue != 0 )
	{
		printf("Error %d in init counter \n", returnValue);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	else
	{
		printf("init counter : successful\n");
	}

	/* start the counter */
	returnValue = i_PCI1500_StartTimerCounter1(boardHandle);
	if ( returnValue != 0 )
	{
		printf("Error %d in start counter \n", returnValue);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	else
	{
		printf("start counter : successful\n");
	}

	while (doContinue == 1)
	{
		WORD value = 0;
		Sleep(100);

		/* does the user hit a key ? */
		if ( _kbhit() )
		{
			switch ( _getch() )
			{
				/* 't' : trigger */
				case 116:
					returnValue = i_PCI1500_TriggerTimerCounter1(boardHandle);
					if ( returnValue != 0 )
					{
						printf("Error %d in i_PCI1500_TriggerTimerCounter1 \n", returnValue);
						i_PCI1500_StopTimerCounter1(boardHandle);
						i_PCI1500_CloseBoard(boardHandle);
						_getch();
						return -1;
					}
					printf("i_PCI1500_TriggerTimerCounter1 success\n");
					break;
				/* 'esc' : exit */
				case 27:
					doContinue = 0;
					break;
			}
		}

		/* read counter value */
		returnValue = i_PCI1500_ReadTimerCounter1(boardHandle, &value);
		if ( returnValue != 0 )
		{
			printf("Error %d in read counter value \n", returnValue);
			i_PCI1500_StopTimerCounter1(boardHandle);
			i_PCI1500_CloseBoard(boardHandle);
			_getch();
			return -1;
		}
		printf("Counter : %d		 \r", (int)value);
	}

	/* stop the counter */
	returnValue = i_PCI1500_StopTimerCounter1(boardHandle);
	if ( returnValue != 0 )
	{
		printf("Error %d in stop counter \n", returnValue);
	}
	else
	{
		printf("stop counter : successful\n");
	}

	/* release the board */
	returnValue = i_PCI1500_CloseBoard(boardHandle);
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_CloseBoard \n", returnValue);
	}
	else
	{
		printf("i_PCI1500_CloseBoard : successful\n");
	}

	/* exit */
	printf("\n Press any key to exit the sample ...");
	_getch();
	return 0;
}

