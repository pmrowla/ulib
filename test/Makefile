TARGET		= alignhash.test

INCPATH		= ../include
LIBPATH		= ../lib

CXXFLAGS	?= -I$(INCPATH) -g3 -O3 -W -Wall 
LDFLAGS		?= -L$(LIBPATH) -lulib -lrt -lm

%.test: test_%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET)
