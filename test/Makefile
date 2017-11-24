CC = gcc
CPP = g++

CURDIR = $(shell pwd)
SRCDIR = $(CURDIR)/../src
LOGDIR = $(CURDIR)/../src/module/zlog
TESTDIR = $(CURDIR)

WARNINGS = -Wall -Wstrict-prototypes -fwrapv
DEBUG = -g -ggdb
LIBRARY = -lpthread
INCLUDE = -I $(LOGDIR)

TEST = $(TESTDIR)/test_bitmap\
	   $(TESTDIR)/test_buf\
	   $(TESTDIR)/test_conf\
	   $(TESTDIR)/test_default\
	   $(TESTDIR)/test_hello\
	   $(TESTDIR)/test_hex\
	   $(TESTDIR)/test_init\
	   $(TESTDIR)/test_leak\
	   $(TESTDIR)/test_level\
	   $(TESTDIR)/test_log\
	   $(TESTDIR)/test_longlog\
	   $(TESTDIR)/test_mdc\
	   $(TESTDIR)/test_multithread\
	   $(TESTDIR)/test_pipe\
	   $(TESTDIR)/test_press_syslog\
	   $(TESTDIR)/test_press_write2\
	   $(TESTDIR)/test_press_write\
	   $(TESTDIR)/test_press_zlog2\
	   $(TESTDIR)/test_press_zlog\
	   $(TESTDIR)/test_profile\
	   $(TESTDIR)/test_record\
	   $(TESTDIR)/test_syslog\
	   $(TESTDIR)/test_tmp

TESTLOGOBJ = $(TESTDIR)/test_bitmap.o\
			 $(TESTDIR)/test_buf.o\
			 $(TESTDIR)/test_conf.o\
			 $(TESTDIR)/test_default.o\
			 $(TESTDIR)/test_hello.o\
			 $(TESTDIR)/test_hex.o\
			 $(TESTDIR)/test_init.o\
			 $(TESTDIR)/test_leak.o\
			 $(TESTDIR)/test_level.o\
			 $(TESTDIR)/test_log.o\
			 $(TESTDIR)/test_longlog.o\
			 $(TESTDIR)/test_mdc.o\
			 $(TESTDIR)/test_multithread.o\
			 $(TESTDIR)/test_pipe.o\
			 $(TESTDIR)/test_press_syslog.o\
			 $(TESTDIR)/test_press_write2.o\
			 $(TESTDIR)/test_press_write.o\
			 $(TESTDIR)/test_press_zlog2.o\
			 $(TESTDIR)/test_press_zlog.o\
			 $(TESTDIR)/test_profile.o\
			 $(TESTDIR)/test_record.o\
			 $(TESTDIR)/test_syslog.o\
			 $(TESTDIR)/test_tmp.o

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




$(TEST) : 


$(TESTDIR)/test_bitmap : $(TESTDIR)/test_bitmap.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_buf : $(TESTDIR)/test_buf.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_conf : $(TESTDIR)/test_conf.o $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_default : $(TESTDIR)/test_default.o $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_hashtable : $(TESTDIR)/test_hashtable.o $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_hello : $(TESTDIR)/test_hello.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_hex : $(TESTDIR)/test_hex.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_init : $(TESTDIR)/test_init.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_leak : $(TESTDIR)/test_leak.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_level : $(TESTDIR)/test_level.o $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_log : $(TESTDIR)/test_log.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_longlog : $(TESTDIR)/test_longlog.o $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_mdc : $(TESTDIR)/test_mdc.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_multithread : $(TESTDIR)/test_multithread.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_pipe : $(TESTDIR)/test_pipe.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_press_syslog : $(TESTDIR)/test_press_syslog.o $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_press_write2 : $(TESTDIR)/test_press_write2.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_press_write : $(TESTDIR)/test_press_write.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_press_zlog2 : $(TESTDIR)/test_press_zlog2.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_press_zlog : $(TESTDIR)/test_press_zlog.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_profile : $(TESTDIR)/test_profile.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_record : $(TESTDIR)/test_record.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_syslog : $(TESTDIR)/test_syslog.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)

$(TESTDIR)/test_tmp : $(TESTDIR)/test_tmp.o  $(LOGOBJS)
	$(CC) -o $@ $^ $(LIBRARY) $(INCLUDE) $(DEBUG) $(WARNINGS)


%.o : %.c
	$(CC) -o $@ -c $< $(INCLUDE) $(DEBUG) $(WARNINGS)



.PHONY : clean

clean :
	rm -fr  $(TEST)
	rm -fr  $(LOGOBJS)
	rm -fr  $(TESTLOGOBJ)


