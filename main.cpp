#include <iomanip>
#include <iostream>
#include <fstream>

#define PRINT_PROGRESS_BAR true
#define FIXED_SEED true // if true, random seed will be 0, otherwise seed will be current time

#include "parameters.hpp"
#include "particle.hpp"

#if PRINT_PROGRESS_BAR
  #include "l2lib/progress_bar.hpp"
#endif

#include "l2lib/histo.hpp"

constexpr double hist_min = 0;
constexpr double hist_max = 4e-6;
constexpr double hist_div = 100;

static_assert(hist_min < hist_max);

/* main */
int main(){
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  particles ps;

  std::cout << "T : " << T << std::endl;
  std::cout << "m : " << m << std::endl;
  std::cout << "rep_n : " << rep_n << std::endl;
  std::cout << "histogram area : " << ptclnum * (hist_max - hist_min) / hist_div << std::endl;

  #if PRINT_PROGRESS_BAR
  l2lib::progress_bar pbar(rep_n,50);
  #endif

  std::ofstream ofs("out.txt");

  for(unsigned long long i=0;i < rep_n;++i){
    ps.adv();

    Histo h(hist_min, hist_max, hist_div);

    for(auto&& p : ps) {
        h.insert(p.vnorm());
    }

    h.print(ofs);
    ofs << "\n\n";

    #if PRINT_PROGRESS_BAR
    pbar.adv();
    #endif
  }
}
