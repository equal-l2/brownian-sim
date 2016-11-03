#include <iomanip>
#include <iostream>

#define PRINT_PROGRESS_BAR true
#define FIXED_SEED true // if true, random seed will be 0, otherwise seed will be current time

#include "progress_bar.hpp"
#include "parameters.hpp"
#include "particle.hpp"

#if PRINT_PROGRESS_BAR
	#include "progress_bar.hpp"
#endif

/* main */
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

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
