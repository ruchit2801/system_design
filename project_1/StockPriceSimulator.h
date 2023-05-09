//
// Created by Ruchit Vithani on 10/13/22.
//

#ifndef PROJECT_1_STOCKPRICESIMULATOR_H
#define PROJECT_1_STOCKPRICESIMULATOR_H

#include <iostream>
#include <vector>

using namespace std;

class StockPriceSimulator {
private:
    double S0, maturity, mean, sigma, r, strike_price, dividend;
    int N;
    string option_flag;
public:
    StockPriceSimulator(double s0, double maturity, double mean, double sigma, double r, double strike_price, double dividend, int n, string option_flag);
    virtual ~StockPriceSimulator();
    void SimulateStockPrice(vector<vector<double>> &res) const;
};


#endif //PROJECT_1_STOCKPRICESIMULATOR_H
