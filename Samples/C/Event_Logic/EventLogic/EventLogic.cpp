// Test_EventLogic.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

int _tmain(int /* argc */, _TCHAR* /* argv[] */)
{
	INT returnValue = 0;
	HANDLE	boardHandle = NULL;
	ULONG readValue = 0;
	BYTE portIndex = 0;
	BYTE eventLogic = 0;
	CHAR eventMask[9];

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
	printf("* Event logic sample. \n");
	printf("* Enables interrupt and install event logic. \n");
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


	/* get the port to use */
	ReadUlong("Enter the port to use (0 or 1): ", 0,1,&readValue);
	portIndex = (BYTE)readValue;

	/* get the event logic to use */
	ReadUlong("Enter the event logic to use (0:OR or 1:AND): ",0,1,&readValue);
	eventLogic = (BYTE)readValue;

	/* get the event mask mask */
	do
	{
		printf("\n Enter the event mask. Mask is a %u-bits string", portIndex == 0 ? 8 : 6);
		printf("\n Values are : 'X':not used, '0':low level, '1':high level, '2':falling edge, '3':rising edge, '4':both edge \n");
		_flushall();
		fgets(eventMask,sizeof(eventMask),stdin);
		/* for compatibility, string must be null ended */
		if (eventMask[strlen(eventMask)-1] == '\n')
		{
			eventMask[strlen(eventMask)-1] = '\0';
		}
	}
	while((strlen(eventMask) != 8) && (strlen(eventMask) != 6));

	/* Initialize the event logic */
	returnValue = i_PCI1500_InitEventLogic(boardHandle,portIndex,eventLogic,eventMask);
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_InitEventLogic \n", returnValue);
		i_PCI1500_ResetBoardIntRoutine(boardHandle);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	printf("i_PCI1500_InitEventLogic : successful\n");

	/* start the event logic */
	returnValue = i_PCI1500_StartEventLogic(boardHandle,portIndex);
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_StartEventLogic \n", returnValue);
		i_PCI1500_ResetBoardIntRoutine(boardHandle);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	printf("i_PCI1500_StartEventLogic : successful\n");

	printf("The board is now waiting an event. Press any key to exit this sample.\n");
	/*
	* Wait that the user hit a key 
	* The displaying is now done in the Utils.cpp file (interrupt routine)
	*/
	for(;;)
	{
		Sleep(100);
		if ( _kbhit() )
		{
			_getch();
			break;
		}
	}

	/* stop the event logic */
	returnValue = i_PCI1500_StopEventLogic(boardHandle, portIndex);
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_StopEventLogic \n", returnValue);
	}
	else
	{
		printf("i_PCI1500_StopEventLogic : successful\n");
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

