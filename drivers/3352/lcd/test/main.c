/*******************************************************************************
 * 文件名:main.c
 * 文件描述:
 * 作者:menqp
 * 创建日期:2016/05/19 13:37:46
 * 公司：esdtek
 * 版本：Ver1.0
 *
 * 历史版本：
 * 修改人                修改时间                修改版本        修改内容
 *
 *
 ******************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/fcntl.h>

int main(int argc, char *argv[])
{

	int fd = open( "/dev/tty0", O_RDWR);

	if (0 > fd)
	{
		printf("error\n");
	}

	write( fd, "\33[9;1]", 8);
	close( fd );
    return 0;
}
