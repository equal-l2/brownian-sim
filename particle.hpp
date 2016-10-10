#pragma once
#include <array>      // std::array
#include <random>     // std::mt19937, std::normal_distribution
#include <functional> // std::bind
#include <chrono>     // std::chrono::system_clock
#include <cmath>      // std::exp
#include "parameters.hpp"

template<unsigned dim>
struct particle{
    particle():r(),v(){}
    std::array<double,dim> r;
    std::array<double,dim> v;
};

struct particles : public std::array<particle<dim>,ptclnum> {
    void adv(){
        static auto v2 = std::bind(
            std::normal_distribution<>(0,sqrt((k*T/m)*(1-std::exp(-2*beta*dt)))),
            #if FIXED_SEED
                std::mt19937(0)
            #else
                std::mt19937(std::chrono::system_clock::now().time_since_epoch().count())
            #endif
        );

        static const double c1 = 1-std::exp(-beta*dt);

        for(auto& p : *this){
            for(unsigned i=0;i<dim;++i){
                p.r[i] += c1*p.v[i]/beta;
                p.v[i] += -p.v[i]*c1+v2();
            }
        }
    }
};
