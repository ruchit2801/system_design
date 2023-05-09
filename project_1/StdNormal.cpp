//
// Created by Ruchit Vithani on 10/8/22.
//

#include<iostream>
#include<cmath>
#include <ctime>

#include <boost/random/normal_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>

#define PI 22.0/7.0

using namespace std;

#include "StdNormal.h"

double StdNormal::gen_normal(){
    boost::variate_generator<boost::mt19937, boost::normal_distribution<> >
            generator(boost::mt19937(std::chrono::system_clock::now().time_since_epoch().count()),
                      boost::normal_distribution<>());

    double r = generator();
    return r;
}

double StdNormal::R_(double z) const{
    return z * (this->a1 + z*(this->a2 + z*(this->a3 + z*(this->a4 + z*this->a5))));
}

double StdNormal::operator()(double x) {

    double z = 1.0 / (1.0 + this->p * x);
    double r_z = this->R_(z);

    if(x >= 0){
        return 1.0 - ((1.0/ sqrt(2.0*PI)) * exp(-1.0 * (pow(x, 2)/2.0)) * r_z);
    } else{
        return 1 - (*this)(-1.0*x);
    }
}