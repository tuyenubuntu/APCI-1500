/**
* This source code is an example that shows how to use the methods i_PCI1500_Set16DigitalOutputsOn and i_PCI1500_Set16DigitalOutputsOff
* The algorithm is the following:
* - Open board (via index or identifier - see the Utils.cpp file)
* - Enable the digital output memory
* - Call the method i_PCI1500_Set16DigitalOutputsOff with the mask 0xFF (all the outputs)
* - Call the method i_PCI1500_Set16DigitalOutputsOn with a specified mask
* - Disable the digital output memory
* - Close the board
**/
#include "stdafx.h"

#define VALUE_CHANNEL(x,ch)	( (x >> ch) & 0x1 )

/**
* Entry point
**/
int _tmain( int /*argc*/, _TCHAR* /*argv[]*/ )
{
	INT returnValue = 0;
	HANDLE	boardHandle = NULL;
	ULONG readValue = 0;
	WORD mask = 0;

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
	printf("* Set digital outputs sample. \n");
	printf("* Enable the digital output memory and set the digital outputs to a \n");
	printf("* specified state.\n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n\n");

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

	/* set all the output to low */
	returnValue = i_PCI1500_Set16DigitalOutputsOff(boardHandle, 0xFFFF );
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_Set16DigitalOutputsOff \n", returnValue);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	printf("i_PCI1500_Set16DigitalOutputsOff : succesfull\n");

	/* ask the mask */
	ReadUlong("Enter a mask of digital outputs that will be set to 1: (0 to 65535) ",0,0xFFFF, &readValue);
	mask = (WORD)readValue;

	/* set the mask of output to on */
	returnValue = i_PCI1500_Set16DigitalOutputsOn(boardHandle,mask);
	if ( returnValue != 0 )
	{
		printf("Error %d in i_PCI1500_Set16DigitalOutputsOn \n", returnValue);
		i_PCI1500_CloseBoard(boardHandle);
		_getch();
		return -1;
	}
	printf("i_PCI1500_Set16DigitalOutputsOn : succesfull\n");

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

