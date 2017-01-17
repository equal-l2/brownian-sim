CXXFLAGS = -std=c++11 -O3 -Wall -Wextra

.PHONY: clean

brown_sim : main.cpp *.hpp l2lib/progress_bar.hpp
	$(CXX) main.cpp $(CXXFLAGS) -o $@

clean:
	$(RM) brown_sim make_histo

