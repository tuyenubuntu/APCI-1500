/**
* This source code is an example that shows how to use the method i_PCI1500_Read16DigitalInputs
* The algorithm is the following:
* - Open board (via index or identifier - see the Utils.cpp file)
* - Call the method i_PCI1500_Read16DigitalInputs
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
	WORD channelsValue = 0;

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
	printf("* Read digital inputs sample. \n");
	printf("* Read the 16 digital inputs of the board and display their status. \n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n\n");


	printf("\n Press any key to exit the sample ...\n");
	printf("_________________________________________________________________\n");
	printf("|0  |1  |2  |3  |4  |5  |6  |7  |8  |9  |10 |11 |12 |13 |14 |15 |\n");

	do
	{
		/* read the value of the selected channel */
		returnValue = i_PCI1500_Read16DigitalInputs(boardHandle, &channelsValue);
		if (returnValue != 0)
		{
			printf("Error while reading 16 digital inputs : %d \n", returnValue);
			/* close the board and return */
			i_PCI1500_CloseBoard(boardHandle);
			return -1;
		}

		/* print the channel value */
		printf("|%d  |%d  |%d  |%d  |%d  |%d  |%d  |%d  |%d  |%d  |%d  |%d  |%d  |%d  |%d  |%d  |\t",
			VALUE_CHANNEL(channelsValue,0),
			VALUE_CHANNEL(channelsValue,1),
			VALUE_CHANNEL(channelsValue,2),
			VALUE_CHANNEL(channelsValue,3),
			VALUE_CHANNEL(channelsValue,4),
			VALUE_CHANNEL(channelsValue,5),
			VALUE_CHANNEL(channelsValue,6),
			VALUE_CHANNEL(channelsValue,7),
			VALUE_CHANNEL(channelsValue,8),
			VALUE_CHANNEL(channelsValue,9),
			VALUE_CHANNEL(channelsValue,10),
			VALUE_CHANNEL(channelsValue,11),
			VALUE_CHANNEL(channelsValue,12),
			VALUE_CHANNEL(channelsValue,13),
			VALUE_CHANNEL(channelsValue,14),
			VALUE_CHANNEL(channelsValue,15));
		
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

