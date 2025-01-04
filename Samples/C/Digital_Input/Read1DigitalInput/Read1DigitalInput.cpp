/**
* This source code is an example that shows how to use the method i_PCI1500_Read1DigitalInput
* The algorithm is the following:
* - Open board (via index or identifier - see the Utils.cpp file)
* - Call the method i_PCI1500_Read1DigitalInput
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
	BYTE channelIndex = 0;
	BYTE channelValue = 0;
	ULONG readValue = 0;

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
	printf("* Read 1 digital input sample. \n");
	printf("* Read the selected input channel. \n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n\n");

	/* get the channel to read */
	ReadUlong("Enter the index of the channel you want to read : (0-15) ",0,15, &readValue);
	channelIndex = (BYTE)readValue;

	printf("\n Press any key to exit the sample ...\n");
	printf("          ________\n");
	printf("Channel : |%d \t |\n", (int)channelIndex);

	do
	{
		/* read the value of the selected channel */
		returnValue = i_PCI1500_Read1DigitalInput(boardHandle, channelIndex, &channelValue);
		if (returnValue != 0)
		{
			printf("Error while reading 1 digital inputs : %d \n", returnValue);
			/* close the board and return */
			i_PCI1500_CloseBoard(boardHandle);
			return -1;
		}

		/* print the channel value */
		printf("Value :   |%d \t |\t",channelValue );
		
		/* show that something is running */
		DisplayRunningStatus();

		Sleep(50);
	}
	while ( !_kbhit() );

	/* close the board */
	returnValue = i_PCI1500_CloseBoard(boardHandle);
	if (returnValue != 0)
	{
		printf("Error while closing board : %d \n", (int)returnValue);
		_getch();
		return -1;
	}

	/* success */
	return 0;
}

