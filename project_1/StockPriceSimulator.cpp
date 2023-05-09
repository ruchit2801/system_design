//
// Created by Ruchit Vithani on 10/13/22.
//

#include<cmath>
#include <utility>
#include "StockPriceSimulator.h"
#include "StdNormal.h"
#include "BSM.h"

using namespace std;


StockPriceSimulator::StockPriceSimulator(double S0, double maturity, double mean, double sigma, double r, double strike_price, double dividend, int n, string option_flag) : S0(
        S0), maturity(maturity), mean(mean), sigma(sigma), r(r), strike_price(strike_price), dividend(dividend), N(n), option_flag(move(option_flag)) {}

StockPriceSimulator::~StockPriceSimulator() = default;

void StockPriceSimulator::SimulateStockPrice(vector<vector<double>> &res) const {
    vector<double>stock_prices, option_values, delta_values, beta_values, h_error_values, daily_error_values, pnl;

    double t, bt;
    t = maturity/N;
    bt = 1.0 / 252.0;

    for(int i=0;i<N;i++){

        if(i==0){
            stock_prices.push_back(S0);
        } else {
            double prev = stock_prices[i-1];
            stock_prices.push_back(prev + (mean * prev * t) + (sigma * prev * sqrt(t) * StdNormal::gen_normal()));
        }

        BSM option = BSM(strike_price, stock_prices[i], r, maturity - i*t, sigma, dividend, option_flag);
        option_values.push_back(option.BSM_Pricer());
        delta_values.push_back(option.getDeltaValue());

        double beta, h_error, daily_error;
        if (i==0) {
            beta = option_values[i] - (delta_values[i] * stock_prices[i]);
        } else {
            beta = delta_values[i-1] * stock_prices[i] + (beta_values[i-1] * exp(1.0 * r * bt)) - (delta_values[i] * stock_prices[i]);
        }
        beta_values.push_back(beta);

        if (i==0){
            h_error = 0.0;
        } else {
            h_error = delta_values[i-1] * stock_prices[i] + beta_values[i-1] * exp(r * bt) - option_values[i];
        }
        h_error_values.push_back(h_error);

        if (i == 0){
            daily_error = h_error_values[i];
        } else {
            daily_error =h_error_values[i] - h_error_values[i-1];
        }
        daily_error_values.push_back(daily_error);

        pnl.push_back(option_values[0] - option_values[i]);
    }

    res.push_back(stock_prices);
    res.push_back(option_values);
    res.push_back(delta_values);
    res.push_back(h_error_values);
    res.push_back(daily_error_values);
    res.push_back(pnl);
}