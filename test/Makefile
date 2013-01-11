TARGET		= alignhash.test alignhash_bench.test fbsearch.test version.test tree.test \
		list.test listsort.test gcd.test aes.test bitmap.test part.test heapsort.test \
		comb.test console.test bfilter.test rand.test rc4.test sha256sum.test \
		avl_bench.test splay_bench.test set_bench.test bfilter_bench.test stirling.test \
		zipf_rng.test thread.test periodic.test hash.test bit.test rdtsc.test bn.test \
		chainhash.test chainhash_bench.test chainhash_class.test chainhash_r_class.test \
		chainhash_r_bench.test chainhash_class_bench.test indep_workloads.test \
		share_workloads.test log.test

INCPATH		= ../include
LIBPATH		= ../lib

CXX		?= g++
CXXFLAGS	?= -g3 -O2 -W -Wall
LDFLAGS		?= -lulib -lpthread -lrt
DEBUG		?=

%.test: test_%.cpp
	$(CXX) -I $(INCPATH) $(CXXFLAGS) $(DEBUG) $< -o $@ -L $(LIBPATH) $(LDFLAGS)

all: $(TARGET)

clean:
	rm -rf $(TARGET)

.PHONY: all clean
