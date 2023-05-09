//
// Created by Ruchit Vithani on 9/29/22.
//

#include "OptionPrice.h"

#include <utility>
#include <cmath>
#include <vector>

using namespace std;

vector<vector<double>> build_tree(double S0, int n, double u, double d){
    vector<vector<double>> result;
    result.push_back(vector<double>{S0});
    for(int i=0;i<n;i++){
        vector<double> previous_layer = result[i];
        vector<double> current_layer;
        for(int j=0;j<previous_layer.size();j++){
            if(j==0){
                current_layer.push_back(previous_layer[j]*u);
                current_layer.push_back(previous_layer[j]*d);
            } else {
                current_layer.push_back(previous_layer[j]*d);
            }
        }
        result.push_back(current_layer);
    }

    return result;
}

vector<vector<double>> compute_price_backwards(const vector<double>& terminal_layer, int n, double p, double q, double discount_factor) {
    vector<vector<double>> backwards_tree;
    backwards_tree.push_back(terminal_layer);

    for(int i=0;i<n;i++){
        vector<double> previous_layer = backwards_tree[i];
        vector<double> current_layer;
        for(int j=0;j<previous_layer.size()-1; j++){
            double val = discount_factor * (p * previous_layer[j] + q * previous_layer[j+1]);
            current_layer.push_back(val);
        }
        backwards_tree.push_back(current_layer);
    }
    return backwards_tree;
}

vector<double> get_terminal_layer(const vector<double>& terminal_layer, const string& flag, double strike_price) {
    vector<double> result;
    if(flag == "c" || flag == "C"){
        for(double e : terminal_layer){
            result.push_back(max(e - strike_price, 0.0));
        }
    } else {
        for(double e : terminal_layer) {
            result.push_back(max(strike_price - e, 0.0));
        }
    }
    return result;
}

double get_d1(double sigma, double T, double t, double St, double K, double r){
    return (log(St/K) + ((r + (pow(sigma, 2)/2)) * (T - t)))/(sigma * sqrt(T - t));
}

double get_d2(double d1, double sigma, double T, double t){
    return d1 - sigma * sqrt(T - t);
}

double N(double x){
    // REFERENCE: https://stackoverflow.com/a/2329269/13952588

    double a1 =  0.254829592;
    double a2 = -0.284496736;
    double a3 =  1.421413741;
    double a4 = -1.453152027;
    double a5 =  1.061405429;
    double p  =  0.3275911;

    int sign = 1;
    if (x < 0)
        sign = -1;
    x = fabs(x)/sqrt(2.0);

    double t = 1.0/(1.0 + p*x);
    double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);

    return 0.5*(1.0 + sign*y);
}

vector<double> OptionPrice::BSM_Pricer() {
    vector<double> res;
    double d1, d2;
    d1 = get_d1(this->getVolatility(), this->getTimeToMaturity(), 0.0, this->getCurrentPrice(), this->getStrikePrice(), this->getRiskFreeRate());
    d2 = get_d2(d1, this->getVolatility(), this->getTimeToMaturity(), 0.0);

    if(this->flag == "C" or this->flag == "c"){
        res.push_back((this->getCurrentPrice() * N(d1)) - (this->getStrikePrice() * N(d2) * exp(-1*this->getRiskFreeRate()*this->getTimeToMaturity())));
    } else {
        res.push_back((-this->getCurrentPrice() * N( -d1)) + (this->getStrikePrice() * N(-d2) * exp(-1*this->getRiskFreeRate()*this->getTimeToMaturity())));
    }
    res.push_back(N(d1));
    res.push_back(N(d1) - 1);
    return res;
}


vector<double> OptionPrice::Binomial_Pricer() {
    vector<double> res;

    int number_of_periods = 50;
    double u, d;
    u = exp(this->getVolatility() * sqrt(this->getTimeToMaturity()/(number_of_periods*1.0)));
    d = pow(u, -1);

    double r;
    r = exp(this->getRiskFreeRate() * this->getTimeToMaturity()/(1.0*number_of_periods));

    double p, q, discount_factor;
    p = (r - d) / (u - d);
    q = 1 - p;
    discount_factor = exp(-1*this->getRiskFreeRate()*(this->getTimeToMaturity()/(1.0*number_of_periods)));
    vector<vector<double>> binomial_tree = build_tree(this->getCurrentPrice(), number_of_periods, u, d);
    vector<double> terminal_layer = get_terminal_layer(binomial_tree[binomial_tree.size()-1], this->flag, this->getStrikePrice());
    vector<vector<double>> backwards_tree = compute_price_backwards(terminal_layer, number_of_periods, p, q, discount_factor);

    double d1;
    d1 = get_d1(this->getVolatility(), this->getTimeToMaturity(), 0.0, this->getCurrentPrice(), this->getStrikePrice(), this->getRiskFreeRate());

    res.push_back(backwards_tree[backwards_tree.size()-1][0]);
    res.push_back(N(d1));
    res.push_back(N(d1) - 1);
    return res;
}

OptionPrice::OptionPrice(double strike_price, double current_price, double risk_free_rate, double time_to_maturity,
                         double volatility, std::string flag) {
    this->setStrikePrice(strike_price);
    this->setCurrentPrice(current_price);
    this->setRiskFreeRate(risk_free_rate);
    this->setTimeToMaturity(time_to_maturity);
    this->setVolatility(volatility);
    this->flag = std::move(flag);
}


