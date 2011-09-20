#
# Generic ULIB makefile
# Author: Zeno Tan <tzlloch@gmail.com>
# DATE: 2010/8/25
#

# root of ulib directory
ROOT	= ../../..

# path of ulib include output
INCPATH = $(ROOT)/include/ulib

# path of ulib lib output
LIBPATH	= $(ROOT)/lib

# output library
TARGET	= $(LIBPATH)/libshell.a

CC	= gcc
CFLAGS	= -I $(INCPATH) -g3 -O3 -Wall -W -Werror -pipe -c -fno-strict-aliasing

#
# define object files below
#
OBJS	= console.o argv_split.o

.c.o:
	$(CC) $(CFLAGS) $< -o $@

#
# build targets
#

all: $(TARGET)

.PHONY: all clean $(INCPATH)

$(TARGET): $(OBJS) $(INCPATH)
	mkdir -p $(LIBPATH)
	ar csr $(TARGET) $(OBJS)

$(INCPATH):
	mkdir -p $(INCPATH)
	cp *.h $(INCPATH)/

clean:
	rm -rf $(OBJS)
	rm -rf $(TARGET)
