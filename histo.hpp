#include <iostream> // std::ostream
#include <vector>   // std::vector

class Histo{
    typedef Histo self;
public:
    Histo(double min_in, double max_in, size_t n_of_bin_in)
        :min(min_in),max(max_in),n_of_bin(n_of_bin_in),width((max-min)/n_of_bin),bins(n_of_bin){}

    void print(std::ostream& os){
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
