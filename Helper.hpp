#ifndef __HELPER_H_INCLUDED__
#define __HELPER_H_INCLUDED__

#include "boost/random/taus88.hpp"
#include <boost/random/mersenne_twister.hpp>
#include <chrono>       // Casove fce
#include <iostream>
#include <random>
#include <thread>
#include <windows.h>
namespace helper {

float nahodneCislo();
float random();
int zaokrouhli(float);
void pockej(int);       // pocka x vterin
void zapniStopky();
int integratePower(int, float);

typedef std::chrono::high_resolution_clock stopky;
typedef std::chrono::system_clock sysCas;
typedef stopky::time_point Okamzik;
typedef stopky::duration Doba;
//typedef boost::random::random_device nahodak;       // tak na tohle bych musel kompilovat boost

}

#endif // __HELPER_H_INCLUDED__

