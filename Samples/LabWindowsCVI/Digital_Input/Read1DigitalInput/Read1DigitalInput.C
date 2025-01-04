#include <userint.h>
#include <utility.h>
#include <ansi_c.h>
#include "..\..\PCI1500.H"


void	main	(void)
	{
	
	int 	      i_ReturnValue  = 0;	// Return error code 
	unsigned char b_BoardIndex   = 0;
	unsigned long b_BoardHandle  = 0;	// APCI-1500 Board handle
	unsigned char b_boardNbr 	 = 0;
	
	unsigned char b_channelIndex = 0;	
	unsigned char b_ChannelValue = 0;   // Channel value to read  
	
	unsigned char b_Channel      = 1;   // Channel to read

	int i_key = 0;   // Tests the hidden key 
	
    unsigned char   nameStr[25];
    
    
	/****************************/
	/* Print sample information */
	/****************************/

	printf ("\n\n");
	printf ("\n+---------------------------------------------------+");
	printf ("\n| APCI-1500 digital input SAMPLE01 :                |");
	printf ("\n| Get hardware information from one APCI-1500 board |");
	printf ("\n| Reads the digital input number one of the board   |");
	printf ("\n+---------------------------------------------------+");
	printf ("\n| PIN ASSIGNEMENT:                                  |");
	printf ("\n|    PIN 1:  0 - 15V low  -> Reading input: 0       |");
	printf ("\n|    PIN 1: 16 - 24V high -> Reading input: 1       |");
	printf ("\n+---------------------------------------------------+");
	printf ("\n| ADDI-DATA additional products                     |");
	printf ("\n|    Cable           : ST010                        |");
	printf ("\n|    Connection board: PX901-AD or PX901-A          |");
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
	i_ReturnValue = i_PCI1500_GetNumberOfBoards( &b_boardNbr );	
	
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
	

	/* Get the channel Number to read */
	do
	{
    /* Run through a series of popups... */
    PromptPopup ("PCI1500", "Chose Input Channel to read :",nameStr, 20);

 	b_channelIndex =  nameStr[0] - 48;
 	
 	printf("\nInput chanel  %d ist selected",  b_channelIndex); 
 	
 	} while ( (b_channelIndex < 0) || (b_channelIndex > 16));
	
	
	
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

       /**************************************************/
       /* The function Read1DigitalInput reads the value */
       /* from the channel 1.                            */
       /* The test program stops if <ESC> is hidden      */
       /**************************************************/

       i_ReturnValue = i_PCI1500_Read1DigitalInput  (b_BoardHandle,
						                             b_channelIndex,
						                             &b_ChannelValue);
       switch (i_ReturnValue)
       {
	   case  0:
			printf("\ni_PCI1500_Read1DigitalInput         OK");
			break;

	   case -1:
			printf("\ni_PCI1500_Read1DigitalInput         error");
			printf("\nError = %d. The channel index is wrong ", i_ReturnValue);
			break;

	   case -2:
		    printf("\ni_PCI1500_Read1DigitalInput         error");
			printf("\nError = %d. Error while calling IOCTL function (wrong handle ?)", i_ReturnValue);
			break;

	   default:
			printf("\ni_PCI1500_Read1DigitalInput         error");
			printf("\nERROR = %d", i_ReturnValue);
       }
       
       printf("\n\nPress any key to start reading the channel %d!\n",b_channelIndex);
       printf("\nPress >ESC< to end the test!\n");
       GetKey();
       i_key = 1;
       do
       {
	     i_ReturnValue = i_PCI1500_Read1DigitalInput ( b_BoardHandle,
							                           b_channelIndex,
						                               &b_ChannelValue);
	     printf("Input 1 value: %u\n", b_ChannelValue);
	     if (KeyHit() == 1)
		 {
	       i_key = GetKey();
		 }
	   }
       while (i_key != 0x300);


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
