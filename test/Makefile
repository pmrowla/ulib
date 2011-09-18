TARGET		= alignhash.test alignhash_bench.test

INCPATH		= ../include
LIBPATH		= ../lib

CXX		?= g++
CXXFLAGS	?= -I$(INCPATH) -g3 -O3 -W -Wall 
LDFLAGS		?= -L$(LIBPATH) -lulib -lrt -lm

%.test: test_%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET)
