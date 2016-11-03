#include <iostream> // std::ostream
#include <vector>   // std::vector
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>

class Hist{
    typedef Hist self;
public:
    Hist(double min_in, double max_in, size_t n_of_bin_in)
        :min(min_in),max(max_in),n_of_bin(n_of_bin_in),width((max-min)/n_of_bin),bins(n_of_bin){}

    void print(std::ostream& os = std::cout){
        for(unsigned i=0;i<n_of_bin;++i)
            os << std::scientific << (i*width+min) << ' ' << bins[i] << '\n';
    }

    template<typename InIt>
    inline void insert(InIt b, InIt e){
	for(auto it=b;b!=e;++it) insert(*b);
    }

    inline void insert(double v){
	if(min <= v && v < max ) ++bins[static_cast<std::size_t>((v-min)/width)];
    }

    const double min;
    const double max;
    const size_t n_of_bin;
    const double width;
    std::vector<double> bins;
};

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
    
    Hist h(min,max,n_of_bin);
    
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

    h.print();
}
