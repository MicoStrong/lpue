#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>

using namespace std;

int main()
{    
  int fd = creat("a.txt", S_IRWXU);
  
  return 0;
}

