CC = gcc
CPP = g++

TARGET = service

CURDIR = $(shell pwd)
SRCDIR = $(CURDIR)/src

OBJS = $(SRCDIR)/tool_util.o\
	   $(SRCDIR)/tool_thread_pool.o\
	   $(SRCDIR)/tool_socket.o\
	   $(SRCDIR)/tool_rpc.o



$(TARGET) : $(OBJS)
	$(CC) -o $@ $^


%.o : %.c
	$(CC) -o $@ -c $^



.PHONY : clean

clean :
	rm -fr $(OBJS)
