/**
* Demonstrates how to use the watchdog of the board
**/
#include "stdafx.h"

int _tmain ( int /*argc*/, _TCHAR* /*argv[]*/ )
{
	INT returnValue = 0;
	HANDLE boardHandle = NULL;
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
	printf("* Watchdog sample. \n");
	printf("* Since there is only one watchdog on the board you do not have the \n");
	printf("* choice of the index. \n");
	printf("* We enable the interrupt so you will receive an interrupt each time \n");
	printf("* the watchdog reach 0. \n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n\n");

	/* set the digital outputs to on */
	returnValue = i_PCI1500_Set16DigitalOutputsOn( boardHandle, 0xFFFF );
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_Set16DigitalOutputsOn \n", returnValue);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	printf("i_PCI1500_Set16DigitalOutputsOn : successful\n");

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

	/* ask the reload value */
	ReadUlong("Enter the reload value of the watchdog (1-65535) :",1,65535, &readValue);
	reloadValue = (WORD)readValue;

	/* init the watchdog */
	returnValue = i_PCI1500_InitWatchdogCounter3(boardHandle,
		PCI1500_WATCHDOG,
		reloadValue,
		1,	/* continuous cycle - no need to reinit the watchdog */
		0,	/* no hardware gate*/
		1);	/* enable interrupt */
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_InitWatchdogCounter3 \n", returnValue);
		i_PCI1500_ResetBoardIntRoutine(boardHandle);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	else
	{
		printf("i_PCI1500_InitWatchdogCounter3 : successful\n");
	}

	/* start the watchdog */
	returnValue = i_PCI1500_StartWatchdogCounter3(boardHandle);
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_StartWatchdogCounter3 \n", returnValue);
		i_PCI1500_ResetBoardIntRoutine(boardHandle);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	else
	{
		printf("i_PCI1500_StartWatchdogCounter3 : successful\n");
	}

	printf("Hit a key to exit the sample. Hit space to set the digital outputs. \n");
	for (;;)
	{
		WORD value = 0;
		Sleep(100);

		/* does the user hit a key ? */
		if ( _kbhit() )
		{
			/* space key ? */
			if ( _getch() == 32 )
			{
				returnValue = i_PCI1500_Set16DigitalOutputsOn( boardHandle, 0xFFFF );
				if ( returnValue != 0 )
				{
					printf("Error %d in i_PCI1500_Set16DigitalOutputsOn \n", returnValue);
					i_PCI1500_StopWatchdogCounter3(boardHandle);
					i_PCI1500_ResetBoardIntRoutine(boardHandle);
					i_PCI1500_CloseBoard(boardHandle);
					_getch();
					return -1;
				}
				printf("i_PCI1500_Set16DigitalOutputsOn : successful\n");
			}
			else
			{
				break;
			}
		}

		/* read watchdog value */
		returnValue = i_PCI1500_ReadWatchdogCounter3(boardHandle, &value);
		if ( returnValue != 0 )
		{
			printf("Error %d in i_PCI1500_ReadWatchdogCounter3 \n", returnValue);
			i_PCI1500_ResetBoardIntRoutine(boardHandle);
			i_PCI1500_CloseBoard(boardHandle);
			_getch();
			return -1;
		}
		printf("Watchdog : %d		 \r", (int)value);
	}

	/* stop the watchdog */
	returnValue = i_PCI1500_StopWatchdogCounter3(boardHandle);
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_StopWatchdogCounter3 \n", returnValue);
	}
	else
	{
		printf("i_PCI1500_StopWatchdogCounter3 : successful\n");
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

