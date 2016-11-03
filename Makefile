CXXFLAGS = -std=c++11 -O3 -Wall -Wextra

.PHONY: all test
all : brown_sim make_histo
test:
brown_sim : main.cpp
	$(CXX) main.cpp $(CXXFLAGS) -o $@

make_histo : make_histo.cpp
	$(CXX) $^ $(CXXFLAGS) -O3 -o $@
