//
// Created by Ruchit Vithani on 10/14/22.
//

#ifndef PROJECT_1_REALDELTAHEDGING_H
#define PROJECT_1_REALDELTAHEDGING_H

#include "BSM.h"
#include<iostream>

using namespace std;

class RealDeltaHedging{
private:
    const double tolerance = 1.0*1e-4;
    const double L = 1.0*1e-5;
    const double R = 1.0;
public:
    double get_implied_volatility(double K, double S0, double r, double tm, double q, const string& flag, double target_price) const;
    void run_delta_hedging_on_real_data(const string& t0,
                                        const string& tm,
                                        const string& flag,
                                        double K,
                                        double q,
                                        vector<double> &interest_rates,
                                        vector<double> &sec_prices,
                                        vector<double> &op_prices,
                                        vector<vector<double>> &res);

public:

};


#endif //PROJECT_1_REALDELTAHEDGING_H
