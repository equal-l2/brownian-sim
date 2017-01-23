#include <iomanip>
#include <iostream>

#define PRINT_PROGRESS_BAR true
#define FIXED_SEED true // if true, random seed will be 0, otherwise seed will be current time

#include "parameters.hpp"
#include "particle.hpp"

#if PRINT_PROGRESS_BAR
  #include "l2lib/progress_bar.hpp"
#endif

/* main */
int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  particles ps;

  #if PRINT_PROGRESS_BAR
  l2lib::progress_bar pbar(rep_n,50);
  #endif

  for(unsigned long long i=0;i < rep_n;++i){
    ps.adv();

    #if PRINT_PROGRESS_BAR
    pbar.adv();
    #endif
  }
}
