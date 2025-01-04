#include <formatio.h>
#include <userint.h>
#include <utility.h>
#include <ansi_c.h>
#include "..\..\Lib_Lab_CVI\PCI1500.H"
#include "..\..\Lib_Lab_CVI\pci1500-define.H"

/*************************************************/
/* Now the interrupt routine will be initialized */
/* After that it is possible to use this routine */
/* in the asynchronus mode.                      */
/* In the main programm you have the possibility */
/* to check the different gobal variables for    */
/* registrate if an interrupt occurs             */
/*************************************************/

unsigned char b_EventCpt [2];
unsigned char b_TimerCounterCpt[3];
unsigned char b_WatchdogCpt;
unsigned char b_VoltageErrorCpt;

 void cdecl v_InterruptRoutine (DWORD_ b_BoardHandle,
 							BYTE_ b_FIFOOverflow,
							BYTE_ dw_InterruptMask,
			                WORD_ w_InputValues)

	{
	
	printf("\ndw_InterruptMask:  %d\n",  dw_InterruptMask); 
	
	
	if (dw_InterruptMask & 0x1)
	  {                                                   /**************************/
	  b_EventCpt [0] = b_EventCpt [0] + 1;                /* Event port A interrupt */
	  }                                                   /**************************/

	if (dw_InterruptMask & 0x2)
	  {                                                   /**************************/
	  b_EventCpt [1] = b_EventCpt [1] + 1;                /* Event port B interrupt */
	  }                                                   /**************************/

	if (dw_InterruptMask & 0x4)
	  {                                                   /****************************/
	  b_TimerCounterCpt [0] = b_TimerCounterCpt [0] + 1;  /* Timer/Counter1 interrupt */
	  }                                                   /****************************/

	if (dw_InterruptMask & 0x8)
	  {                                                   /****************************/
	  b_TimerCounterCpt [1] = b_TimerCounterCpt [1] + 1;  /* Timer/Counter2 interrupt */
	  }                                                   /****************************/

	if (dw_InterruptMask & 0x10)
	  {                                                   /**********************/
	  b_TimerCounterCpt [2] = b_TimerCounterCpt [2] + 1;  /* Counter3 interrupt */
	  }                                                   /**********************/

	if (dw_InterruptMask & 0x20)
	  {                                                   /**********************/
	  b_WatchdogCpt = b_WatchdogCpt + 1;                  /* Watchdog interrupt */
	  }                                                   /**********************/

	if (dw_InterruptMask & 0xC0)
	  {                                                   /*****************/
	  b_VoltageErrorCpt = b_VoltageErrorCpt + 1;          /* Voltage error */
	  }                                                   /*****************/
	  
    }


void	main	(void)
	{
	
	int 	       i_ReturnValue  = 0;	// Return error code 
	unsigned char  b_BoardIndex   = 0;
	unsigned long  b_BoardHandle  = 0;	// APCI-1500 Board handle
	unsigned char  b_boardNbr 	  = 0;
	
	unsigned short l_Value = 0;   // Channel value to read  
				   
	unsigned char  b_Channel      = 1;   // Channel to read

	int i_key = 0;   // Tests the hidden key 
	
	
	int            i_Range          = 0; // Variable to check if the value range was wrong

	unsigned char  b_InterruptNbr   = 0;	// APCI-1500 interrupt
	

	unsigned char  b_InputClockSelected       	= PCI1500_1_8_KHZ;     // Input frequency,fixed on 1.8kHz
	unsigned char  b_ComponentMode 				= PCI1500_TIMER;       // Operation mode of the timer 1
	unsigned short w_ReloadValue          		= 0;                   // Division factor for the timer 1
	unsigned char  b_EnableContinuousCycle 		= 1; 				   // Reset the timer to us_ReloadValue after each interrupt, and continue counting (0,1)  
	unsigned char  b_EnableInterrupt            = 1;			       // An interrupt is generated each time the timer or counter expires (0,1)
	unsigned short l_ReadValue                  = 0;                   // Current value of the timer/counter	

    unsigned char   nameStr[25];  	
	

	/****************************/
	/* Print sample information */
	/****************************/

	printf ("\n\n");
	printf ("\n+---------------------------------------------------+");
	printf ("\n| APCI-1500 digital input SAMPLE05 :                |");
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
       
        /***************************************/
        /* Installs the User interrupt routine */
        /* and allows to react to interrupts   */
        /***************************************/

       i_ReturnValue = i_PCI1500_SetBoardIntRoutine (b_BoardHandle, v_InterruptRoutine);       
      
       
       switch (i_ReturnValue)
       {
	   case  0:
			printf("\ni_PCI1500_SetBoardIntRoutine         OK");
			break;

	   case -1:
			printf("\ni_PCI1500_SetBoardIntRoutine         error");
			printf("\nError = %d.  The device handle parameter is wrong  ", i_ReturnValue);
			break;

	   case -2:
			printf("\ni_PCI1500_SetBoardIntRoutine         error");
			printf("\nError = %d.  An interrupt routine was still isntalled. Remove it with i_PCI1500_ResetBoardIntRoutine and retry   ", i_ReturnValue);
			break;
			
	   case -3:
			printf("\ni_PCI1500_SetBoardIntRoutine         error");
			printf("\nError = %d.  Error while creating kill event   ", i_ReturnValue);
			break;

	   case -4:
			printf("\ni_PCI1500_SetBoardIntRoutine         error");
			printf("\nError = %d.  Error while creating interrupt event  ", i_ReturnValue);
			break;			
			
	   case -5:
			printf("\ni_PCI1500_SetBoardIntRoutine         error");
			printf("\nError = %d.  Error while creating interrupt thread   ", i_ReturnValue);
			break;

	   case -6:
			printf("\ni_PCI1500_SetBoardIntRoutine         error");
			printf("\nError = %d.  Error while changing the priority class of the thread   ", i_ReturnValue);
			break;
			
	   case -7:
			printf("\ni_PCI1500_SetBoardIntRoutine         error");
			printf("\nError = %d.  Error while changing the priority of the thread   ", i_ReturnValue);
			break;

	   case -8:
			printf("\ni_PCI1500_SetBoardIntRoutine         error");
			printf("\nError = %d.  Error while calling the IOCTL command  ", i_ReturnValue);
			break;			
			
	   case -9:
			printf("\ni_PCI1500_SetBoardIntRoutine         error");
			printf("\nError = %d.  Error in the interrupt callback function   ", i_ReturnValue);
			break;			
			
	   default:
			printf("\ni_PCI1500_SetBoardIntRoutine          error");
			printf("\nERROR = %d", i_ReturnValue);
       }

       
	 
	 
	   /* Initializes the input clock used for timers and watchdog   */  
	   i_ReturnValue = i_PCI1500_InitTimerInputClock(b_BoardHandle, 
											  b_InputClockSelected);
       switch (i_ReturnValue)
       {
	   case  0:
			printf("\ni_PCI1500_InitTimerInputClock        OK");
			break;

	   case -1:
			printf("\ni_PCI1500_InitTimerInputClock        error");
			printf("\nError = %d.  The selected clock index is wrong    ", i_ReturnValue);
			break;

	   case -2:
			printf("\ni_PCI1500_InitTimerInputClock         error");
			printf("\nError = %d.  Error while calling IOCTL function (wrong handle ?)    ", i_ReturnValue);
			break;
			
	   default:
			printf("\ni_PCI1500_InitTimerInputClock          error");
			printf("\nERROR = %d", i_ReturnValue);
       } 	 
	 
	 
	 
   /*********************************************/
   /* Reads in the l_ReloadValue; Does it again */
   /* if the value is not between 1 and 65535   */
   /*********************************************/
   printf("\n\nPlease enter the division factor!\n");
   printf("The value must be between 1 and 65535:");
   do
   {
     if (i_Range == 1)
	 {
       printf("Value not between 1 and 65535:");
	 }
     ScanIn("%i", &w_ReloadValue);
     i_Range = 1;
   }
   while ((0L >= w_ReloadValue) || (w_ReloadValue >= 65535L));
	 
	 

   /***********************************************/
   /* Initializes the operation mode of the timer */
   /***********************************************/	 
	i_ReturnValue = i_PCI1500_InitTimerCounter1 	(b_BoardHandle ,
	 								 b_ComponentMode,
	 								 w_ReloadValue,
	       							 b_EnableContinuousCycle,
	       							 b_EnableInterrupt);
       
   switch (i_ReturnValue)
   {
   case  0:
		printf("\ni_PCI1500_InitTimerCounter1         OK");
		break;

   case -1:
		printf("\ni_PCI1500_InitTimerCounter1         error");
		printf("\nError = %d.  Invalid mode   ", i_ReturnValue);
		break;

   case -2:
		printf("\ni_PCI1500_InitTimerCounter1         error");
		printf("\nError = %d.  Wrong device handle    ", i_ReturnValue);
		break;
	
   case -3:
		printf("\ni_PCI1500_InitTimerCounter1         error");
		printf("\nError = %d.  Error while calling IOCTL function (wrong handle ?)    ", i_ReturnValue);
		break;
	
   default:
		printf("\ni_PCI1500_InitTimerCounter1          error");
		printf("\nERROR = %d", i_ReturnValue);
   }      
       
       
     printf("\n\nPress any key to start the timer!\n");
     printf("\nPress >ESC< to stop the timer!\n");
     GetKey();
     
     /**********************/
     /* Starts the timer 1 */
     /**********************/ 
     i_ReturnValue = i_PCI1500_StartTimerCounter1(b_BoardHandle);
     
	 switch (i_ReturnValue)
	 {
	   case 0:
	     printf ("\ni_PCI1500_StartTimerCounter1        OK");
	     break;

	   case -1:
	     printf ("\ni_PCI1500_StartTimerCounter1        error");
	     printf ("\nError = %d. Wrong device handle", i_ReturnValue);
	     break;

	   case -2:
	     printf ("\ni_PCI1500_StartTimerCounter1        error");
	     printf ("\nError = %d. The component is still started, stop it before trying to restart it ", i_ReturnValue);
	     break;
	     
	   case -3:
	     printf ("\ni_PCI1500_StartTimerCounter1        error");
	     printf ("\nError = %d. The component is not initialized ", i_ReturnValue);
	     break;

	   case -4:
	     printf ("\ni_PCI1500_StartTimerCounter1        error");
	     printf ("\nError = %d. Error while calling IOCTL function (wrong handle ?) ", i_ReturnValue);
	     break;


	   default:
	     printf ("\ni_APCI1500_StartTimerCounter        error");
	     printf ("\nError = %d", i_ReturnValue);
	   
	 } // switch (i_ReturnValue)



    /**************************************************/
     /* Reads the current value of the timer/counter 1 */
     /* Returns the current value of the timer/counter */
     /**************************************************/

     i_ReturnValue = i_PCI1500_ReadTimerCounter1 ( b_BoardHandle,
	                        				       &l_ReadValue);
     switch (i_ReturnValue)
	 {
	   case 0:
	     printf ("\ni_PCI1500_ReadTimerCounter1        OK");
	     break;

	   case -1:
	     printf ("\ni_PCI1500_ReadTimerCounter1        error");
	     printf ("\nError = %d. Wrong device handle", i_ReturnValue);
	     break;

	   case -2:
	     printf ("\ni_PCI1500_ReadTimerCounter1        error");
	     printf ("\nError = %d. Nothing is started on the component (so nothing to trigger) ", i_ReturnValue);
	     break;

	   case -3:
	     printf ("\ni_PCI1500_ReadTimerCounter1        error");
	     printf ("\nError = %d. Error while calling IOCTL function (wrong handle ?) ", i_ReturnValue);
	     break;

	   default:
	     printf ("\ni_APCI1500_ReadTimerCounter1        error");
	     printf ("\nError = %d", i_ReturnValue);
	     
	 } // switch (i_ReturnValue)


       /******************************************/
       /* Prints the current value of the timer. */
       /* Stops if the >ESC< is hidden           */
       /******************************************/
	 i_key = 1;
     do
	 {
	   i_ReturnValue = i_PCI1500_ReadTimerCounter1 ( b_BoardHandle,  &l_ReadValue);
	   printf("Timer value: %5u", l_ReadValue);
	   
	   printf("    Number of interrupts: %3u\n", b_TimerCounterCpt [0]);
	   if (KeyHit() == 1)
	   {
	     i_key = GetKey();
	   }
	 }
     while (i_key != 0x300);

     /*****************************/
     /* Stops the timer/counter 1 */
     /*****************************/

     i_ReturnValue = i_PCI1500_StopTimerCounter1  (b_BoardHandle);

	 switch (i_ReturnValue)
	 {
	   case 0:
	     printf ("\ni_APCI1500_StopTimerCounter1        OK");
	     break;

	   case -1:
	     printf ("\ni_APCI1500_StopTimerCounter1          error");
	     printf ("\nError = %d. Wrong device handle", i_ReturnValue);
	     break;

	   case -2:
	     printf ("\ni_APCI1500_StopTimerCounter1        error");
	     printf ("\nError = %d. Nothing is started on the component (so nothing to stop) ", i_ReturnValue);
	     break;

	   case -3:
	     printf ("\ni_APCI1500_StopTimerCounter1        error");
	     printf ("\nError = %d.  Error while calling IOCTL function (wrong handle ?) ", i_ReturnValue);
	     break;

	   default:
	     printf ("\ni_APCI1500_StopTimerCounter1        error");
	     printf ("\nError = %d", i_ReturnValue);
	     break;
	 } // switch (i_ReturnValue)

        /*****************************************/
        /* Deinstalls the User interrupt routine */
        /*****************************************/

        i_ReturnValue = i_PCI1500_ResetBoardIntRoutine (b_BoardHandle);

	    switch (i_ReturnValue)
		{
		  case 0:
		    printf ("\ni_APCI1500_ResetBoardIntRoutine     OK");
		    break;

		  case -1:
		    printf ("\ni_APCI1500_ResetBoardIntRoutine     error");
		    printf ("\nError = %d. The device handle parameter is wrong", i_ReturnValue);
		    break;

		  case -2:
		    printf ("\ni_APCI1500_ResetBoardIntRoutine     error");
		    printf ("\nError = %d. No interrupt routine installed !", i_ReturnValue);
		    break;

		  case -3:
		    printf ("\ni_PCI1500_ResetBoardIntRoutine     error");
		    printf ("\nError = %d. Error in the reset interrupt callback function !", i_ReturnValue);
		    break;

		  default:
		    printf ("\ni_APCI1500_ResetBoardIntRoutine     error");
		    printf ("\nError = %d", i_ReturnValue);
		    break;
		} // switch (i_ReturnValue)



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
