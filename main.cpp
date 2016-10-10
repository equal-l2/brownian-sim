#include <array>
#include <chrono> // std::chrono::system_clock
#include <cmath> // std::exp
#include <functional> // std::bind
#include <iomanip> // std::setw,setprecision
#include <iostream> // std::cout,std::clog,std::endl(<ostream>),std::scientific(<ios>)
#include <iterator> // std::begin,std::end
#include <numeric> // std::inner_product
#include <random> // std::mt19937,std::normal_distribution
#include <vector> // std::vector

#define PRINT_PROGRESS_BAR true
#define FIXED_SEED true

#include "progress_bar.hpp"
#include "parameters.hpp"
#include "particle.hpp"
#include "histo.hpp"

#if PRINT_PROGRESS_BAR
	#include "progress_bar.hpp"
#endif

/* main */
int main(){
	std::ios::sync_with_stdio(false);

	particles ps;

	#if PRINT_PROGRESS_BAR
	progress_bar pbar(process_time/dt+1,50);
	#endif

	for(unsigned long long i=0;i*dt < process_time;++i){
		ps.adv();

		#if PRINT_PROGRESS_BAR
		pbar.adv();
		#endif
	}
}
