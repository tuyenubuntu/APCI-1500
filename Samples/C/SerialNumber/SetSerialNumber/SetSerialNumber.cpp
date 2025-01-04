// GetSeialNumber.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE boardHandle = NULL;
	INT returnValue = 0;
	INT boolValue = 0;
	DWORD serialNumber;
	DWORD firmwareVersion;

	//	Open a board
	returnValue = OpenBoard(&boardHandle);
	if (returnValue != 0)
	{
		printf("Error %d opening the board \n", returnValue);
		_getch();
		return -1;
	}
	
	//	display some useful informations
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	printf("* Sample that shows the serial number of the board. \n");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n\n");
	
	//	read the serial number
	returnValue = i_PCI1500_GetSerialNumber(boardHandle, &serialNumber);
	if(returnValue != 0)
	{
			printf("Error %d in i_PCI1500_GetSerialNumber", returnValue);
			i_PCI1500_CloseBoard(boardHandle);
			_getch();
			return -1;
	}
	else
	{
		//	display value
		printf("Serial Number : A-D %lu \n", serialNumber);
	}
	//	read the Firmware Number
	returnValue = i_PCI1500_GetFirmwareVersion(boardHandle, &firmwareVersion);
	if(returnValue != 0)
	{
			printf("Error %d in i_PCI1500_GetBoardFirmwareVersion", returnValue);
			i_PCI1500_CloseBoard(boardHandle);
			_getch();
			return -1;
	}
	else
	{
		//	display value
		printf("Firmware Version : %c%c %c%c \n",(firmwareVersion>>24 & 0xFF),(firmwareVersion>>16 & 0xFF),(firmwareVersion>>8 & 0xFF),(firmwareVersion & 0xFF));
	}

	//Set Serial Number

	printf("Do you wish to change the Serial Number ? Yes:1 or No:0\n");
	scanf("%d",&boolValue);
	if(boolValue != 0){
		do {
			printf("Please Enter the serial Number A-D XXXXXX\n");
			scanf("%d",&serialNumber);
		}while(serialNumber>1000000 & serialNumber<99999);
	}
	//	set the Serial Number
	returnValue = i_PCI1500_SetSerialNumber(boardHandle, serialNumber);
	if ( returnValue != 0 )
	{
		printf("i_PCI1500_SetSerialNumber error : %d \n", returnValue);
	}
	else
	{
		printf("i_PCI1500_SetSerialNumber ok. \n");
	}
	
	//	close the board
	returnValue = i_PCI1500_CloseBoard(boardHandle);
	if ( returnValue != 0 )
	{
		printf("i_PCI1500_CloseBoard error : %d \n", returnValue);
	}
	else
	{
		printf("i_PCI1500_CloseBoard ok. \n");
	}

	//	exit
	printf("\n Press any key to exit the sample ...");
	_getch();
	
	return 0;
}