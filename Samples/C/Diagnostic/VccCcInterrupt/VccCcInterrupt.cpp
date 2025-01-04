/**
* Demonstrates how to use the short-circuit / voltage supply lost detection
**/
#include "stdafx.h"

int _tmain ( int /*argc*/, _TCHAR* /*argv[]*/ )
{
	INT returnValue = 0;
	HANDLE boardHandle = NULL;

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
	printf("* Short circuit - Voltage supply lost sample. \n");
	printf("* Enables to detect short circuit or voltage supply lost thanks to\n");
	printf("* interrupts.\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n\n");

	/* set the digital output memory */
	returnValue = i_PCI1500_SetDigitalOutputMemoryOn(boardHandle);
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_SetDigitalOutputMemoryOn \n", returnValue);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	printf("i_PCI1500_SetDigitalOutputMemoryOn : successful\n");

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

	/* enables the event logic on port 1 to receive the vcc and cc interruption */
	returnValue = i_PCI1500_InitEventLogic(boardHandle,PCI1500_PORT_1,PCI1500_LOGIC_OR,"xxxxxx");
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
	returnValue = i_PCI1500_StartEventLogic(boardHandle,PCI1500_PORT_1);
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_StartEventLogic \n", returnValue);
		i_PCI1500_ResetBoardIntRoutine(boardHandle);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	printf("i_PCI1500_StartEventLogic : successful\n");

	/* We set the digital outputs to ON in order to be able to short-circuit them */
	returnValue = i_PCI1500_Set16DigitalOutputsOn( boardHandle, 0xFFFF );
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_Set16DigitalOutputsOn \n", returnValue);
		i_PCI1500_StopEventLogic(boardHandle, PCI1500_PORT_1);
		i_PCI1500_ResetBoardIntRoutine(boardHandle);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	printf("i_PCI1500_Set16DigitalOutputsOn : successful\n");

	printf("The digital outputs are ON. \n");
	printf("You can short-circuit them to get a CC interrupt.\n");
	printf("You can lower the input voltage to get a VCC interrupt. \n");
	printf("Press space to set the outputs again. \n");
	printf("Press any other key to stop the sample.\n");

	/* endless loop */
	for(;;)
	{
		Sleep(100);
		if ( _kbhit() )
		{ 
			/* space key ? */
			if ( _getch() == 32 )
			{
				returnValue = i_PCI1500_Set16DigitalOutputsOn( boardHandle, 0xFFFF );
				if ( returnValue != 0 )
				{
					printf("Error %d in i_PCI1500_Set16DigitalOutputsOn \n", returnValue);
					i_PCI1500_StopEventLogic(boardHandle, PCI1500_PORT_1);
					i_PCI1500_ResetBoardIntRoutine(boardHandle);
					i_PCI1500_CloseBoard(boardHandle);
					_getch();
					return -1;
				}
				printf("i_PCI1500_Set16DigitalOutputsOn : successful\n");
			}
			/* other key */
			else
			{
				break;
			}
		}
	}

	/* reset the digital outputs */
	returnValue = i_PCI1500_Set16DigitalOutputsOff( boardHandle, 0xFFFF );
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_Set16DigitalOutputsOff \n", returnValue);
	}
	else
	{
		printf("i_PCI1500_Set16DigitalOutputsOff : successful\n");
	}

	/* stop the event logic */
	returnValue = i_PCI1500_StopEventLogic(boardHandle, PCI1500_PORT_1);
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

