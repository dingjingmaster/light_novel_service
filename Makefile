CC = gcc
CPP = g++
CHDIR = cd
MAKE = make
CLEAN = clean

CURDIR = $(shell pwd)
SRCDIR = $(CURDIR)/src
LOGDIR = $(CURDIR)/src/module/zlog
TESTDIR = $(CURDIR)/test

WARNINGS = -Wall -Wstrict-prototypes -fwrapv
DEBUG = -g -ggdb
LIBRARY = -lpthread
INCLUDE = -I $(LOGDIR)

TARGET = service
TEST = test

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

SERVEROBJS = $(SRCDIR)/main.o\
			 $(SRCDIR)/main_run.o\
			 $(SRCDIR)/tool_util.o\
			 $(SRCDIR)/tool_thread_pool.o\
			 $(SRCDIR)/tool_socket.o\
			 $(SRCDIR)/tool_rpc.o

.PHONY : clean test

$(TARGET):


$(TEST):
	$(CHDIR) $(TESTDIR) && $(MAKE)

all : $(TARGET) $(TEST)


$(TARGET) : $(SERVEROBJS) $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)


%.o : %.c
	$(CC) -o $@ -c $< $(INCLUDE) $(DEBUG) $(WARNINGS)



.PHONY : clean

clean :
	rm -fr  $(TARGET)
	rm -fr  $(LOGOBJS)
	rm -fr  $(SERVEROBJS)
	$(CHDIR) $(TESTDIR) && $(MAKE) $(CLEAN) 
