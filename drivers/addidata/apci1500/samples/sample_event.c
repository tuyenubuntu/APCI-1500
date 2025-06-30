/** @file sample_event.c
 
   This demonstarte how to use digital input event in user mode.
 
   @par CREATION  
   @author Krauth Julien
   @date   20.07.06
   
   @par VERSION
   @verbatim
   $LastChangedRevision:431 $
   $LastChangedDate:2007-04-24 10:28:56 +0200 (Tue, 24 Apr 2007) $
   @endverbatim   
   
   @par LICENCE
   @verbatim
   Copyright (C) 2004,2005  ADDI-DATA GmbH for the source code of this module.
        
        ADDI-DATA GmbH 
        Dieselstrasse 3 
        D-77833 Ottersweier 
        Tel: +19(0)7223/9493-0 
        Fax: +49(0)7223/9493-92 
        http://www.addi-data-com 
        info@addi-data.com 
        
   This program is free software; you can redistribute it and/or modify it under 
   the terms of the GNU General Public License as published by the Free Software 
   Foundation; either version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, 
   but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
   or FITNESS FOR A PARTICULAR PURPOSE. 
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along with 
   this program; if not, write to the Free Software Foundation, 
   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

   You shoud also find the complete GPL in the COPYING file 
   accompanying this source code.
   @endverbatim   
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/sysmacros.h> /* major() minor() */
#include <sys/time.h>
#include <apci1500.h>
#include <signal.h>
#include <errno.h>
#include <assert.h>
#include <pthread.h>

static int Stop;

//------------------------------------------------------------------------------

/**@struct thread_arg_t
 * 
 * This structure is used to transmit some parameters to threads.  
 */
struct thread_arg_t {
	
	int threadnbr;	/**< This is the minor ID of the board */
	int fd;			/**< File descriptor of the board */ 
}; 

//--------------------------------------------------------------------------------

/**@struct callback_irq_t
 * 
 * Contains informations of the board that call interrupt callback function.  
 */
struct callback_irq_t {
	
	int minor;				/**< Board minor number */
	int fd;					/**< Board file descriptor */
	int mask;				/**< mask of the interrupt source:<br>
								 1: Event on port 1 <br>
								 2: Event on port 2 <br>
								 4: Timer 1 <br>								 
								 8: Timer 2 <br>
								 0x7fffffff: Driver fifo full <br>
								 0x7ffffffe: Driver fifo empty
							*/
	unsigned long value; 	/**< Digital inputs status is read in the interrupt function.
								 Digital inputs status value is returned here. */   
};

//------------------------------------------------------------------------------
/** Filter the "." and ".." entries in the struct dirent 
 *  area set up by the scandir() function (utility function).
 */
int
get_real_dir_entry (const struct dirent * ent)
{
        if (! strcmp(ent->d_name,"."))
                return 0;
        if (! strcmp(ent->d_name,".."))
                return 0;
                                
        return 1;
}

//--------------------------------------------------------------------------------

/** this function look up for cards in the /proc/sys/apci1500/ directory 
* @param cards A pointer to the card area to fill
* @return The number of cards detected (may be zero if nor cards found).
*/
int apci1500_find_cards(int ** cards)
{
	struct dirent **eps;
	int cnt = 0; // number of card found
	
    char APCI_SPECIAL_FILE_DIR[255]={0};
    char proc_path_template[255]={0};

    /* search which node is available */
    {
		struct stat file_stat;
		const char PROC_PATH[]="/proc/sys/apci1500/";
		const char DEV_PATH[]="/dev/apci1500/";
		
        if (stat(PROC_PATH,&file_stat) == 0)
        {
            /* Kernel 2.4 */
            strncpy(APCI_SPECIAL_FILE_DIR, PROC_PATH, strlen(PROC_PATH));
            strcpy(proc_path_template, "%s%s/ctrl");
        }
        else if (stat(DEV_PATH,&file_stat) == 0)
        {
            /* Kernel 2.6 */
            strncpy(APCI_SPECIAL_FILE_DIR, DEV_PATH, strlen(DEV_PATH));
            strcpy(proc_path_template, "%s%s");
        }
        else
        {
            perror("fstat");
            exit(1);
        }
    }
	
	/* scan directory for card entry */
	if ( (cnt = scandir (APCI_SPECIAL_FILE_DIR, &eps, get_real_dir_entry , alphasort)) == -1 )
	{
		perror("scandir");
		return 0;
	}	
	
	if (cnt == 0) return 0;
	
	/* allocate cards area */
	if ( ! ( (*cards) = malloc( cnt * sizeof(int) ) ) )
	{
		perror("malloc");
		free(eps);
		return 0;
	}
	
	/* for each card entry, open it and store file descriptor in cards[] */
	{
		int i;
		for (i=0; i< cnt; i++)
		{
			int fd;
			char name[100];
			
			snprintf(name,sizeof(name),proc_path_template,APCI_SPECIAL_FILE_DIR,eps[i]->d_name);
			
			if ( ( fd = open(name, O_RDWR)) == -1 )
			{
				perror("open");
				exit(1);
			}			
									
			{
				struct stat file_stat;
				if ( fstat(fd,&file_stat) )
				{
					perror("fstat");
					exit(1);
				}			
				if (!S_ISCHR(file_stat.st_mode)) 
				{
					/* should never happen !*/
					printf("file %d is not a character device\n",i);
					exit(1);
				}
				printf("%s, major:%d minor:%d \n",name, major(file_stat.st_rdev),minor(file_stat.st_rdev));
			
				(*cards)[minor(file_stat.st_rdev)] = fd;
			} 
			/* index device file descriptor by the minor number */
		}		
	}
	return cnt;
}
//--------------------------------------------------------------------------------

/** Exit callback function.
 *
 * This function is called on Ctrl+c key combination.
 * It change the Stop flag status.
 */
static void v_ControlExit (int notused)
{
      Stop = 0;
      printf("Sample abort.\n");
}

//--------------------------------------------------------------------------------

/** Interrupt callback.
 * 
 * Centralized informations of all boards.
 */
void callback_irq (struct callback_irq_t board)
{
	/* 
	 * For test:
	 * When a signal is detected on a digital input,
	 * the first and second digital outputs are 
	 * set / reset altenatively.
	 * It is then possible with an oscilloscope 
	 * to compare the input and output signals.
	 */
	static int i = 0;
	i ^= 1;
	if ( ioctl( board.fd, CMD_APCI1500_Set1DigitalOutputOn, (i+1) ) )
		perror("ioctl");
	 	
	printf ("Interrupt on board %d mask %d inputs value 0x%lx.\n", board.minor, board.mask, board.value);

}

//--------------------------------------------------------------------------------

/** Board thread.
 * 
 * The driver manage separatly each APCI-1500.
 * Each board is initialized by it's own thread.
 * Once an interrupt occured in the kernel driver,
 * this thread is waked up, and call the global 
 * interrupt callback callback_irq.
 */
void * fn_thread (void * arg)
{
	struct thread_arg_t *thread_args = (struct thread_arg_t *) arg; 
	uint32_t dw_EventInfo [2];
	long port1 = 0;
	long port2 = 0;
	struct callback_irq_t board;
				
    /* Deprecated, initialization is done automatically in the driver */
	printf("CMD_APCI1500_SetBoardInformation\n");
	if ( ioctl( thread_args->fd, CMD_APCI1500_SetBoardInformation, NULL ) ) {
		perror("ioctl");
	}	

	/* The 3 next function are not necessary for the interrupt, they just switch all digital outputs off */
	printf("=> CMD_APCI1500_SetOutputMemoryOn\n");
	if ( ioctl( thread_args->fd, CMD_APCI1500_SetOutputMemoryOn, NULL ) ) {
		perror("ioctl");
	}

	printf("CMD_APCI1500_Set16DigitalOutputOff \n");
	if ( ioctl( thread_args->fd, CMD_APCI1500_Set16DigitalOutputOff, 0xFFFF ) ) {
		perror("ioctl");
	}

	printf("=> CMD_APCI1500_SetOutputMemoryOff\n");
	if ( ioctl( thread_args->fd, CMD_APCI1500_SetOutputMemoryOff, NULL ) ) {
		perror("ioctl");
	}
	
	printf("CMD_APCI1500_SetBoardIntRoutine\n");	
	if ( ioctl( thread_args->fd, CMD_APCI1500_SetBoardIntRoutine, NULL ) ) {
		perror("ioctl");
	}
			
	/* For the mask configuration, please see in apci1500.h */						
	port1 = MAKE_APCI1500_INPUT_EVENT_ARG_PORT1 (	APCI1500_INPUT_PORT_1, 
													APCI1500_OR, 
													"11111111");

	printf("CMD_APCI1500_SetInputEventMask on port 1\n");		
	if ( ioctl( thread_args->fd, CMD_APCI1500_SetInputEventMask, port1 ) ) {
		perror("ioctl");
	}	

	port2 = MAKE_APCI1500_INPUT_EVENT_ARG_PORT2 (	APCI1500_INPUT_PORT_2, 
													APCI1500_OR, 
													"111111");

	printf("CMD_APCI1500_SetInputEventMask on port 2\n");		
	if ( ioctl( thread_args->fd, CMD_APCI1500_SetInputEventMask, port2 ) ) {
		perror("ioctl");
	}	

	printf("CMD_APCI1500_StartInputEvent on port 1 and port 2\n");		
	if ( ioctl( thread_args->fd, CMD_APCI1500_StartInputEvent, (APCI1500_INPUT_PORT_1 | APCI1500_INPUT_PORT_2) ) ) {
		perror("ioctl");
	}	
		
	/* Put the thread in sleep state until an event is catched */
	printf("CMD_APCI1500_WaitInterrupt on board %d.\n", thread_args->threadnbr);
	while (Stop) {
	
		if ( ioctl( thread_args->fd, CMD_APCI1500_WaitInterrupt, dw_EventInfo) ) {
			perror("ioctl");
		}	

		/* Prepare the call of the interrupt callback */
		board.minor = thread_args->threadnbr;
		board.fd = thread_args->fd;
		board.mask = (int)dw_EventInfo[0];
		board.value = dw_EventInfo[1];
		callback_irq (board);
	}		

	pthread_exit(NULL);
}

//--------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	int ret = 0;
	int i = 0;
	int *fd;
	int nbr_boards = 0;
	pthread_t *thread = NULL;
	struct thread_arg_t *thread_args = NULL;
	
	Stop = 1;
	
	/* Search for APCI-1500 boards */
	if ((nbr_boards = apci1500_find_cards(&fd)) == 0) {
		printf("No APCI-1500 found\n");
		exit(EXIT_FAILURE);
	}
	
	thread = malloc (sizeof (pthread_t) * nbr_boards);	
	if (thread == NULL) {
		printf("Can't allocate memory for thread\n");
		exit(EXIT_FAILURE);
	}
	
	thread_args = malloc (sizeof (struct thread_arg_t) * nbr_boards);	
	if (thread_args == NULL) {
		printf("Can't allocate memory for thread_args\n");
		exit(EXIT_FAILURE);
	}	
	
	/* Set the v_ControlExit callback function on Ctrl+c key combination.
	 * Once Ctrl+C are pressed, the v_ControlExit function is called to end the 
	 * sample.
	 */
	signal (SIGINT, v_ControlExit);	
	
    for (i=0; i<nbr_boards; i++) {
		
		thread_args[i].threadnbr = i;	/**< This is the minor ID of the board */
		thread_args[i].fd = fd[i];		/**< File descriptor of the board */
		
		/* Create a thread for each board */
		if ((ret = pthread_create (&thread[i], NULL, fn_thread, &thread_args[i])) != 0) {
		   printf("%d : %s", i, strerror(ret));
		   exit(EXIT_FAILURE);
		}
		printf ("Create and start thread for board %d\n", i);
    }
    
	/* Wait Ctrl+c key combination */
	printf ("TO STOP THE SAMPLE PRESS CTRL+C\n");
	while (Stop) sleep(1);

	/* Stop threads */
    for (i=0; i<nbr_boards; i++) {
		pthread_cancel (thread[i]);
		
		printf("CMD_APCI1500_StopInputEvent on port 1 and port 2\n");		
		if ( ioctl( thread_args[i].fd, CMD_APCI1500_StopInputEvent, (APCI1500_INPUT_PORT_1 | APCI1500_INPUT_PORT_2) ) ) {
			perror("ioctl");
		}	
		
		printf("CMD_APCI1500_ResetBoardIntRoutine\n");	
		if ( ioctl( thread_args[i].fd, CMD_APCI1500_ResetBoardIntRoutine, NULL ) ) {
			perror("ioctl");
		}			
    }

    free (thread);
    free (thread_args);
	
	return 0;
}
