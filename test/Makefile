TARGET=   alignhash.test

CXXFLAGS= -I../ -O3 -W -Wall 

%.test: test_%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: all clean

all: $(TARGET)

clean:
	rm -rf $(TARGET)
