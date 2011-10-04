TARGET		= alignhash.test alignhash_bench.test fbsearch.test version.test tree.test \
		list.test listsort.test gcd.test aes.test bitmap.test part.test heapsort.test \
		comb.test console.test bfilter.test rand.test rc4.test sha256sum.test

INCPATH		= ../include
LIBPATH		= ../lib

CXX		?= g++
CXXFLAGS	?= -g3 -O3 -W -Wall
LDFLAGS		?= -lulib -lrt -lm

%.test: test_%.cpp
	$(CXX) -I $(INCPATH) $(CXXFLAGS) $< -o $@ -L $(LIBPATH) $(LDFLAGS)

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET)
