/*
 * =====================================================================================
 *
 *       Filename:  proc_pwrite.cpp
 *
 *    Description:  practise
 *
 *        Version:  1.0
 *        Created:  2010年10月17日 14时51分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), YOUR EMAIL
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */


#include <iostream>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

using std::cerr;
using std::endl;


const int bufSize = 100;
const int times = 1000;

int
main(void)
{
	int   fd;
	pid_t pid;
	if ((fd = creat("proc_p_file", S_IRUSR | S_IWUSR | 
				   	S_IRGRP | S_IROTH)) == -1)
	{
		cerr << "creat file error: "
			<< strerror(errno) << endl;
		return -1;
	}
	for (int index = 0; index < 3; ++index)
	{
		if ((pid = fork()) < 0)
		{
			cerr << "fork error: "
			   << strerror(errno) << endl;
			return -1;
		}
		else if (pid == 0)
		{
			off_t endPos;
			char buf[bufSize];

			for (int i = 0; i < bufSize - 1; ++i)
				buf[i] = index + '0';
			buf[bufSize - 1] = '\n';
		
			for (int i = 0; i < times; ++i)	
			{

 				if ((endPos = lseek(fd, 0, SEEK_END) == -1))
				{
					cerr << "lseek error: "
						<< strerror(errno) << endl;
					return -1;
				}

				usleep(1000);
				if (pwrite(fd, buf, bufSize, endPos) == -1)
				{
					cerr << "write error: "
						<< strerror(errno) << endl;
					return -1;
				}
                cerr << "position: "<<endPos<<endl;
			}
			close(fd);
			return 0;
		}
	}

	for(int index = 0; index < 3; ++index)
		waitpid(-1, NULL, 0);
	close(fd);
	return 0;
}
