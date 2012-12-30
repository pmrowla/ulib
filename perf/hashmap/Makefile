SPARSEHASH_INC = ../../../sparsehash/include
GPERFTOOLS_INC = ../../../gperftools/include
GPERFTOOLS_LIB = ../../../gperftools/lib
EASTL_INC  = ../../../eastl/include
EASTL_LIB  = ../../../eastl/lib
RDESTL_INC = ../../../rdestl
ULIB_INC = ../../include

INC = -I$(SPARSEHASH_INC) -I$(GPERFTOOLS_INC) -I$(EASTL_INC) -I$(RDESTL_INC) -I$(ULIB_INC)
LIB = -L$(GPERFTOOLS_LIB) -L$(EASTL_LIB)

CXXFLAGS ?=-O2 -W -Wall $(INC)
LDFLAGS   =$(LIB) -lEASTL -ltcmalloc -lrt -lpthread -static

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $< -o $@

hash_perf: hash_perf.o
	$(CXX) -o hash_perf hash_perf.o $(LDFLAGS)

clean:
	rm -rf hash_perf
	rm -rf hash_perf.o
	rm -rf *~

.PHONY: clean
