/**
* Demonstrates how to use the counters of the board
**/
#include "stdafx.h"

int _tmain ( int /*argc*/, _TCHAR* /*argv[]*/ )
{
	INT returnValue = 0;
	HANDLE boardHandle = NULL;
	BYTE counterIndex = 0;
	ULONG readValue = 0;
	WORD reloadValue = 0;

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
	printf("* Counter sample. \n");
	printf("* Since there is 3 counter on the board, you can choose the one you want.\n");
	printf("* We enable the interrupt so you will receive an interrupt each time \n");
	printf("* the counter reach is reload value. \n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n\n");

	/* set the interrupt routine */
	returnValue = i_PCI1500_SetBoardIntRoutine(boardHandle, InterruptRoutine);
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_SetBoardIntRoutine \n", returnValue);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	printf("i_PCI1500_SetBoardIntRoutine : successful\n");

	/* ask the counter index */
	ReadUlong("Enter the index of the counter you want to use (0-2) :", 0,2,&readValue);
	counterIndex = (BYTE)readValue;

	/* ask the reload value */
	ReadUlong("Enter the reload value of the counter (1-65535) :",1,65535, &readValue);
	reloadValue = (WORD)readValue;

	/* init the selected counter */
	switch( counterIndex )
	{
		case 0:
			returnValue = i_PCI1500_InitTimerCounter1(boardHandle,
				PCI1500_COUNTER,
				reloadValue,
				1,	/* after having reach 0, continue */
				1);	/* enable interrupt */
			break;
		case 1:
			returnValue = i_PCI1500_InitTimerCounter2(boardHandle,
				PCI1500_COUNTER,
				reloadValue,
				1,	/* after having reach 0, continue */
				0,	/* no hardware trigger */
				0,	/* no hardware gate */
				1);	/* enable interrupt */
			break;
		case 2:
			returnValue = i_PCI1500_InitWatchdogCounter3(boardHandle,
				PCI1500_COUNTER,
				reloadValue,
				1,	/* after having reach 0, continue */
				0,	/* no hardware gate */
				1);	/* enable interrupt */
			break;
	}
	if ( returnValue != 0 )
	{
		printf("Error %d in init counter \n", returnValue);
		i_PCI1500_ResetBoardIntRoutine(boardHandle);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	else
	{
		printf("init counter : successful\n");
	}

	/* start the counter */
	switch ( counterIndex )
	{
		case 0:
			returnValue = i_PCI1500_StartTimerCounter1(boardHandle);
			break;
		case 1:
			returnValue = i_PCI1500_StartTimerCounter2(boardHandle);
			break;
		case 2:
			returnValue = i_PCI1500_StartWatchdogCounter3(boardHandle);
			break;
	}
	if ( returnValue != 0 )
	{
		printf("Error %d in start counter \n", returnValue);
		i_PCI1500_ResetBoardIntRoutine(boardHandle);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	else
	{
		printf("start counter : successful\n");
	}

	printf("Hit a key to exit the sample. \n");
	for (;;)
	{
		WORD value = 0;
		Sleep(100);

		/* does the user hit a key ? */
		if ( _kbhit() )
		{
			_getch();
			break;
		}

		/* read counter value */
		switch( counterIndex )
		{
			case 0:
				returnValue = i_PCI1500_ReadTimerCounter1(boardHandle, &value);
				break;
			case 1:
				returnValue = i_PCI1500_ReadTimerCounter2(boardHandle, &value);
				break;
			case 2:
				returnValue = i_PCI1500_ReadWatchdogCounter3(boardHandle, &value);
				break;
		}
		if ( returnValue != 0 )
		{
			printf("Error %d in read counter value \n", returnValue);
			i_PCI1500_ResetBoardIntRoutine(boardHandle);
			i_PCI1500_CloseBoard(boardHandle);
			_getch();
			return -1;
		}
		printf("Counter : %d		 \r", (int)value);
	}

	/* stop the counter */
	switch( counterIndex )
	{
		case 0:
			returnValue = i_PCI1500_StopTimerCounter1(boardHandle);
			break;
		case 1:
			returnValue = i_PCI1500_StopTimerCounter2(boardHandle);
			break;
		case 2:
			returnValue = i_PCI1500_StopWatchdogCounter3(boardHandle);
			break;
	}
	if ( returnValue != 0 )
	{
		printf("Error %d in stop counter \n", returnValue);
	}
	else
	{
		printf("stop counter : successful\n");
	}

	/* reset the interrupt routine */
	returnValue = i_PCI1500_ResetBoardIntRoutine(boardHandle);
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_ResetBoardIntRoutine \n", returnValue);
	}
	else
	{
		printf("i_PCI1500_ResetBoardIntRoutine : successful\n");
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

