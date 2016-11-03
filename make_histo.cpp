#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include "histo.hpp"

template <typename T>
T ato(char* a){
    std::stringstream s;
    s << a;
    T buf;
    s >> buf;
    return buf;
}

int main(int argc, char** argv){
    std::ios::sync_with_stdio(false);

    if(argc <= 4){
	std::cout << "Usage: make_histo <number of bin> <min of histo> <max of histo> <filename>\n";
	std::cout << "Note: If filename is \"-\", input data will be received from stdin\n";
	return 1;
    }

    const auto n_of_bin = ato<unsigned long long>(argv[1]);
    const auto min = atof(argv[2]);
    const auto max = atof(argv[3]);
    const std::string filename(argv[4]);
    
    Histo h(min,max,n_of_bin);
    
    std::shared_ptr<std::istream> is;
    if(filename == "-"){
	is.reset(&std::cin,[](...){});
    }
    else{
	is.reset(new std::ifstream(filename));
    }

    if(!(*is)){
	std::cout << "Error on opening \"" << filename << "\"\n";
	return 1;
    }

    double buf;
    while(*is >> buf){
	h.insert(buf);
    }

    h.print(std::cout);
}
