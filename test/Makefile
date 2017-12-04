CC = gcc
CPP = g++

CURDIR = $(shell pwd)
SRCDIR = $(CURDIR)/../src
LOGDIR = $(CURDIR)/../src/module/zlog

WARNINGS = -Wall -Wstrict-prototypes -fwrapv
DEBUG = -g -ggdb
LIBRARY = -lpthread
INCLUDE = -I $(LOGDIR)

# test 相关
LISTDIR = $(CURDIR)/list

# 依赖
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

TESTOBJS = $(SRCDIR)/tool_log.o\
			 $(SRCDIR)/tool_list.o\
			 $(SRCDIR)/tool_util.o\
			 $(SRCDIR)/tool_thread_pool.o\
			 $(SRCDIR)/tool_socket.o\
			 $(SRCDIR)/tool_rpc.o

TEST_LIST = TEST_LIST_1


TLIST_1_OBJ = $(LISTDIR)/test_list1.o


all : $(TEST_LIST) 


TEST_LIST_1 : $(TLIST_1_OBJ) $(TESTOBJS) $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)


%.o : %.c
	$(CC) -o $@ -c $< $(INCLUDE) $(DEBUG) $(WARNINGS)


.PHONY : clean

clean :
	rm -fr $(TEST_LIST)
	rm -fr $(TESTOBJS)
	rm -fr $(TLIST_1_OBJ)


