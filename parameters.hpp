#pragma once
/* physical constants */
constexpr double pi = 3.141592653589793238462643383279;
constexpr double abs_zero = -273.15;              // absolute zero [degree Celsius]
constexpr double k = 1.380649e-23;                // Boltzmann constant [J/K]

/* parameters (user-defined)*/
constexpr double t_degc = 25;                     // temperature [degree Celsius]
constexpr double rho = 2.699e+3;                  // dencity of particle [kg/m^3]
constexpr double eta = 0.890e-3;                  // viscocity of fluid [Pa*s]
constexpr double ra = 100e-6;                     // radius of particle [m]
constexpr double dt = 5.747e-4;                   // step size in time [s]
constexpr unsigned dim = 1;                       // dimension [-]
constexpr unsigned long long ptclnum = 1000;      // particle amount [-]
constexpr double sim_time = 0.3;                  // simulation time [s]

/* parameters (automatically calculated) */
constexpr double T = t_degc-abs_zero;             // temperature in Kelvin [K]
constexpr double m = (4/3.)*pi*ra*ra*ra*rho;      // mass of particle [kg]
constexpr double beta = 6*pi*ra*eta/m;            // constant of drag [-]
constexpr double D = k*T/(m*beta);                // diffusion coefficient [m^2/s]
constexpr unsigned long long rep_n = sim_time/dt; // number of repetition [-]
