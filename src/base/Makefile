WORKROOT	= ../..

INCPATH		= $(WORKROOT)/include/ulib
LIBPATH		= $(WORKROOT)/lib

TARGET		= $(LIBPATH)/libubase.a

CC		?= gcc
CFLAGS		?= -g3 -O3 -Wall -W -Werror -pipe -c -fno-strict-aliasing

DS_OBJS		= tree.o treeutils.o
SEARCH_OBJS	= fbsearch.o
CRYPT_OBJS	=
SORT_OBJS	=
MISC_OBJS	= strutils.o
COMMON_OBJS	= version.o

OBJS		= $(DS_OBJS) $(SEARCH_OBJS) $(CRYPT_OBJS) \
		  $(SORT_OBJS) $(MISC_OBJS) $(COMMON_OBJS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: all clean $(INCPATH)

all: $(TARGET)

$(TARGET): $(OBJS) $(INCPATH)
	mkdir -p $(LIBPATH)
	ar csr $(TARGET) $(OBJS)

$(INCPATH):
	mkdir -p $(INCPATH)
	cp *.h $(INCPATH)/

clean:
	rm -rf $(OBJS)
	rm -rf $(TARGET)
	rm -rf $(INCPATH)/*.h
	rm -rf $(INCPATH)
