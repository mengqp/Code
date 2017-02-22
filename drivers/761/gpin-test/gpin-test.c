
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>

#define GPIN "/dev/gpin"

#define	GPIO_GETMU	_IOWR('G', 0x3A, int)
#define	GPIO_GETOS	_IOWR('G', 0x3B, int)
#define	GPIO_GETBF	_IOWR('G', 0x3C, int)
#define	GPIO_GETBU	_IOWR('G', 0x3D, int)
#define	GPIO_GETMW	_IOWR('G', 0x3E, int)
#define	GPIO_GETBW	_IOWR('G', 0x3F, int)
#define	GPIO_GETGJ	_IOWR('G', 0x39, int)

unsigned int cmd[7]={GPIO_GETMU, GPIO_GETOS, GPIO_GETBF, GPIO_GETBU,GPIO_GETMW,	GPIO_GETBW,GPIO_GETGJ};

int main(int argc,char *argv[])
{
    int gp_fd = -1;
    unsigned int info;
	int level;
    if(argc != 2)
   	{
      printf("argc is not == 2n");
	  return -1;
	}
	info= atoi(argv[1]);
    gp_fd = open(GPIN, O_WRONLY);
    if (gp_fd == -1)
    {
        printf("fail to open "GPIN "!\n");
		return -1;
    }

	while (1)
	{
		if(ioctl(gp_fd, cmd[6], &level) >= 0)
			printf("read gpioinfo %d level %d\n", info, level);

		usleep( 200 * 1000 );
	}

    close(gp_fd);


    return 0;
}
