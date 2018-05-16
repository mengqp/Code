OBJS = main.o
# CC = /opt/wisermind_9G45/bin/arm-none-linux-gnueabi-g++
CC = /opt/arm-2011.03/bin/arm-none-linux-gnueabi-gcc
# CC = g++
LINKOPTS=-c -g
LINK1OPTS = -g -o
main:$(OBJS)
	$(CC) $(OBJS) $(LINK1OPTS) $@

main.o:main.c
	$(CC) $(LINKOPTS) $<


clean:
	rm -f $(OBJS) main
