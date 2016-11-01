#include <iostream> // std::ostream
#include <vector>   // std::vector
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
    if(argc <= 4){
	std::cout << "Usage: make_histo <filename> <number of bin> <min of histo> <max of histo>\n";
	return 1;
    }

    const char* filename = argv[1];
    const auto n_of_bin = ato<unsigned long long>(argv[2]);
    const auto min = atof(argv[3]);
    const auto max = atof(argv[4]);

    Hist h(min,max,n_of_bin);

    std::ifstream ifs(filename);
    if(!ifs.is_open()){
	std::cout << "Error on opening " << filename << '\n';
	return 1;
    }

    double buf;
    while(ifs >> buf){
	h.insert(buf);
    }

    h.print();
}
