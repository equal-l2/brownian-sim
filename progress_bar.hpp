#pragma once
#include <sstream>   // std::ostringstream
#include <iomanip>   // std::setw,setprecision
#include <iostream>  // std::clog
#include <cmath>     // std::pow
#include <algorithm> //std::min

class progress_bar{
    using big_uint = unsigned long long;
    const big_uint max;
    const unsigned width;
    const int precision;
    big_uint count;
    big_uint next_show_count;
    std::ostream& os;

    void show(){
        std::ostringstream oss;

        /* draw progress bar */
        const unsigned tics = static_cast<unsigned>((static_cast<double>(count)/max)*width);
        oss << '\r';
        oss << '[';
        if(tics != 0){
            for(unsigned i = tics-1; i; --i){
                oss << '=';
            }
            oss << '>';
        }
        if(tics < width){
            for(unsigned i = width-tics; i; --i){
                oss << ' ';
            }
        }
        oss << "] ";

        /* draw progress in percentage */
        // `precision` > 0 : increased digits after decimal point
        // `precision` <= 0: print just before decimal point
        // if `precision` is negative, screen updating will happen less

        big_uint next_tic_count = static_cast<big_uint>(static_cast<double>(tics+1)/width*max);
        big_uint next_ratio_count;

        if(precision > 0){
            oss << '['
            << std::fixed << std::setw(static_cast<int>(4+precision)) << std::setprecision(static_cast<int>(precision))
            << count*(100.0/max) << "%]";
            next_ratio_count = static_cast<big_uint>(count+max/std::pow(10,2+precision));
        }
        else{
            oss << '[' << std::fixed << std::setw(3) << std::setprecision(0) << count*(100.0/max) << "%]";
            next_ratio_count = static_cast<big_uint>(count+max/100);
        }
        next_show_count = std::min({next_tic_count,next_ratio_count,max-1});

        // actual flushing of buffer will happen only when either progress in percentage or tics changes
        // `next_show_count` is capped with `max` to ensure last value is 100%

        os << oss.str() << std::flush;
    }
public:
    progress_bar(big_uint max_in, unsigned width_in, int precision_in = 0, std::ostream& os_in = std::clog)
    // max       : max count (count value on 100% progress)
    // width     : width of progress bar in character
    // precision : digits after decimal point

    // Caution
    // Too much precision can cause great performance decrease

    :max(max_in),width(width_in),precision(precision_in),count(),next_show_count(),os(os_in){
        show();
    }
    ~progress_bar(){
        os << std::endl;
    }
    void adv(big_uint i = 1){
        if((count += i) >= next_show_count){show();}
    }
};
