#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "restart.h"

#define SIZE 1024*1024*5

int
main (int argc, char *argv[]) {
	char buf[] = "g";
	pid_t childpid = 0;
	int fd;
	int i, n;
    
    char *buffer = malloc (SIZE); 
    
    
	if ( (fd = open ( "./data_brw_file", O_CREAT|O_RDWR|O_TRUNC) )== -1) { /* create pipe for synchronization */
		perror("Failed to create the synchronization pipe");
		return 1;
	}
    printf("Parent PID= %d\n",(long)getpid());
	
    if ((childpid = fork()) < 0){
        perror("error fork process\n");
        return -1;
    }

    int  m = 0;
    if (childpid  > 0 )
    {    
        for (  m = 0  ; m < SIZE ; m++){
            buffer[m] = 'p';
        } 
    }else{
        
        for (  m = 0  ; m < SIZE ; m++){
            buffer[m] = 'c';
        }
    }
    
    if (write(fd, buffer, SIZE) != SIZE)
		perror("Failed to write synchronization characters");
	
	fprintf(stderr, " process ID:%ld parent ID:%ld child ID:%ld !\n",
			 (long)getpid(), (long)getppid(), (long)childpid);
}
