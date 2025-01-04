#include <userint.h>
#include <utility.h>
#include <ansi_c.h>
#include "d:\SVN\Addidata_Device_Drivers\Current\PCI1500\Samples\LabWindowsCVI\PCI1500.H"


void	main	(void)
	{
	
	int 	      i_ReturnValue  = 0;	// Return error code 
	unsigned char b_BoardIndex   = 0;
	unsigned long b_BoardHandle  = 0;	// APCI-1500 Board handle
	unsigned char b_boardNbr 	 = 0;

	int i_key = 0;   // Tests the hidden key 
	
    unsigned char   nameStr[25];
  
    
	unsigned short l_Value = 65535;   // Channel value to set (0 - 65535)     
    
    
	/****************************/
	/* Print sample information */
	/****************************/

	printf ("\n\n");
	printf ("\n+---------------------------------------------------+");
	printf ("\n| APCI-1500 digital output SAMPLE04 :               |");
	printf ("\n| Get hardware information from one APCI-1500 board |");
	printf ("\n| Sets digital outputs of the board                 |");
	printf ("\n| The number of outputs is given by l_Value         |");
	printf ("\n+---------------------------------------------------+");
	printf ("\n| Pin assigment:                                    |");
	printf ("\n|         With multimeter between PIN 11 to 18 and  |");
	printf ("\n|         PIN 30 to 37 (Plus) and PIN 29 (Minus):   |");
	printf ("\n|         (This sample needs external power supply: |");
	printf ("\n|         24 Volt at Pin 28, 0 Volt at PIN 29 )     |");
	printf ("\n|          - Outputs  set   -> Voltage = 24 Volt    |");
	printf ("\n|          - Outputs  reset -> Voltage = 0  Volt    |");
	printf ("\n+---------------------------------------------------+");
	printf ("\n| ADDI-DATA additional products                     |");
	printf ("\n|    Cable   : ST010  37pin SUB D                   |");
	printf ("\n+    Platine : PX901AD                              |");
	printf ("\n+---------------------------------------------------+");
	printf ("\n| <ESC> exit sample                                 |");
	printf ("\n+---------------------------------------------------+");
	printf ("\n| Press any key for start the sample                |");
	printf ("\n+---------------------------------------------------+");
	printf ("\n\n");
	GetKey  ();

	/**************************************/
	/* Search an initialise one APCI-1500 */
	/**************************************/
	
	/* Get the number of boards available */
	i_ReturnValue = i_PCI1500_GetNumberOfBoards(&b_boardNbr);	
	
    switch (i_ReturnValue)
	  {
	  case 0:
	   printf ("\ni_PCI1500_GetNumberOfBoards OK");
	   break;

	  case -1:
	   printf ("\ni_PCI1500_GetNumberOfBoards");   
	   printf ("\nError while getting the number of boards ");
	   break;
	  }

	 printf("\n %d are detected",  b_boardNbr);

   	/* Check the number of board */
	if (b_boardNbr == 0)
	{
		printf("Error : no board found \n");
		return ;
	}	
	
	
	/* Get the index from the user */
	do
	{
    /* Run through a series of popups... */
    PromptPopup ("PCI1500", "Chose the card :",nameStr, 20);

 	b_BoardIndex =  nameStr[0] - 48;
 	
 	printf("\nCard  %d ist selected",  b_BoardIndex); 
 	
 	} while ( (b_BoardIndex < 0) || (b_BoardIndex > b_boardNbr-1));
	

	
	/* Open the Board */ 
	i_ReturnValue = i_PCI1500_OpenBoardViaIndex (b_BoardIndex, &b_BoardHandle);

	/* Error handling */ 
    switch (i_ReturnValue)
	  {
	  case 0:
	   printf ("\ni_PCI1500_OpenBoardViaIndex OK");
	   break;

	  case -1:
	   printf ("\ni_PCI1500_OpenBoardViaIndex");   
	   printf ("\nUnable to get the number of available boards  ");
	   break;
	   
	  case -2:
	   printf ("\ni_PCI1500_OpenBoardViaIndex");   
	   printf ("\nWrong device index parameter. The parameter is too high ");
	   break;
	  
	  case -3:
	   printf ("\ni_PCI1500_OpenBoardViaIndex");   
	   printf ("\nError while getting the device's class ");
	   break;
	  
	  case -4:
	   printf ("\ni_PCI1500_OpenBoardViaIndex");   
	   printf ("\nError while getting informations about the device  ");
	   break;
	  
	  case -5:
	   printf ("\ni_PCI1500_OpenBoardViaIndex");   
	   printf ("\nMemory allocation error");
	   break;

	  case -6:
	   printf ("\ni_PCI1500_OpenBoardViaIndex");   
	   printf ("\nGet device interface detail error");
	   break;	  
	  
	  case -7:
	   printf ("\ni_PCI1500_OpenBoardViaIndex");   
	   printf ("\nError while creating communication handle");
	   break;
	  
	  case -8:
	   printf ("\ni_PCI1500_OpenBoardViaIndex");   
	   printf ("\nError in the initialization callback function");
	   break;

	  }


	/**************************/
	/* Test if no error occur */
	/**************************/

	if (i_ReturnValue == 0)
	   {


 	  /********************************************************************/
	  /* The funktion SetOutputMemoryOn stores the current state of the   */
	  /* output. This is neccessary for the function Set16DigitalOutputOff */
	  /********************************************************************/


  	  i_ReturnValue = i_PCI1500_SetDigitalOutputMemoryOn  (b_BoardHandle);
	     switch (i_ReturnValue)
		 {
	       case  0:
			 printf("\ni_PCI1500_SetDigitalOutputMemoryOn       OK");
			 break;

	       case -1:
			 printf("\ni_PCI1500_SetDigitalOutputMemoryOn        error");
			 printf("\nError = %d. Error while calling IOCTL function (wrong handle ?) ", i_ReturnValue);
			 break;

	       default:
			 printf("\ni_APCI1500_SetOutputMemoryOn        error");
			 printf ("\nError = %d", i_ReturnValue);
		 }
	     printf("\n\nPress any key to set the outputs of the board!\n");
	     GetKey();



 	   /*********************************************/
	   /* The function sets the outputs, the number */
	   /* is given by the variable b_Value          */
	   /*********************************************/

	   i_ReturnValue = i_PCI1500_Set16DigitalOutputsOn (b_BoardHandle,
							                             l_Value);
	     switch (i_ReturnValue)
		 {
	       case  0:
			 printf("\ni_PCI1500_Set16DigitalOutputsOn     OK");
		     break;

	       case -1:
			 printf("\ni_PCI1500_Set16DigitalOutputsOn     error");
			 printf("\nError = %d.Error while calling IOCTL function (wrong handle ?)", i_ReturnValue);
			 break;

	       default:
			 printf("\ni_APCI1500_Set16DigitalOutputOn     error");
			 printf("\nError = %d", i_ReturnValue);
		 }
	     printf("\n\nPress any key to reset the outpus of the board! \n");
	     GetKey();

	   /******************************************/
	   /* Deactivates the outputs, the number is */
	   /* given by the variable l_Value          */
	   /******************************************/

 	   i_ReturnValue = i_PCI1500_Set16DigitalOutputsOff (b_BoardHandle,
							                             l_Value);
	     switch (i_ReturnValue)
		 {
	       case  0:
			 printf("\ni_PCI1500_Set16DigitalOutputsOff     OK");
		     break;

	       case -1:
			 printf("\ni_PCI1500_Set16DigitalOutputsOff     error");
			 printf("\nError = %d.Error while calling IOCTL function (wrong handle ?)", i_ReturnValue);
			 break;

	       default:
			 printf("\ni_APCI1500_Set16DigitalOutputOff     error");
			 printf("\nError = %d", i_ReturnValue);
		 }
	     printf("\n\nPress any key to reset the outpus of the board! \n");
	     GetKey();

 
 	  /******************************************************************/
	  /* The funktion SetOutputMemoryOff deactivates the Output memeory */
	  /******************************************************************/

   	  i_ReturnValue = i_PCI1500_SetDigitalOutputMemoryOff  (b_BoardHandle);
	     switch (i_ReturnValue)
		 {
	       case  0:
			 printf("\ni_PCI1500_SetDigitalOutputMemoryOff       OK");
			 break;

	       case -1:
			 printf("\ni_PCI1500_SetDigitalOutputMemoryOff        error");
			 printf("\nError = %d. Error while calling IOCTL function (wrong handle ?) ", i_ReturnValue);
			 break;

	       default:
			 printf("\ni_APCI1500_SetOutputMemoryOn        error");
			 printf ("\nError = %d", i_ReturnValue);
		 }
	     printf("\n\nPress any key to set the outputs of the board!\n");
	     GetKey();


	   /**************************/
	   /* Close the board handle */
	   /**************************/
	   i_ReturnValue = i_PCI1500_CloseBoard (b_BoardHandle);
	   
	   switch (i_ReturnValue)
	      {
	      case 0:
		   printf ("\ni_PCI1500_CloseBoard         OK");
		   break;

	      case -1:
		   printf ("\ni_PCI1500_CloseBoard         error");
		   printf ("\nError = %d. The device handle parameter is wrong ", i_ReturnValue);
		   break;
	      } 
	   } 


	printf ("\n\n");
	printf ("\n+---------------------------------------------------+");
	printf ("\n| Program concluded.                                |");
	printf ("\n+---------------------------------------------------+");
	printf ("\n| Press ESC for exit from sample                    |");
	printf ("\n+---------------------------------------------------+");
	printf ("\n\n");

	/************/
	/* Wait ESC */
	/************/

	GetKey();
	printf ("\n\n");
	}
