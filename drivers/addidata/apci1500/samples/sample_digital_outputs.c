/** @file sample_digital_outputs.c
 
   This demonstarte how to use digital outputs in user mode.
 
   @par CREATION  
   @author Krauth Julien
   @date   10.10.08
   
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

volatile static int Stop;
static int *fd;

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
//--------------------------------------------------------------------------------

/** Exit callback function.
 *
 * This function is called on Ctrl+c key combination.
 * It change the Stop flag status.
 */
static void v_ControlExit (int notused)
{
	Stop = 1;
	
	printf("Set all digital outputs off\n");
	if ( ioctl( fd[0], CMD_APCI1500_Set16DigitalOutputOff, 0xFFFF ) )
	{
		perror("ioctl (CMD_APCI1500_Set16DigitalOutputOff)");
		exit(EXIT_FAILURE);
	}
	
	if ( ioctl( fd[0], CMD_APCI1500_SetOutputMemoryOff, NULL ) )
	{
		perror("ioctl (CMD_APCI1500_SetOutputMemoryOff)");
		exit(EXIT_FAILURE);		
	}
	
	signal (SIGINT, SIG_DFL);
	
	printf("Sample abort.\n");
}

//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	int nbr_boards = 0;
	
	Stop = 0;
	
	/* Search for APCI-1500 boards */
	if ((nbr_boards = apci1500_find_cards(&fd)) == 0) 
	{
		printf("No APCI-1500 found\n");
		exit(EXIT_FAILURE);
	}
	
	/* Set the v_ControlExit callback function on Ctrl+c key combination.
	 * Once Ctrl+C are pressed, the v_ControlExit function is called to end the 
	 * sample.
	 */
	signal (SIGINT, v_ControlExit);	
	
	if ( ioctl( fd[0], CMD_APCI1500_SetOutputMemoryOn, NULL ) )
	{
		perror("ioctl (CMD_APCI1500_SetOutputMemoryOn)");
		exit(EXIT_FAILURE);		
	}   
   
	/* Wait Ctrl+c key combination */
	printf ("TO STOP THE SAMPLE PRESS CTRL+C\n");
	
	while (!Stop)
	{
		printf("Set all digital outputs on (2 seconds)\n");
		if ( ioctl( fd[0], CMD_APCI1500_Set16DigitalOutputOn, 0xFFFF ) )
		{
			perror("ioctl (CMD_APCI1500_Set16DigitalOutputOn)");
			exit(EXIT_FAILURE);
		}
		usleep(2000000);
	
		if (!Stop)
		{
			printf("Set all digital outputs off (2 seconds)\n");
			if ( ioctl( fd[0], CMD_APCI1500_Set16DigitalOutputOff, 0xFFFF ) )
			{
				perror("1 ioctl (CMD_APCI1500_Set16DigitalOutputOff)");
				exit(EXIT_FAILURE);
			}	
			usleep(2000000);
		}			
	}
	
	return EXIT_SUCCESS;
}
