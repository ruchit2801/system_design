//
// Created by Ruchit Vithani on 9/29/22.
//

#include "BSM.h"
#include "StdNormal.h"

#include <utility>
#include <cmath>

using namespace std;

double get_d1(double sigma, double T, double t, double St, double K, double r){
    return (log(St/K) + ((r + (pow(sigma, 2)/2)) * (T - t)))/(sigma * sqrt(T - t));
}

double get_d2(double d1, double sigma, double T, double t){
    return d1 - sigma * sqrt(T - t);
}

double BSM::getStrikePrice() const {
    return strike_price;
}

double BSM::getCurrentPrice() const {
    return current_price;
}

double BSM::getRiskFreeRate() const {
    return risk_free_rate;
}

double BSM::getTimeToMaturity() const {
    return time_to_maturity;
}

double BSM::getVolatility() const {
    return volatility;
}

double BSM::getDividend() const {
    return dividend;
}

const string &BSM::getFlag() const {
    return flag;
}


double BSM::getDeltaValue() {
    StdNormal N = StdNormal();
    double d1 = get_d1(volatility, time_to_maturity, 0.0, current_price, strike_price, risk_free_rate);
    if(this->flag == "C" or this->flag == "c"){
        return exp(-1.0*dividend * time_to_maturity) * N(d1);
    } else {
        return exp(-1.0 * dividend * time_to_maturity) * (N(d1) - 1);
    }
}



double BSM::BSM_Pricer() {
    StdNormal N = StdNormal();

    double d1, d2;
    d1 = get_d1(volatility, time_to_maturity, 0.0, current_price, strike_price, risk_free_rate);
    d2 = get_d2(d1, volatility, time_to_maturity, 0.0);

    if(this->flag == "C" or this->flag == "c"){
        return (current_price * exp(-1.0 * dividend * time_to_maturity) * N(d1)) - ((strike_price * N(d2) * exp(-1*risk_free_rate*time_to_maturity)));
    } else {
        return (-current_price * exp(-1.0 * dividend * time_to_maturity) * N( -d1)) + (strike_price * N(-d2) * exp(-1.0*risk_free_rate*time_to_maturity));
    }
}


double BSM::getDerivative() const {
    double d1 = get_d1(volatility, time_to_maturity, 0.0, current_price, strike_price, risk_free_rate);
    double der = 0.39894244888 * exp(-0.5 * pow(d1,2));
    return current_price * sqrt(time_to_maturity) * der * exp(-dividend * time_to_maturity);
}

BSM::BSM(double strikePrice, double currentPrice, double riskFreeRate, double timeToMaturity, double volatility,
         double dividend, string flag) : strike_price(strikePrice), current_price(currentPrice),
                                                risk_free_rate(riskFreeRate), time_to_maturity(timeToMaturity),
                                                volatility(volatility), dividend(dividend), flag(std::move(flag)) {}

BSM::~BSM() = default;
