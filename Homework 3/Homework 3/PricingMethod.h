//
// Created by Ruchit Vithani on 9/29/22.
//

#ifndef HOMEWORK_3_PRICINGMETHOD_H
#define HOMEWORK_3_PRICINGMETHOD_H

#include<iostream>
using namespace std;

class PricingMethod {
public:
    virtual vector<double> BSM_Pricer() = 0;
    virtual vector<double> Binomial_Pricer() = 0;
};


#endif //HOMEWORK_3_PRICINGMETHOD_H
