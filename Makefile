CC = gcc
CPP = g++

TARGET = service

WARNINGS = -Wall -Wstrict-prototypes -fwrapv
DEBUG = -g -ggdb
LIBRARY = -lpthread
CURDIR = $(shell pwd)
SRCDIR = $(CURDIR)/src
LOGDIR = $(CURDIR)/src/module/zlog

LOGOBJS = $(LOGDIR)/buf.o\
		  $(LOGDIR)/category.o\
		  $(LOGDIR)/category_table.o\
		  $(LOGDIR)/conf.o\
		  $(LOGDIR)/event.o\
		  $(LOGDIR)/format.o\
		  $(LOGDIR)/level.o\
		  $(LOGDIR)/level_list.o\
		  $(LOGDIR)/mdc.o\
		  $(LOGDIR)/record.o\
		  $(LOGDIR)/record_table.o\
		  $(LOGDIR)/rotater.o\
		  $(LOGDIR)/rule.o\
		  $(LOGDIR)/spec.o\
		  $(LOGDIR)/thread.o\
		  $(LOGDIR)/zc_arraylist.o\
		  $(LOGDIR)/zc_hashtable.o\
		  $(LOGDIR)/zc_profile.o\
		  $(LOGDIR)/zc_util.o\
		  $(LOGDIR)/zlog.o

SERVEROBJS = $(SRCDIR)/tool_util.o\
			 $(SRCDIR)/tool_thread_pool.o\
			 $(SRCDIR)/tool_socket.o\
			 $(SRCDIR)/tool_rpc.o



$(TARGET) : $(SERVEROBJS) $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY)


%.o : %.c
	$(CC) -o $@ -c $^ $(DEBUG) $(WARNINGS)



.PHONY : clean

clean :
	rm -fr  $(TARGET)
	rm -fr  $(LOGOBJS)
	rm -fr  $(SERVEROBJS)
