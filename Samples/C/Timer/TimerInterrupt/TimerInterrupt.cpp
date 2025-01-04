/**
* Demonstrates how to use the timers of the board
**/
#include "stdafx.h"

int _tmain ( int /*argc*/, _TCHAR* /*argv[]*/ )
{
	INT returnValue = 0;
	HANDLE boardHandle = NULL;
	BYTE timerIndex = 0;
	ULONG readValue = 0;
	WORD reloadValue = 0;
	BYTE clock = 0;

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
	printf("* Timer sample. \n");
	printf("* Since there are 2 timers on the board, you can choose the one you want.\n");
	printf("* We enable the interrupt so you will receive an interrupt each time \n");
	printf("* the timer reach is reload value. \n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n\n");

	/* ask the input clock */
	ReadUlong("Select the input clock (0: 115.2kHz, 1: 3.6kHz, 2: 1.8kHz) :",0,2,&readValue);
	switch(readValue)
	{
		case 0:
			clock = PCI1500_115_KHZ;
			break;
		case 1:
			clock = PCI1500_3_6_KHZ;
			break;
		case 2:
			clock = PCI1500_1_8_KHZ;
			break;
	}

	/* set the input clock */
	returnValue = i_PCI1500_InitTimerInputClock(boardHandle, clock);
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_InitTimerInputClock \n", returnValue);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	printf("i_PCI1500_InitTimerInputClock : successful\n");

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

	/* ask the timer index */
	ReadUlong("Enter the index of the timer you want to use (0,1) :", 0,1,&readValue);
	timerIndex = (BYTE)readValue;

	/* ask the reload value */
	ReadUlong("Enter the reload value of the timer (1-65535) :",1,65535, &readValue);
	reloadValue = (WORD)readValue;

	/* init the selected timer */
	switch( timerIndex )
	{
		case 0:
			returnValue = i_PCI1500_InitTimerCounter1(boardHandle,
				PCI1500_TIMER,
				reloadValue,
				1,	/* after having reach 0, continue */
				1);	/* enable interrupt */
			break;
		case 1:
			returnValue = i_PCI1500_InitTimerCounter2(boardHandle,
				PCI1500_TIMER,
				reloadValue,
				1,	/* after having reach 0, continue */
				0,	/* no hardware trigger */
				0,	/* no hardware gate */
				1);	/* enable interrupt */
			break;
	}
	if ( returnValue != 0 )
	{
		printf("Error %d in init timer \n", returnValue);
		i_PCI1500_ResetBoardIntRoutine(boardHandle);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	else
	{
		printf("init timer : successful\n");
	}

	/* start the timer */
	switch ( timerIndex )
	{
		case 0:
			returnValue = i_PCI1500_StartTimerCounter1(boardHandle);
			break;
		case 1:
			returnValue = i_PCI1500_StartTimerCounter2(boardHandle);
			break;
	}
	if ( returnValue != 0 )
	{
		printf("Error %d in start timer \n", returnValue);
		i_PCI1500_ResetBoardIntRoutine(boardHandle);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	else
	{
		printf("start timer : successful\n");
	}

	printf("Hit a key to exit the sample. press space to clear FiFo\n");
	int fifoClear = 0;
	for (;;)
	{
		WORD value = 0;
		fifoClear++;
		Sleep(100);
		
		/* does the user hit a key ? */
		if ( _kbhit() )
		{
			int c = _getch();
			if (c == 32) // press space
				i_PCI1500_ClearInterruptFIFO(boardHandle);
			else
				break;
		}

		/* read timer value */
		switch( timerIndex )
		{
			case 0:
				returnValue = i_PCI1500_ReadTimerCounter1(boardHandle, &value);
				break;
			case 1:
				returnValue = i_PCI1500_ReadTimerCounter2(boardHandle, &value);
				break;
		}
		if ( returnValue != 0 )
		{
			printf("Error %d in read timer value \n", returnValue);
			i_PCI1500_ResetBoardIntRoutine(boardHandle);
			i_PCI1500_CloseBoard(boardHandle);
			_getch();
			return -1;
		}
		printf("Timer : %d		 \r", (int)value);
	}

	/* stop the timer */
	switch( timerIndex )
	{
		case 0:
			returnValue = i_PCI1500_StopTimerCounter1(boardHandle);
			break;
		case 1:
			returnValue = i_PCI1500_StopTimerCounter2(boardHandle);
			break;
	}
	if ( returnValue != 0 )
	{
		printf("Error %d in stop timer \n", returnValue);
	}
	else
	{
		printf("stop timer : successful\n");
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

