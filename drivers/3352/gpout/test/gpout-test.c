
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define GPOUT "/dev/gpout"

int main(int argc,char *argv[])
{
    int gp_fd = -1;
    char data[2];
    if(argc != 3)
   	{
      printf("argc is not == 3\n");
	  return -1;
	}
	data[0]= atoi(argv[1]);
	data[1] = atoi(argv[2]);
    gp_fd = open(GPOUT, O_WRONLY);
    if (gp_fd == -1)
    {
        printf("fail to open "GPOUT "!\n");
		return -1;
    }
 
    if(write(gp_fd, data, sizeof(data)) > 0)//传入的数据长度必须为2		
    	printf("set gpioinfo %d level %d\n", data[0], data[1]);

    close(gp_fd);


    return 0;
}


