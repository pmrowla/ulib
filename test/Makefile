TARGET		= alignhash.test alignhash_bench.test fbsearch.test version.test tree.test \
		list.test listsort.test gcd.test aes.test bitmap.test part.test heapsort.test \
		comb.test console.test bfilter.test rand.test

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
