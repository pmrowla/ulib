INCPATH = ../../include
LIBPATH = ../../lib

CXXFLAGS ?=-O2 -W -Wall -I$(INCPATH)
LDFLAGS   =-L$(LIBPATH) -lulib -lpthread -lrt

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $< -o $@

mr_bench: mr_bench.o
	$(CXX) -o mr_bench mr_bench.o $(LDFLAGS)

clean:
	rm -rf mr_bench mr_bench.o

.PHONY: clean
