#ifndef __UTILS_H
#define __UTILS_H

#include <windows.h>
#include <stdio.h>


/**
* Enables to give to the user the choice to open a board
* The function also enables (first) to display informations about the available boards
* @return 0 success, != 0 error
**/
INT OpenBoard(HANDLE * deviceHandle);

/**
* Display a sort of progress bar
**/
void DisplayRunningStatus();

/**
* Enable to read a ulong from the keyboard
* @param description: A description string that is printed to give some information about the value that must be given
**/
void ReadUlong( char* description, ULONG minValue, ULONG maxValue, ULONG* readValue );

void InterruptRoutine (
	HANDLE	/* h_DeviceHandle */,
	BYTE	/* uc_FIFOOverflow */,
	BYTE	uc_InterruptMask,
	WORD	us_Inputs );

#endif