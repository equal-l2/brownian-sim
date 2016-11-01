CXXFLAGS = -std=c++11 -O3 -Wall -Wextra

.PHONY: all test
all : brown_sim make_histo
test:
brown_sim :
	$(CXX) main.cpp $(CXXFLAGS) -o $@

make_histo :
	$(CXX) make_histo.cpp $(CXXFLAGS) -O3 -o $@
