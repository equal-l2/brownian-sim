CXXFLAGS = -std=c++11 -O3 -Wall -Wextra

.PHONY: clean

brown_sim : main.cpp
	$(CXX) main.cpp $(CXXFLAGS) -o $@

clean:
	$(RM) brown_sim make_histo

