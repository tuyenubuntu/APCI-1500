/** @file sample_apci1500.c
*
* @author Sylvain Nahas
*
* @todo events, watchdog-zilog
*/

/** @par LICENCE
* @verbatim
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
* @endverbatim
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


#define TEST_SHOULD_PASS(__cmd,__name, __arg) \
{ \
	printf("=> %s\n",__name); \
	if ( ioctl( fd, __cmd, __arg ) ) \
	{ \
		perror("ioctl"); \
		FAILED();		\
	}\
} 

#define ASK_USER_IF_SUCCESS(__string) \
{ \
	{ \
		int done = 1; \
		while (done) \
		{ \
			printf(__string); \
			fflush(stdout);\
			{\
				char resp;\
				read(STDIN_FILENO,&resp,1);\
				printf("\n");\
				switch(resp)\
				{\
					case 'y':\
						done = 0;\
						break;\
					case 'n':\
						done = 0;\
						FAILED();\
						break;\
					default:\
						break;\
				} \
			} \
		} \
	}\
}


//------------------------------------------------------------------------------
void apci1500_run_test(int fd, char* command);
//------------------------------------------------------------------------------
int failed_tests = 0;
//------------------------------------------------------------------------------
void FAILED(void) 
{
	printf("failed\n");
	failed_tests++;
}
//------------------------------------------------------------------------------
int
timeval_subtract ( struct timeval * result, struct timeval * x, struct timeval * y)
{
	/* Perform the carry for the later subtraction by updating Y. */
	if (x->tv_usec < y->tv_usec) {
		int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
		y->tv_usec -= 1000000 * nsec;
		y->tv_sec += nsec;
	}
	if (x->tv_usec - y->tv_usec > 1000000) {
		int nsec = (x->tv_usec - y->tv_usec) / 1000000;
		y->tv_usec += 1000000 * nsec;
		y->tv_sec -= nsec;
	}
	
	/* Compute the time remaining to wait.
		`tv_usec' is certainly positive. */
	result->tv_sec = x->tv_sec - y->tv_sec;
	result->tv_usec = x->tv_usec - y->tv_usec;
	
	/* Return 1 if result is negative. */
	return x->tv_sec < y->tv_sec;
}


//------------------------------------------------------------------------------
/** Filter the "." and ".." entries in the struct dirent ** area set up by the scandir() function (utility function).*/
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
			char name[512];
			
			snprintf(name,sizeof(name),"%s%s",APCI_SPECIAL_FILE_DIR,eps[i]->d_name);
			
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


//--------------------------------------------------------------------------------
/* Test timer 1 function */
void apci1500_test_timer1(int fd)
{
	struct timeval begin;
	struct timeval end;
	int interrupted = 0;
	
	void apci1500_signal_timer1(int a)
	{
		printf("=> %s\n",__FUNCTION__);
		gettimeofday(&end, NULL);
		interrupted = 1;
	}

	printf("\n\t+++++++++++++++++++++++++++++++++++++\n\t Test of timer 1 \n\t+++++++++++++++++++++++++++++++++++++\n\n\n");
	
	/* APCI1500_1_8_KHZ */
	printf("\n=> APCI1500_1_8_KHZ\n");
	{
		unsigned long freq = APCI1500_1_8_KHZ;
		/* init timer input clock*/
		printf("=> CMD_APCI1500_InitTimerInputClock with APCI1500_1_8_KHZ\n");
		
		if ( ioctl( fd, CMD_APCI1500_InitTimerInputClock, freq ) )
		{
			perror("ioctl");
			FAILED();
		}
		/* activate Driver's interrupt Handler*/
		{
			printf("=> CMD_APCI1500_SetBoardIntRoutine\n");
			if ( ioctl( fd, CMD_APCI1500_SetBoardIntRoutine, NULL ) )
			{
				perror("ioctl");
				FAILED();
			}

		}
		/* request asynchronous SIGIO */
		{
			printf("=> Requesting SIGIO notification\n");
			if (signal(SIGIO,&apci1500_signal_timer1) == SIG_ERR)
			{
				perror("signal");
				FAILED();
			}
			if (fcntl(fd, F_SETOWN, getpid()) == -1)
			{
				perror("fcntl");
				FAILED();				
			}
			{
				int oflags = fcntl(fd, F_GETFL);
				if ( fcntl(fd, F_SETFL, oflags | FASYNC) == -1)
				{
					perror("fcntl");
					FAILED();							
				}
			}
		}
		
		/* Enable / disable the timer / counter 1 interrupt */
		printf("=> CMD_APCI1500_EnableDisableTimerCounter1Interrupt\n");		
		if ( ioctl( fd, CMD_APCI1500_EnableDisableTimerCounter1Interrupt, APCI1500_ENABLE ) )
		{
			perror("ioctl");
			FAILED();				
		}	
				
		/* configure timer 1 with reload value 1747 (1 seconde)  */
		{
			short us_TimerMode = APCI1500_TIMER | APCI1500_CONTINUOUS;
			short us_ReloadValue = 1747; // 2 seconde
			long argInit = MAKELONG( us_TimerMode, us_ReloadValue );
			printf("=> CMD_APCI1500_InitTimerCounter1\n");		
			if ( ioctl( fd, CMD_APCI1500_InitTimerCounter1, argInit ) )
			{
				perror("ioctl");
				FAILED();				
			}						
  		}
		/* start timer */
		{
			printf("=> CMD_APCI1500_StartTimerCounter1\n");		
			gettimeofday(&begin, NULL);
			if ( ioctl( fd, CMD_APCI1500_StartTimerCounter1, NULL ) )
			{
				perror("ioctl");
				FAILED();
			}
		}
		sleep(3); // should be interrupted by SIGIO
		if (!interrupted)
		{
			printf("SIGIO not caught\n");
			FAILED();
		}
		/* stop timer 1 */
		{
			printf("=> CMD_APCI1500_StopTimerCounter1\n");
			if ( ioctl( fd, CMD_APCI1500_StopTimerCounter1, 0 ) )
			{
				perror("ioctl");
				FAILED();
			}
		}
		/* calculate difference between begin and timer 1 signal */
		{
			struct timeval differ;
			if ( timeval_subtract(&differ,&end,&begin) )
			{
				printf("timeval_subtract returned a negative value\n");
				FAILED();
			}
			printf("interruption - begin = %lu s %lu microseconde (should be close to 2 seconds)\n",differ.tv_sec, differ.tv_usec);
		}
  	}
	/* APCI1500_3_6_KHZ */
	printf("\n=> APCI1500_3_6_KHZ\n");
	{
		unsigned long freq = APCI1500_3_6_KHZ;
		/* init timer input clock*/
		printf("=> CMD_APCI1500_InitTimerInputClock with APCI1500_3_6_KHZ\n");
		
		if ( ioctl( fd, CMD_APCI1500_InitTimerInputClock, freq ) )
		{
			perror("ioctl");
			FAILED();
		}
		/* activate Driver's interrupt Handler*/
		{
			printf("=> CMD_APCI1500_SetBoardIntRoutine\n");
			if ( ioctl( fd, CMD_APCI1500_SetBoardIntRoutine, NULL ) )
			{
				perror("ioctl");
				FAILED();
			}

		}
		/* request asynchronous SIGIO */
		{
			printf("=> Requesting SIGIO notification\n");
			if (signal(SIGIO,&apci1500_signal_timer1) == SIG_ERR)
			{
				perror("signal");
				FAILED();
			}
			if (fcntl(fd, F_SETOWN, getpid()) == -1)
			{
				perror("fcntl");
				FAILED();				
			}
			{
				int oflags = fcntl(fd, F_GETFL);
				if ( fcntl(fd, F_SETFL, oflags | FASYNC) == -1)
				{
					perror("fcntl");
					FAILED();							
				}
			}
		}
		
		/* Enable / disable the timer / counter 1 interrupt */
		printf("=> CMD_APCI1500_EnableDisableTimerCounter1Interrupt\n");		
		if ( ioctl( fd, CMD_APCI1500_EnableDisableTimerCounter1Interrupt, APCI1500_ENABLE ) )
		{
			perror("ioctl");
			FAILED();				
		}			
		
		/* configure timer 1 with reload value 1747 (1 seconde)  */
		{	
			short us_TimerMode = APCI1500_TIMER | APCI1500_CONTINUOUS;
			short us_ReloadValue = 3490; // 2 seconde
			long argInit = MAKELONG( us_TimerMode, us_ReloadValue );
			printf("=> CMD_APCI1500_InitTimerCounter1\n");				
			if ( ioctl( fd, CMD_APCI1500_InitTimerCounter1, argInit ) )
			{
				perror("ioctl");
				FAILED();				
			}						
  		}
		/* start timer */
		{
			printf("=> CMD_APCI1500_StartTimerCounter1\n");		
			gettimeofday(&begin, NULL);
			if ( ioctl( fd, CMD_APCI1500_StartTimerCounter1, NULL ) )
			{
				perror("ioctl");
				FAILED();
			}
		}
		sleep(3); // should be interrupted by SIGIO
		if (!interrupted)
		{
			printf("SIGIO not caught\n");
			FAILED();
		}
		/* stop timer 1 */
		{
			printf("=> CMD_APCI1500_StopTimerCounter1\n");
			if ( ioctl( fd, CMD_APCI1500_StopTimerCounter1, 0 ) )
			{
				perror("ioctl");
				FAILED();
			}
		}
		/* calculate difference between begin and timer 1 signal */
		{
			struct timeval differ;
			if ( timeval_subtract(&differ,&end,&begin) )
			{
				printf("timeval_subtract returned a negative value\n");
				FAILED();
			}
			printf("interruption - begin = %lu s %lu microseconde (should be close to 2 seconds)\n",differ.tv_sec, differ.tv_usec);
		}
  	}
	/* APCI1500_115_KHZ */
	printf("\n=> APCI1500_115_KHZ");
	{
		unsigned long freq = APCI1500_115_KHZ;
		/* init timer input clock*/
		printf("=> CMD_APCI1500_InitTimerInputClock with APCI1500_115_KHZ\n");
		
		if ( ioctl( fd, CMD_APCI1500_InitTimerInputClock, freq ) )
		{
			perror("ioctl");
			FAILED();
		}
		/* activate Driver's interrupt Handler*/
		{
			printf("=> CMD_APCI1500_SetBoardIntRoutine\n");
			if ( ioctl( fd, CMD_APCI1500_SetBoardIntRoutine, NULL ) )
			{
				perror("ioctl");
				FAILED();
			}

		}
		/* request asynchronous SIGIO */
		{
			printf("=> Requesting SIGIO notification\n");
			if (signal(SIGIO,&apci1500_signal_timer1) == SIG_ERR)
			{
				perror("signal");
				FAILED();
			}
			if (fcntl(fd, F_SETOWN, getpid()) == -1)
			{
				perror("fcntl");
				FAILED();				
			}
			{
				int oflags = fcntl(fd, F_GETFL);
				if ( fcntl(fd, F_SETFL, oflags | FASYNC) == -1)
				{
					perror("fcntl");
					FAILED();							
				}
			}
		}
		
		/* Enable / disable the timer / counter 1 interrupt */
		printf("=> CMD_APCI1500_EnableDisableTimerCounter1Interrupt\n");		
		if ( ioctl( fd, CMD_APCI1500_EnableDisableTimerCounter1Interrupt, APCI1500_ENABLE ) )
		{
			perror("ioctl");
			FAILED();				
		}			
		
		/* configure timer 1 with reload value 1747 (1 seconde)  */
		{
			short us_TimerMode = APCI1500_TIMER | APCI1500_CONTINUOUS;
			short us_ReloadValue = 0xFFFF; // maximum value hold in a 16 bits register
			long argInit = MAKELONG( us_TimerMode, us_ReloadValue );
			printf("=> CMD_APCI1500_InitTimerCounter1\n");		
			if ( ioctl( fd, CMD_APCI1500_InitTimerCounter1, argInit ) )
			{
				perror("ioctl");
				FAILED();				
			}						
  		}
		/* start timer */
		{
			printf("=> CMD_APCI1500_StartTimerCounter1\n");		
			gettimeofday(&begin, NULL);
			if ( ioctl( fd, CMD_APCI1500_StartTimerCounter1, NULL ) )
			{
				perror("ioctl");
				FAILED();
			}
		}
		sleep(3); // should be interrupted by SIGIO
		if (!interrupted)
		{
			printf("SIGIO not caught\n");
			FAILED();
		}
		/* stop timer 1 */
		{
			printf("=> CMD_APCI1500_StopTimerCounter1\n");
			if ( ioctl( fd, CMD_APCI1500_StopTimerCounter1, 0 ) )
			{
				perror("ioctl");
				FAILED();
			}
		}
		/* calculate difference between begin and timer 1 signal */
		{
			struct timeval differ;
			if ( timeval_subtract(&differ,&end,&begin) )
			{
				printf("timeval_subtract returned a negative value\n");
				FAILED();
			}
			printf("interruption - begin = %lu s %lu microseconde (should be close to 1.17 seconds)\n",differ.tv_sec, differ.tv_usec);
		}
  	}	
}
//--------------------------------------------------------------------------------
/* Test counter 1 function */
void apci1500_test_counter1(int fd)
{
	struct timeval begin;
	struct timeval end;
	int interrupted = 0;
	
	void apci1500_signal_counter1(int a)
	{
		printf("=> %s\n",__FUNCTION__);
		gettimeofday(&end, NULL);
		interrupted = 1;
	}

	printf("\n\t+++++++++++++++++++++++++++++++++++++\n\t Test of counter 1 \n\t+++++++++++++++++++++++++++++++++++++\n\n\n");
	

	/* activate Driver's interrupt Handler*/
	{
		printf("=> CMD_APCI1500_SetBoardIntRoutine\n");
		if ( ioctl( fd, CMD_APCI1500_SetBoardIntRoutine, NULL ) )
		{
			perror("ioctl");
			FAILED();
		}

	}
	/* request asynchronous SIGIO */
	{
		printf("=> Requesting SIGIO notification\n");
		if (signal(SIGIO,&apci1500_signal_counter1) == SIG_ERR)
		{
			perror("signal");
			FAILED();
		}
		if (fcntl(fd, F_SETOWN, getpid()) == -1)
		{
			perror("fcntl");
			FAILED();				
		}
		{
			int oflags = fcntl(fd, F_GETFL);
			if ( fcntl(fd, F_SETFL, oflags | FASYNC) == -1)
			{
				perror("fcntl");
				FAILED();							
			}
		}
	}
	
	/* Enable / disable the timer / counter 1 interrupt */
	printf("=> CMD_APCI1500_EnableDisableTimerCounter1Interrupt\n");		
	if ( ioctl( fd, CMD_APCI1500_EnableDisableTimerCounter1Interrupt, APCI1500_ENABLE ) )
	{
		perror("ioctl");
		FAILED();				
	}	
			
	/* configure TimerCounter as counter with reload value 1*/
	{
		short us_TimerMode = APCI1500_COUNTER | APCI1500_CONTINUOUS;
		short us_ReloadValue = 1; // 1 input
		long argInit = MAKELONG( us_TimerMode, us_ReloadValue );
		printf("=> CMD_APCI1500_InitTimerCounter1\n");				
		if ( ioctl( fd, CMD_APCI1500_InitTimerCounter1, argInit ) )
		{
			perror("ioctl");
			FAILED();				
		}						
	}
	/* start timer */
	{
		printf("=> CMD_APCI1500_StartTimerCounter1\n");		
		gettimeofday(&begin, NULL);
		if ( ioctl( fd, CMD_APCI1500_StartTimerCounter1, NULL ) )
		{
			perror("ioctl");
			FAILED();
		}
	}
	printf("I now wait for 5 seconds for one input on INPUT 14\n");
	sleep(5); // should be interrupted by SIGIO
	if (!interrupted)
	{
		printf("SIGIO not caught\n");
		FAILED();
	}	
	/* stop timer 1 */
	{
		printf("=> CMD_APCI1500_StopTimerCounter1\n");
		if ( ioctl( fd, CMD_APCI1500_StopTimerCounter1, 0 ) )
		{
			perror("ioctl");
			FAILED();
		}
	}
	/* calculate difference between begin and counter 1 signal */
	{
		struct timeval differ;
		if ( timeval_subtract(&differ,&end,&begin) )
		{
			printf("timeval_subtract returned a negative value\n");
			FAILED();
		}
		printf("interruption - begin = %lu s %lu microseconde \n",differ.tv_sec, differ.tv_usec);
	}

}
//--------------------------------------------------------------------------------
/* Test counter 2 function */
void apci1500_test_counter2(int fd)
{
	struct timeval begin;
	struct timeval end;
	int interrupted = 0;
	
	void apci1500_signal_counter2(int a)
	{
		printf("=> %s\n",__FUNCTION__);
		gettimeofday(&end, NULL);
		interrupted = 1;
	}

	printf("\n\t+++++++++++++++++++++++++++++++++++++\n\t Test of counter 2 \n\t+++++++++++++++++++++++++++++++++++++\n\n\n");
	
	/* activate Driver's interrupt Handler*/
	TEST_SHOULD_PASS(CMD_APCI1500_SetBoardIntRoutine,"CMD_APCI1500_SetBoardIntRoutine",NULL);

	/* request asynchronous SIGIO */
	{
		printf("=> Requesting SIGIO notification\n");
		if (signal(SIGIO,&apci1500_signal_counter2) == SIG_ERR)
		{
			perror("signal");
			FAILED();
		}
		if (fcntl(fd, F_SETOWN, getpid()) == -1)
		{
			perror("fcntl");
			FAILED();				
		}
		{
			int oflags = fcntl(fd, F_GETFL);
			if ( fcntl(fd, F_SETFL, oflags | FASYNC) == -1)
			{
				perror("fcntl");
				FAILED();							
			}
		}
	}
	
	/* Enable / disable the timer / counter 2 interrupt */
	printf("=> CMD_APCI1500_EnableDisableTimerCounter2Interrupt\n");		
	if ( ioctl( fd, CMD_APCI1500_EnableDisableTimerCounter2Interrupt, APCI1500_ENABLE ) )
	{
		perror("ioctl");
		FAILED();				
	}	
			
	/* configure TimerCounter as counter with reload value 1*/
	{

		short us_TimerMode = APCI1500_COUNTER | APCI1500_CONTINUOUS | APCI1500_SOFTWARE_TRIGGER | APCI1500_SOFTWARE_GATE ;
		short us_ReloadValue = 1; // 1 input
		long argInit = MAKELONG( us_TimerMode, us_ReloadValue );
		
		TEST_SHOULD_PASS(CMD_APCI1500_InitTimerCounter2,"CMD_APCI1500_InitTimerCounter2",argInit);
		
	}
	/* start timer */

	TEST_SHOULD_PASS(CMD_APCI1500_StartTimerCounter2,"CMD_APCI1500_StartTimerCounter2",NULL);

	gettimeofday(&begin, NULL);
	
	printf("I now wait for 5 seconds for one input on INPUT 10\n");
	sleep(5); // should be interrupted by SIGIO
	if (!interrupted)
	{
		printf("SIGIO not caught\n");
		FAILED();
	}	

	/* stop timer 1 */
	TEST_SHOULD_PASS(CMD_APCI1500_StopTimerCounter2,"CMD_APCI1500_StopTimerCounter2",NULL);

	/* calculate difference between begin and counter 1 signal */
	{
		struct timeval differ;
		if ( timeval_subtract(&differ,&end,&begin) )
		{
			printf("timeval_subtract returned a negative value\n");
			FAILED();
		}
		printf("interruption - begin = %lu s %lu microseconde \n",differ.tv_sec, differ.tv_usec);
	}

}
//--------------------------------------------------------------------------------
/* Test counter 3 function */
void apci1500_test_counter3(int fd)
{
	struct timeval begin;
	struct timeval end;
	int interrupted = 0;
	
	void apci1500_signal_counter3(int a)
	{
		printf("=> %s\n",__FUNCTION__);
		gettimeofday(&end, NULL);
		interrupted = 1;
	}

	printf("\n\t+++++++++++++++++++++++++++++++++++++\n\t Test of counter 3 \n\t+++++++++++++++++++++++++++++++++++++\n\n\n");
	
	/* activate Driver's interrupt Handler*/
	TEST_SHOULD_PASS(CMD_APCI1500_SetBoardIntRoutine,"CMD_APCI1500_SetBoardIntRoutine",NULL);

	/* request asynchronous SIGIO */
	{
		printf("=> Requesting SIGIO notification\n");
		if (signal(SIGIO,&apci1500_signal_counter3) == SIG_ERR)
		{
			perror("signal");
			FAILED();
		}
		if (fcntl(fd, F_SETOWN, getpid()) == -1)
		{
			perror("fcntl");
			FAILED();				
		}
		{
			int oflags = fcntl(fd, F_GETFL);
			if ( fcntl(fd, F_SETFL, oflags | FASYNC) == -1)
			{
				perror("fcntl");
				FAILED();							
			}
		}
	}
	
	/* Enable / disable the timer / watchdog 3 interrupt */
	printf("=> CMD_APCI1500_EnableDisableWatchdogCounter3Interrupt\n");		
	if ( ioctl( fd, CMD_APCI1500_EnableDisableWatchdogCounter3Interrupt, APCI1500_ENABLE ) )
	{
		perror("ioctl");
		FAILED();				
	}
		
	/* configure TimerCounter as counter with reload value 1*/
	{	
		short us_TimerMode = APCI1500_COUNTER | APCI1500_CONTINUOUS;
		short us_ReloadValue = 1; // 1 input
		long argInit = MAKELONG( us_TimerMode, us_ReloadValue );
		TEST_SHOULD_PASS(CMD_APCI1500_InitWatchdogCounter3,"CMD_APCI1500_InitWatchdogCounter3",argInit);
	}
	/* start timer */
	{
		gettimeofday(&begin, NULL);
		TEST_SHOULD_PASS(CMD_APCI1500_StartCounter3,"CMD_APCI1500_StartCounter3",NULL);
	}
	printf("I now wait for 5 seconds for one input on INPUT 15\n");
	sleep(5); // should be interrupted by SIGIO
	if (!interrupted)
	{
		printf("SIGIO not caught\n");
		FAILED();
	}	
	
	/* stop timer 1 */
	TEST_SHOULD_PASS(CMD_APCI1500_StopCounter3,"CMD_APCI1500_StopCounter3",NULL);
	
	/* calculate difference between begin and counter 1 signal */
	{
		struct timeval differ;
		if ( timeval_subtract(&differ,&end,&begin) )
		{
			printf("timeval_subtract returned a negative value\n");
			FAILED();
		}
		printf("interruption - begin = %lu s %lu microseconde \n",differ.tv_sec, differ.tv_usec);
	}

}
//--------------------------------------------------------------------------------
/* Test timer 2 function */
void apci1500_test_timer2(int fd)
{
	struct timeval begin;
	struct timeval end;
	int interrupted = 0;
	
	void apci1500_signal_timer2(int a)
	{
		printf("=> %s\n",__FUNCTION__);
		gettimeofday(&end, NULL);
		interrupted = 1;
	}

	printf("\n\t+++++++++++++++++++++++++++++++++++++\n\t Test of timer 2 \n\t+++++++++++++++++++++++++++++++++++++\n\n\n");
	
	/* APCI1500_1_8_KHZ */
	printf("\n=> APCI1500_1_8_KHZ\n");
	{
		unsigned long freq = APCI1500_1_8_KHZ;
		/* init timer input clock*/		
		TEST_SHOULD_PASS(CMD_APCI1500_InitTimerInputClock,"CMD_APCI1500_InitTimerInputClock with APCI1500_1_8_KHZ",freq);
		
		/* activate Driver's interrupt Handler*/
		{
			printf("=> CMD_APCI1500_SetBoardIntRoutine\n");
			if ( ioctl( fd, CMD_APCI1500_SetBoardIntRoutine, NULL ) )
			{
				perror("ioctl");
				FAILED();
			}

		}
		/* request asynchronous SIGIO */
		{
			printf("=> Requesting SIGIO notification\n");
			if (signal(SIGIO,&apci1500_signal_timer2) == SIG_ERR)
			{
				perror("signal");
				FAILED();
			}
			if (fcntl(fd, F_SETOWN, getpid()) == -1)
			{
				perror("fcntl");
				FAILED();				
			}
			{
				int oflags = fcntl(fd, F_GETFL);
				if ( fcntl(fd, F_SETFL, oflags | FASYNC) == -1)
				{
					perror("fcntl");
					FAILED();							
				}
			}
		}
		
		/* Enable / disable the timer / counter 2 interrupt */
		printf("=> CMD_APCI1500_EnableDisableTimerCounter2Interrupt\n");		
		if ( ioctl( fd, CMD_APCI1500_EnableDisableTimerCounter2Interrupt, APCI1500_ENABLE ) )
		{
			perror("ioctl");
			FAILED();				
		}
			
		/* configure timer 2 with reload value 1747 (1 seconde)  */
		{	
			short us_TimerMode = APCI1500_TIMER | APCI1500_CONTINUOUS;
			short us_ReloadValue = 1747; // 2 seconde
			long argInit = MAKELONG( us_TimerMode, us_ReloadValue );
			printf("=> CMD_APCI1500_InitTimerCounter2\n");			
			if ( ioctl( fd, CMD_APCI1500_InitTimerCounter2, argInit ) )
			{
				perror("ioctl");
				FAILED();				
			}						
  		}
		/* start timer */
		{
			printf("=> CMD_APCI1500_StartTimerCounter2\n");		
			gettimeofday(&begin, NULL);
			if ( ioctl( fd, CMD_APCI1500_StartTimerCounter2, NULL ) )
			{
				perror("ioctl");
				FAILED();
			}
		}
		sleep(3); // should be interrupted by SIGIO
		if (!interrupted)
		{
			printf("SIGIO not caught\n");
			FAILED();
		}
		/* stop timer 1 */
		{
			printf("=> CMD_APCI1500_StopTimerCounter2\n");
			if ( ioctl( fd, CMD_APCI1500_StopTimerCounter2, 0 ) )
			{
				perror("ioctl");
				FAILED();
			}
		}
		/* calculate difference between begin and timer 1 signal */
		{
			struct timeval differ;
			if ( timeval_subtract(&differ,&end,&begin) )
			{
				printf("timeval_subtract returned a negative value\n");
				FAILED();
			}
			printf("interruption - begin = %lu s %lu microseconde (should be close to 2 seconds)\n",differ.tv_sec, differ.tv_usec);
		}
  	}
	/* APCI1500_3_6_KHZ */
	printf("\n=> APCI1500_3_6_KHZ\n");
	{
		unsigned long freq = APCI1500_3_6_KHZ;
		/* init timer input clock*/
		printf("=> CMD_APCI1500_InitTimerInputClock with APCI1500_3_6_KHZ\n");
		
		if ( ioctl( fd, CMD_APCI1500_InitTimerInputClock, freq ) )
		{
			perror("ioctl");
			FAILED();
		}
		/* activate Driver's interrupt Handler*/
		{
			printf("=> CMD_APCI1500_SetBoardIntRoutine\n");
			if ( ioctl( fd, CMD_APCI1500_SetBoardIntRoutine, NULL ) )
			{
				perror("ioctl");
				FAILED();
			}

		}
		/* request asynchronous SIGIO */
		{
			printf("=> Requesting SIGIO notification\n");
			if (signal(SIGIO,&apci1500_signal_timer2) == SIG_ERR)
			{
				perror("signal");
				FAILED();
			}
			if (fcntl(fd, F_SETOWN, getpid()) == -1)
			{
				perror("fcntl");
				FAILED();				
			}
			{
				int oflags = fcntl(fd, F_GETFL);
				if ( fcntl(fd, F_SETFL, oflags | FASYNC) == -1)
				{
					perror("fcntl");
					FAILED();							
				}
			}
		}
		
		/* Enable / disable the timer / counter 2 interrupt */
		printf("=> CMD_APCI1500_EnableDisableTimerCounter2Interrupt\n");		
		if ( ioctl( fd, CMD_APCI1500_EnableDisableTimerCounter2Interrupt, APCI1500_ENABLE ) )
		{
			perror("ioctl");
			FAILED();				
		}
			
		/* configure timer 2 with reload value 1747 (1 seconde)  */
		{
			short us_TimerMode = APCI1500_TIMER | APCI1500_CONTINUOUS;
			short us_ReloadValue = 3490; // 2 seconde
			long argInit = MAKELONG( us_TimerMode, us_ReloadValue );
			printf("=> CMD_APCI1500_InitTimerCounter2\n");	
			if ( ioctl( fd, CMD_APCI1500_InitTimerCounter2, argInit ) )
			{
				perror("ioctl");
				FAILED();				
			}						
  		}
		/* start timer */
		{
			printf("=> CMD_APCI1500_StartTimerCounter2\n");		
			gettimeofday(&begin, NULL);
			if ( ioctl( fd, CMD_APCI1500_StartTimerCounter2, NULL ) )
			{
				perror("ioctl");
				FAILED();
			}
		}
		sleep(3); // should be interrupted by SIGIO
		if (!interrupted)
		{
			printf("SIGIO not caught\n");
			FAILED();
		}
		/* stop timer 1 */
		{
			printf("=> CMD_APCI1500_StopTimerCounter2\n");
			if ( ioctl( fd, CMD_APCI1500_StopTimerCounter2, 0 ) )
			{
				perror("ioctl");
				FAILED();
			}
		}
		/* calculate difference between begin and timer 1 signal */
		{
			struct timeval differ;
			if ( timeval_subtract(&differ,&end,&begin) )
			{
				printf("timeval_subtract returned a negative value\n");
				FAILED();
			}
			printf("interruption - begin = %lu s %lu microseconde (should be close to 2 seconds)\n",differ.tv_sec, differ.tv_usec);
		}
  	}
	/* APCI1500_115_KHZ */
	printf("\n=> APCI1500_115_KHZ");
	{
		unsigned long freq = APCI1500_115_KHZ;
		/* init timer input clock*/
		printf("=> CMD_APCI1500_InitTimerInputClock with APCI1500_115_KHZ\n");
		
		if ( ioctl( fd, CMD_APCI1500_InitTimerInputClock, freq ) )
		{
			perror("ioctl");
			FAILED();
		}
		/* activate Driver's interrupt Handler*/
		{
			printf("=> CMD_APCI1500_SetBoardIntRoutine\n");
			if ( ioctl( fd, CMD_APCI1500_SetBoardIntRoutine, NULL ) )
			{
				perror("ioctl");
				FAILED();
			}

		}
		/* request asynchronous SIGIO */
		{
			printf("=> Requesting SIGIO notification\n");
			if (signal(SIGIO,&apci1500_signal_timer2) == SIG_ERR)
			{
				perror("signal");
				FAILED();
			}
			if (fcntl(fd, F_SETOWN, getpid()) == -1)
			{
				perror("fcntl");
				FAILED();				
			}
			{
				int oflags = fcntl(fd, F_GETFL);
				if ( fcntl(fd, F_SETFL, oflags | FASYNC) == -1)
				{
					perror("fcntl");
					FAILED();							
				}
			}
		}
		
		/* Enable / disable the timer / counter 2 interrupt */
		printf("=> CMD_APCI1500_EnableDisableTimerCounter2Interrupt\n");		
		if ( ioctl( fd, CMD_APCI1500_EnableDisableTimerCounter2Interrupt, APCI1500_ENABLE ) )
		{
			perror("ioctl");
			FAILED();				
		}
				
		/* configure timer 2 with reload value 1747 (1 seconde)  */
		{
			short us_TimerMode = APCI1500_TIMER | APCI1500_CONTINUOUS;
			short us_ReloadValue = 0xFFFF; // maximum value hold in a 16 bits register
			long argInit = MAKELONG( us_TimerMode, us_ReloadValue );
			printf("=> CMD_APCI1500_InitTimerCounter2\n");		
			if ( ioctl( fd, CMD_APCI1500_InitTimerCounter2, argInit ) )
			{
				perror("ioctl");
				FAILED();				
			}						
  		}
		/* start timer */
		{
			printf("=> CMD_APCI1500_StartTimerCounter2\n");		
			gettimeofday(&begin, NULL);
			if ( ioctl( fd, CMD_APCI1500_StartTimerCounter2, NULL ) )
			{
				perror("ioctl");
				FAILED();
			}
		}
		sleep(3); // should be interrupted by SIGIO
		if (!interrupted)
		{
			printf("SIGIO not caught\n");
			FAILED();
		}
		/* stop timer 2 */
		{
			printf("=> CMD_APCI1500_StopTimerCounter2\n");
			if ( ioctl( fd, CMD_APCI1500_StopTimerCounter2, 0 ) )
			{
				perror("ioctl");
				FAILED();
			}
		}
		/* calculate difference between begin and timer 2 signal */
		{
			struct timeval differ;
			if ( timeval_subtract(&differ,&end,&begin) )
			{
				printf("timeval_subtract returned a negative value\n");
				FAILED();
			}
			printf("interruption - begin = %lu s %lu microseconde (should be close to 1.17 seconds)\n",differ.tv_sec, differ.tv_usec);
		}
  	}	
	

}


//--------------------------------------------------------------------------------
void apci1500_test_output(int fd)
{
	printf("\n\t+++++++++++++++++++++++++++++++++++++\n\t CMD_APCI1500_Set1DigitalOutput On/Off \n\t+++++++++++++++++++++++++++++++++++++\n\n\n");
	
	printf("\n\t => Test with CMD_APCI1500_SetOutputMemoryOff\n\n");
	
	if ( ioctl( fd, CMD_APCI1500_SetOutputMemoryOff, NULL ) )
	{
		perror("ioctl");
		FAILED();		
	}
	{
		char channel = 0;
		 		
 		{
 			printf("=> Set1DigitalOutputOff %d\n",channel);
 			if ( !ioctl( fd, CMD_APCI1500_Set1DigitalOutputOff, channel ) )
 			{
				printf("(should fail)\n");
				FAILED(); 				
 			}
			else
			{
				perror("ioctl");
			}
 		}
					
		for( channel=1; channel<=16; channel++ ) 
		{
			printf("=> CMD_APCI1500_Set1DigitalOutputOn %d\n",channel);
			if ( ioctl( fd, CMD_APCI1500_Set1DigitalOutputOn, channel ) )
			{
				perror("ioctl");
				FAILED();			
			}
			usleep(200000);
		}
	}
	
	printf("\n\t => Test with CMD_APCI1500_SetOutputMemoryOn\n\n");
	
	printf("=> CMD_APCI1500_SetOutputMemoryOn\n");
	if ( ioctl( fd, CMD_APCI1500_SetOutputMemoryOn, NULL ) )
	{
		perror("ioctl");
		FAILED();		
	}
	{
		char channel;
		 		
		for( channel=1; channel<=16; channel++ ) 
 		{
 			printf("=> Set1DigitalOutputOff %d\n",channel);
 			if ( ioctl( fd, CMD_APCI1500_Set1DigitalOutputOff, channel ) )
 			{
 				perror("ioctl");
				FAILED();

 			}
 		}
					
		for( channel=1; channel<=16; channel++ ) 
		{
			printf("=> Set1DigitalOutputOn %d\n",channel);
			if ( ioctl( fd, CMD_APCI1500_Set1DigitalOutputOn, channel ) )
			{
				perror("ioctl");
				FAILED();	
			}
			usleep(200000);
		}
	}	

	/* 8 -------------------------------------------------------------*/	
	printf("\n\t => Test with CMD_APCI1500_SetOutputMemoryOff\n\n");
	
	if ( ioctl( fd, CMD_APCI1500_SetOutputMemoryOff, NULL ) )
	{
		perror("ioctl");
		FAILED();
	}
	{
		short port = 0;
 		{
 			printf("=> Set8DigitalOutputOff %d\n",port);
 			if ( ioctl( fd, CMD_APCI1500_Set8DigitalOutputOff, MAKEWORD(port,0xFF ) ) )
 			{
 				perror("ioctl");				

 			}
			else
			{
				printf("should have failed\n");
				FAILED();
			}
 		}
					
		for( port=1; port<=2; port++ ) 
		{
			printf("=> CMD_APCI1500_Set8DigitalOutputOn %d\n",port);
			if ( ioctl( fd, CMD_APCI1500_Set8DigitalOutputOn, MAKEWORD(port,0xFF) ) )
			{
				perror("ioctl");
				FAILED();
			}
			usleep(200000);
		}
	}
	
	printf("\n\t => Test with CMD_APCI1500_SetOutputMemoryOn\n\n");
	
	printf("=> CMD_APCI1500_SetOutputMemoryOn\n");
	if ( ioctl( fd, CMD_APCI1500_SetOutputMemoryOn, NULL ) )
	{
		perror("ioctl");
		FAILED();
	}
	{
		short port;
		 		
		for( port=1; port<=2; port++ ) 
 		{
 			printf("=> Set8DigitalOutputOff %d\n",port);
 			if ( ioctl( fd, CMD_APCI1500_Set8DigitalOutputOff, MAKEWORD(port,0xFF) ) )
 			{
 				perror("ioctl");
				FAILED();

 			}
 		}
					
		for( port=1; port<=2; port++ ) 
		{
			printf("=> Set8DigitalOutputOn %d\n",port);
			if ( ioctl( fd, CMD_APCI1500_Set8DigitalOutputOn, MAKEWORD(port,0xFF) ) )
			{
				perror("ioctl");
				FAILED();
			}
			usleep(200000);
		}
	}	

	/* 16 -------------------------------------------------------------*/	
	printf("\n\t => Test with CMD_APCI1500_SetOutputMemoryOff\n\n");
	
	if ( ioctl( fd, CMD_APCI1500_SetOutputMemoryOff, NULL ) )
	{
		perror("ioctl");
		FAILED();
	}
	{
		printf("=> Set16DigitalOutputOff \n");
		if ( ioctl( fd, CMD_APCI1500_Set16DigitalOutputOff, 0xFFFF ) )
		{
			perror("ioctl");			
		}
		else
		{
			printf("should have failed\n");
			FAILED();
		}

		printf("=> CMD_APCI1500_Set16DigitalOutputOn\n");
		if ( ioctl( fd, CMD_APCI1500_Set16DigitalOutputOn, 0xFFFF ) )
		{
			perror("ioctl");
			FAILED();
		}
		usleep(200000);

	}
	
	printf("\n\t => Test with CMD_APCI1500_SetOutputMemoryOn\n\n");
	
	printf("=> CMD_APCI1500_SetOutputMemoryOn\n");
	if ( ioctl( fd, CMD_APCI1500_SetOutputMemoryOn, NULL ) )
	{
		perror("ioctl");
		FAILED();
	}
	{
		printf("=> Set16DigitalOutputOff \n");
		if ( ioctl( fd, CMD_APCI1500_Set16DigitalOutputOff, 0xFFFF ) )
		{
			perror("ioctl");
			FAILED();

		}

		printf("=> CMD_APCI1500_Set16DigitalOutputOn \n");
		if ( ioctl( fd, CMD_APCI1500_Set16DigitalOutputOn, 0xFFFF ) )
		{
			perror("ioctl");
			FAILED();
		}
		usleep(200000);
		printf("=> CMD_APCI1500_Set16DigitalOutputOff \n");
		if ( ioctl( fd, CMD_APCI1500_Set16DigitalOutputOff, 0xFFFF ) )
		{
			perror("ioctl");
			FAILED();
		}
		usleep(200000);
		
	}	
}

/** timeout behaviour */
void apci1500_test_watchdog_universal_1(int fd)
{
	printf("\n=> WATCHDOG UNIVERSAL TEST 1 (timeout behaviour)\n");
	TEST_SHOULD_PASS(CMD_APCI1500_SetOutputMemoryOn,"CMD_APCI1500_SetOutputMemoryOn",NULL);
	TEST_SHOULD_PASS(CMD_APCI1500_InitTimerInputClock,"CMD_APCI1500_InitTimerInputClock with APCI1500_1_8_KHZ",APCI1500_1_8_KHZ);

	TEST_SHOULD_PASS(CMD_APCI1500_StopCounter3,"CMD_APCI1500_StopCounter3",NULL);	
	TEST_SHOULD_PASS(CMD_APCI1500_Set16DigitalOutputOn,"CMD_APCI1500_Set16DigitalOutputOn",0xFFFF);

	ASK_USER_IF_SUCCESS("LEDs should be on, are they ? [y,n]>");

	/* configure watchdog  */
	{
		short us_TimerMode = APCI1500_WATCHDOG;
		short us_ReloadValue = 1747; // 2 seconde // 1747
		long argInit = MAKELONG( us_TimerMode, us_ReloadValue );

		TEST_SHOULD_PASS(CMD_APCI1500_InitWatchdogCounter3,"CMD_APCI1500_InitWatchdogCounter3",argInit); // The function do a init and start
	}

	TEST_SHOULD_PASS(CMD_APCI1500_StopCounter3,"CMD_APCI1500_StopCounter3",NULL); // test the stop command
	printf("\n=> WATCHDOG UNIVERSAL DAUER TEST (long run)\n");
	sleep(5);

	printf("\n=> WATCHDOG UNIVERSAL DAUER TEST (long run)\n");
	TEST_SHOULD_PASS(CMD_APCI1500_StartCounter3,"CMD_APCI1500_StartCounter3",NULL);
		

	printf("Now trigger watchdog for environ 3 seconds\n");

	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);  				
	usleep( 500000 );  		
	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);  		
	usleep( 500000 );  		
	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);
	usleep( 500000 );
	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);
	usleep( 500000 );
	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);
	usleep( 500000 );
	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);
	usleep( 500000 );
	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);	
	usleep( 500000 );
	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);
	printf("waiting two seconds ()\n");
	sleep(2);
	// ask for user input
	ASK_USER_IF_SUCCESS("LEDs should be gone now, are they ? [y,n]>");



	TEST_SHOULD_PASS(CMD_APCI1500_Set16DigitalOutputOn,"CMD_APCI1500_Set16DigitalOutputOn",0xFFFF);

	ASK_USER_IF_SUCCESS("LEDs should still off now, are they ? [y,n]>");

	/* configure watchdog  */
	{

		short us_TimerMode = APCI1500_WATCHDOG;
		short us_ReloadValue = 1747; // 2 seconde
		long argInit = MAKELONG( us_TimerMode, us_ReloadValue );

		TEST_SHOULD_PASS(CMD_APCI1500_InitWatchdogCounter3,"CMD_APCI1500_InitWatchdogCounter3",argInit);
		
	}
	TEST_SHOULD_PASS(CMD_APCI1500_StopCounter3,"CMD_APCI1500_StopCounter3",NULL);
	TEST_SHOULD_PASS(CMD_APCI1500_Set16DigitalOutputOn,"CMD_APCI1500_Set16DigitalOutputOn",0xFFFF);

	ASK_USER_IF_SUCCESS("LEDs should be on, are they ? [y,n]>");	
}

/** timeout behaviour */
void apci1500_test_watchdog_universal_dauer_test(int fd)
{
	printf("\n=> WATCHDOG UNIVERSAL DAUER TEST (long run)\n");
	TEST_SHOULD_PASS(CMD_APCI1500_SetOutputMemoryOn,"CMD_APCI1500_SetOutputMemoryOn",NULL);	
	TEST_SHOULD_PASS(CMD_APCI1500_InitTimerInputClock, "CMD_APCI1500_InitTimerInputClock with APCI1500_1_8_KHZ",APCI1500_1_8_KHZ);


	/* configure watchdog  */
	{

		short us_TimerMode = APCI1500_WATCHDOG;
		short us_ReloadValue = 1747; // 2 seconde
		long argInit = MAKELONG( us_TimerMode, us_ReloadValue );

		TEST_SHOULD_PASS(CMD_APCI1500_InitWatchdogCounter3,"CMD_APCI1500_InitWatchdogCounter3",argInit);
		
	}
	
	TEST_SHOULD_PASS(CMD_APCI1500_Set16DigitalOutputOn,"CMD_APCI1500_Set16DigitalOutputOn",0xFFFF);

	while ( 1 )
	{
		TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);  				
		usleep( 500000 );  		
	}

}

//--------------------------------------------------------------------------------
/* start/stop fcn */
void apci1500_test_watchdog_universal_2(int fd)
{
	printf("\n=> WATCHDOG UNIVERSAL TEST 2 (watchdog start/stop)\n");	
	

	TEST_SHOULD_PASS(CMD_APCI1500_SetOutputMemoryOn,"CMD_APCI1500_SetOutputMemoryOn",NULL);	
	TEST_SHOULD_PASS(CMD_APCI1500_InitTimerInputClock, "CMD_APCI1500_InitTimerInputClock with APCI1500_1_8_KHZ",APCI1500_1_8_KHZ);


	/* configure watchdog  */
	{

		short us_TimerMode = APCI1500_WATCHDOG;
		short us_ReloadValue = 1747; // 2 seconde
		long argInit = MAKELONG( us_TimerMode, us_ReloadValue );

		TEST_SHOULD_PASS(CMD_APCI1500_InitWatchdogCounter3,"CMD_APCI1500_InitWatchdogCounter3",argInit);
		
	}
	TEST_SHOULD_PASS(CMD_APCI1500_Set16DigitalOutputOn,"CMD_APCI1500_Set16DigitalOutputOn",0xFFFF);

	printf("Now I trigger the watchdog for environ 3 seconds\n");
	
	usleep( 500000 );
	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);
	usleep( 500000 );
	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);
	usleep( 500000 );
	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);
	usleep( 500000 );
	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);
	usleep( 500000 );
	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);
	usleep( 500000 );
	TEST_SHOULD_PASS(CMD_APCI1500_TriggerWatchdog,"CMD_APCI1500_TriggerWatchdog",NULL);
	usleep( 500000 );
	TEST_SHOULD_PASS(CMD_APCI1500_StopCounter3,"CMD_APCI1500_StopCounter3",NULL);
	printf("waiting two seconds ()\n");
	sleep(2);
	// ask for user input
	ASK_USER_IF_SUCCESS("LEDs should always on now, are they ? [y,n]>");
	TEST_SHOULD_PASS(CMD_APCI1500_StartCounter3,"CMD_APCI1500_StartCounter3",NULL);		
	sleep(2);
	ASK_USER_IF_SUCCESS("LEDs should be off now, are they ? [y,n]>");	
	TEST_SHOULD_PASS(CMD_APCI1500_Set16DigitalOutputOn,"CMD_APCI1500_Set16DigitalOutputOn",0xFFFF);
	ASK_USER_IF_SUCCESS("LEDs should be still off now, are they ? [y,n]>");
}


//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------

void output_watchdog_state_str(unsigned long status)
{
		
	if (status & APCI1500_WATCHDOG_STATE_OVERFLOWED)
		printf("APCI1500_WATCHDOG_STATE_OVERFLOWED ");
		
	if (status & APCI1500_WATCHDOG_STATE_ENABLED )
		printf("APCI1500_WATCHDOG_STATE_ENABLED "); 

}


//--------------------------------------------------------------------------------
/* CMD_APCI1500_ReadTimer3/CMD_APCI1500_GetWatchdogStatus/CMD_APCI1500_GetWatchdogReloadValue */
void apci1500_test_watchdog_universal_3(int fd)
{
	printf("\n=> WATCHDOG UNIVERSAL TEST : CMD_APCI1500_ReadTimer3/CMD_APCI1500_GetWatchdogStatus/CMD_APCI1500_GetWatchdogReloadValue\n");	

	
	TEST_SHOULD_PASS(CMD_APCI1500_SetOutputMemoryOn,"CMD_APCI1500_SetOutputMemoryOn",NULL);	
	TEST_SHOULD_PASS(CMD_APCI1500_InitTimerInputClock, "CMD_APCI1500_InitTimerInputClock with APCI1500_1_8_KHZ",APCI1500_1_8_KHZ);


	/* get watchdog status */
	{
		unsigned long status = -1;
		TEST_SHOULD_PASS(CMD_APCI1500_GetWatchdogStatus,"CMD_APCI1500_GetWatchdogStatus",&status);
		printf("("); output_watchdog_state_str(status); printf(")\n");
	}
	
	{
		long currentwatchdogvalue = 0;
		TEST_SHOULD_PASS(CMD_APCI1500_ReadCounter3, "CMD_APCI1500_ReadTimer3",&currentwatchdogvalue);
		printf("current watchdog value = %ld\n",currentwatchdogvalue);
	}

	/* configure watchdog  */
	{

		short us_TimerMode = APCI1500_WATCHDOG;
		short us_ReloadValue = 800; // 1 seconde
		long argInit = MAKELONG( us_TimerMode, us_ReloadValue );

		TEST_SHOULD_PASS(CMD_APCI1500_InitWatchdogCounter3,"CMD_APCI1500_InitWatchdogCounter3",argInit);
		/* reload value */
		{
			unsigned long reloadvalue = 0;
			TEST_SHOULD_PASS(CMD_APCI1500_GetWatchdogReloadValue,"CMD_APCI1500_GetWatchdogReloadValue",&reloadvalue);
			printf("%ld\n", reloadvalue);
			assert(reloadvalue == us_ReloadValue);
		}		
		
	}

	/* get watchdog status */
	{
		unsigned long status = -1;
		TEST_SHOULD_PASS(CMD_APCI1500_GetWatchdogStatus,"CMD_APCI1500_GetWatchdogStatus",&status);
		printf("%ld\n",status);
		printf("("); output_watchdog_state_str(status); printf(")\n");
		assert(status == APCI1500_WATCHDOG_STATE_ENABLED);
		
	}	
	TEST_SHOULD_PASS(CMD_APCI1500_Set16DigitalOutputOn,"CMD_APCI1500_Set16DigitalOutputOn",0xFFFF);
	
	{
		int i = 0;
		for (i=0; i< 10; i++)
		{
			usleep( 100000 );
			{
				long currentwatchdogvalue = 0;
				TEST_SHOULD_PASS(CMD_APCI1500_ReadCounter3, "CMD_APCI1500_ReadTimer3",&currentwatchdogvalue);
				printf("current watchdog value = %ld\n",currentwatchdogvalue);

				//

				unsigned long status = -1;
				TEST_SHOULD_PASS(CMD_APCI1500_GetWatchdogStatus,"CMD_APCI1500_GetWatchdogStatus",&status);
				printf("("); output_watchdog_state_str(status); printf(")\n");

				//
			}			
		}		
	}
	/* get watchdog status */
	{
		unsigned long status = -1;
		TEST_SHOULD_PASS(CMD_APCI1500_GetWatchdogStatus,"CMD_APCI1500_GetWatchdogStatus",&status);
		printf("("); output_watchdog_state_str(status); printf(")\n");
		assert(status == APCI1500_WATCHDOG_STATE_OVERFLOWED);
	}
	
	

}
//--------------------------------------------------------------------------------
void apci1500_test_watchdog_universal(int fd)
{
	printf("\n\t+++++++++++++++++++++++++++++++++++++\n\t Test of universal watchdog \n\t+++++++++++++++++++++++++++++++++++++\n\n\n");

	printf("\n=> APCI1500_1_8_KHZ\n");

	apci1500_test_watchdog_universal_1(fd);
	apci1500_test_watchdog_universal_2(fd);	
	apci1500_test_watchdog_universal_3(fd);
}

//--------------------------------------------------------------------------------
/* CMD_APCI1500_Read1DigitalInput
CMD_APCI1500_Read8DigitalInput
CMD_APCI1500_Read16DigitalInput
*/
void apci1500_test_input(int fd)
{
	/* 1 dig IO */
	{
		unsigned char chan = 0;
		printf("\n=> CMD_APCI1500_Read1DigitalInput\n");
		for (chan=1; chan < 17; chan++ )
		{			

			unsigned int parm = chan;
			if ( ioctl(fd, CMD_APCI1500_Read1DigitalInput, &parm) )
			{
				perror("ioctl");
				FAILED();
			}
			printf("%d ",parm);
		}
		printf("\n");		
	}
	/* 8 dig IO */
	{
		unsigned char chan = 0;
		printf("\n=> CMD_APCI1500_Read8DigitalInput\n");
		for (chan=1; chan < 3; chan++ )
		{			
			unsigned int parm = chan;
			if ( ioctl(fd, CMD_APCI1500_Read8DigitalInput, &parm) )
			{
				perror("ioctl");
				FAILED();
			}
			printf("%d ",parm);
		}
		printf("\n");	
	}	
	/* 16 dig IO */
	{
		uint16_t chan = 0;
		printf("\n=> CMD_APCI1500_Read16DigitalInput\n");

		if ( ioctl(fd, CMD_APCI1500_Read16DigitalInput, &chan) )
		{
			perror("ioctl");
			FAILED();
		}
		printf("%d ",chan);
		
		printf("\n");	
	}	
	
}

//--------------------------------------------------------------------------------
/* CMD_APCI1500_CheckAndGetPCISlotNumber
CMD_APCI1500_SetBoardInformation
CMD_APCI1500_GetHardwareInformation
*/
void apci1500_test_basic(int fd) 
{
	printf("=> CMD_APCI1500_CheckAndGetPCISlotNumber\n");
	{	
		// deprecated (the number of boards is now unlimited and the OS gives actually these information)
		int nb = 0;
		char b_SlotArray[CONFIG_APCI1500_MAX_BOARD_NBR+1];
		if ( (nb = ioctl(fd,CMD_APCI1500_CheckAndGetPCISlotNumber,b_SlotArray)) == 0 )
		{
			printf("no boards found\n"); 
			FAILED();
		}
		else
		{
			printf("The driver advertise %d board\n", nb);
			
			{
				int i;
				for (i=0; i< nb; i++)
					printf ("\t%d: Slot Number                       : %d\n", i, b_SlotArray[i]);		
			}
		}
	}
	
	TEST_SHOULD_PASS(CMD_APCI1500_CheckAndGetPCISlotNumber,"CMD_APCI1500_CheckAndGetPCISlotNumber",NULL);

	/* Deprecated */
	TEST_SHOULD_PASS(CMD_APCI1500_SetBoardInformation,"CMD_APCI1500_SetBoardInformation",NULL);



	// deprecated (the OS gives actually these information)
	{
	str_BaseInformations s_BaseInformations;
	memset(&s_BaseInformations,0,sizeof(str_BaseInformations));
		
	TEST_SHOULD_PASS(CMD_APCI1500_GetHardwareInformation,"CMD_APCI1500_GetHardwareInformation",&s_BaseInformations);
		
	printf("\tBAR 0 : %d\n",  s_BaseInformations.ui_BaseAddress[0] ); 
	printf("\tBAR 1 : %d\n",  s_BaseInformations.ui_BaseAddress[1] ); 
	printf("\tBAR 2 : %d\n",  s_BaseInformations.ui_BaseAddress[2] ); 
	printf("\tBAR 3 : %d\n",  s_BaseInformations.ui_BaseAddress[3] ); 
	printf("\tBAR 5 : %d\n",  s_BaseInformations.ui_BaseAddress[4] ); 
	printf("\tinterrupt nb: %d\n", s_BaseInformations.b_Interrupt);
	printf("\tslot number: %d\n", s_BaseInformations.b_SlotNumber);
	}
}
//--------------------------------------------------------------------------------
void apci1500_test_timers(int fd)
{
	apci1500_test_timer1(fd);
	apci1500_test_timer2(fd);
}
//--------------------------------------------------------------------------------
void apci1500_test_counters(int fd)
{
	apci1500_test_counter1(fd);
	apci1500_test_counter2(fd);
	apci1500_test_counter3(fd);
}

//--------------------------------------------------------------------------------
void apci1500_test_all(int fd)
{
	apci1500_run_test(fd, "basic");
	apci1500_run_test(fd, "timers");	
	apci1500_run_test(fd, "counters");
	apci1500_run_test(fd, "output");
	apci1500_run_test(fd, "input");
}
//--------------------------------------------------------------------------------
void apci1500_test_help(int fd);
//--------------------------------------------------------------------------------

static struct {char* name; char * desc; void (*fc) (int) ;} commandtab[] =
{
	{	
		"basic",
		"(CMD_APCI1500_CheckAndGetPCISlotNumber, CMD_APCI1500_SetBoardInformation, CMD_APCI1500_GetHardwareInformation)",
		apci1500_test_basic
	},
	{	"timer1",
		"test timers 1 and SIGIO notification",
		apci1500_test_timer1
	},
	{	
		"timer2",
		"test timers 2 and SIGIO notification",
		apci1500_test_timer2
	},
	{
		"timers",
		"test timers 1, 2",
		apci1500_test_timers
	},
	{
		"output",
		"test output",
		apci1500_test_output
	},
	{
		"input",
		"test input",
		apci1500_test_input
	},
	{
		"counter1",
		"configure countertimer 1 as counter and wait for one input",
		apci1500_test_counter1
	},
	{
		"counter2",
		"configure countertimer 2 as counter and wait for one input",
		apci1500_test_counter2
	},
	{	
		"counter3",
		"test counter 3 and SIGIO notification",
		apci1500_test_counter3
	},		
	{
		"counters",
		"test for counter 1,2 and 3",
		apci1500_test_counters
	},
	{
		"help",
		"show this help",
		apci1500_test_help
	},
	{
		"watchdog-universal",
		"test watchdog universal functionality for some special cards",
		apci1500_test_watchdog_universal
	},
	{
		"wu-1",
		"test watchdog universal timeout behaviour",
		apci1500_test_watchdog_universal_1
	},	
	{
		"wu-2",
		"test watchdog universal start/stop",
		apci1500_test_watchdog_universal_2
	},		
	{
		"wu-3",
		"test watchdog universal (\n\tCMD_APCI1500_ReadTimer3\n\tCMD_APCI1500_GetWatchdogStatus\n\tCMD_APCI1500_GetWatchdogReloadValue)",
		apci1500_test_watchdog_universal_3
	},	
	{
		"wudauer",
		"test watchdog universal functionality in long run for some special cards",
		apci1500_test_watchdog_universal_dauer_test
	},
	{
		"all",
		"basic timers counters output input",
		apci1500_test_all
	},
	{NULL,NULL,NULL}
};

//--------------------------------------------------------------------------------
void apci1500_test_help(int fd)
{
	int i = 0;
	printf("\navailable commands:\n");
	while (commandtab[i].name != NULL)
	{
		
		printf("%s\t%s\n",commandtab[i].name,commandtab[i].desc);
		i++;
	}
	printf("\n");
}
//--------------------------------------------------------------------------------
void apci1500_run_test(int fd, char* command)
{
	
	int i = 0;
		
	while (commandtab[i].name != NULL)
	{
		if (strcmp(command, commandtab[i].name) == 0 )
		{
			commandtab[i].fc (fd);
			return;
		}
		i++;
	}
	printf("unknown command %s\n",command);
	apci1500_run_test(fd, "help");
	exit(1);

}
//--------------------------------------------------------------------------------
static void usage(void)
{
	printf("testapci1500 FILE COMMAND1 [COMMAND2] ... [COMMANDN] \n" \
	"FILE is the path of a special device file\n" \
	);
	
}

//--------------------------------------------------------------------------------
int main(int argc, char** argv)
{

	int apci1500_card_fd;

	if (argc < 3 )
	{
		printf("not enough arguments\n");
		usage();
		apci1500_test_help(0);
		exit(1);
		
	}
	
	if ( ( apci1500_card_fd = open(argv[1], O_RDWR)) == -1 )
	{
		perror("open");
		exit(1);
	}			
							
	{
		struct stat file_stat;
		if ( fstat(apci1500_card_fd,&file_stat) )
		{
			perror("fstat");
			exit(1);
		}			
		if (!S_ISCHR(file_stat.st_mode)) 
		{
			/* should never happen !*/
			printf("file %s is not a character device\n",argv[1]);
			printf("failed");
			exit(1);
		}
		printf("%s, major:%d minor:%d \n",argv[1], major(file_stat.st_rdev),minor(file_stat.st_rdev));	
	} 
	printf("\n+++++++++++++++++++++++++++++++++++++\nrunning test on device %s  \n+++++++++++++++++++++++++++++++++++++\n\n\n",argv[1]);	
	
	/* run test */
	{
		int index;
		for (index=2; index< argc ; index++)
		{
			apci1500_run_test(apci1500_card_fd, argv[index]);
		}
	}
	printf("\n%d tests failed\n",failed_tests);
	exit(failed_tests);
}
