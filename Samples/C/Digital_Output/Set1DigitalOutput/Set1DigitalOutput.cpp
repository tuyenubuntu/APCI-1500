/**
* This source code is an example that shows how to use the methods i_PCI1500_Set1DigitalOutputOn and i_PCI1500_Set1DigitalOutputsff
**/
#include "stdafx.h"

#define VALUE_CHANNEL(x,ch)	( (x==ch) ? 'x' : '-' )

/**
* Entry point
**/
int _tmain( int /*argc*/, _TCHAR* /*argv[]*/ )
{
	INT returnValue = 0;
	HANDLE	boardHandle = NULL;
	ULONG readValue = 0;
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
	printf("* Set 1 digital output sample. \n");
	printf("* Use the numeric touch of your keyboard to change the status of the \n");
	printf("* inputs 0 to 7. \n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n\n");

	/* digital output memory ? */
	ReadUlong("Do you want to use digital output memory (0: no, 1: yes) ?", 0,1, &readValue);
	if ( readValue == 0 )
	{
		/* disable output memory */
		returnValue = i_PCI1500_SetDigitalOutputMemoryOff(boardHandle);
		if ( returnValue != 0 )
		{
			printf("Error %d in i_PCI1500_SetDigitalOutputMemoryOff \n", returnValue);
			i_PCI1500_CloseBoard(boardHandle);
			_getch();
			return -1;
		}
		printf("i_PCI1500_SetDigitalOutputMemoryOff : succesfull\n");
	}
	else
	{
		/* enable output memory */
		returnValue = i_PCI1500_SetDigitalOutputMemoryOn(boardHandle);
		if ( returnValue != 0 )
		{
			printf("Error %d in i_PCI1500_SetDigitalOutputMemoryOn \n", returnValue);
			i_PCI1500_CloseBoard(boardHandle);
			_getch();
			return -1;
		}
		printf("i_PCI1500_SetDigitalOutputMemoryOn : succesfull\n");
	}

	printf("Use the touch 0 to 7 to set the output to 1. Press 'ESC' to \n");
	printf("exit this sample. If you do not use digital output memory, setting an \n");
	printf("output to 0 will result with an error. \n");

	/* endless loop */
	printf("|0  |1  |2  |3  |4  |5  |6  |7  |\n");
	while(doContinue == 1)
	{
		int hitChar = _getch();
		switch(hitChar)
		{
			/* 'ESC' */
			case 27:
				doContinue = 0;
				break;
			/* 0 to 7*/
			case 48:
			case 49:
			case 50:
			case 51:
			case 52:
			case 53:
			case 54:
			case 55:
				returnValue = i_PCI1500_Set1DigitalOutputOn( boardHandle, (BYTE)(hitChar-48));
				if ( returnValue != 0 )
				{
					printf("Error %d in i_PCI1500_Set1DigitalOutputOn \n", returnValue);
					i_PCI1500_CloseBoard(boardHandle);
					_getch();
					return -1;
				}
				printf("|%c  |%c  |%c  |%c  |%c  |%c  |%c  |%c  | \r",
					VALUE_CHANNEL((hitChar-48),0),
					VALUE_CHANNEL((hitChar-48),1),
					VALUE_CHANNEL((hitChar-48),2),
					VALUE_CHANNEL((hitChar-48),3),
					VALUE_CHANNEL((hitChar-48),4),
					VALUE_CHANNEL((hitChar-48),5),
					VALUE_CHANNEL((hitChar-48),6),
					VALUE_CHANNEL((hitChar-48),7));
				break;
		}
	}

	/* close the board*/
	returnValue = i_PCI1500_CloseBoard(boardHandle);
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_CloseBoard \n", returnValue);
		_getch();
		return -1;
	}
	printf("i_PCI1500_CloseBoard : succesfull\n");

	printf("Hit a key to exit ...");
	_getch();

	/* success */
	return 0;
}

