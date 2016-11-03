CXXFLAGS = -std=c++11 -O3 -Wall -Wextra

.PHONY: all test clean

all : brown_sim make_histo

test: all
	./brown_sim && ./make_histo 10 0 10 test.dat

clean:
	$(RM) brown_sim make_histo

brown_sim : main.cpp
	$(CXX) main.cpp $(CXXFLAGS) -o $@

make_histo : make_histo.cpp
	$(CXX) $^ $(CXXFLAGS) -O3 -o $@
