EXEC	= gpout-test
OBJS    = gpout-test.o

CROSS	= /opt/arm-2011.03/bin/arm-none-linux-gnueabi-

CC	= $(CROSS)gcc

STRIP	= $(CROSS)strip
CFLAGS	= -Wall -g
#-march=armv5t -O2

all:  clean $(EXEC)

$(EXEC):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
#	$(STRIP) $@

clean:
	-rm -f $(EXEC) *.o
