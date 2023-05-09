//
// Created by Ruchit Vithani on 9/29/22.
//

#ifndef HOMEWORK_3_OPTIONPRICE_H
#define HOMEWORK_3_OPTIONPRICE_H


#include <string>

using namespace std;


class BSM{
private:
    double strike_price;
    double current_price;
    double risk_free_rate;
    double time_to_maturity;
    double volatility;
    double dividend;
    string flag;
public:
    BSM(double strike_price, double current_price, double risk_free_rate, double time_to_maturity, double volatility, double dividend, string flag);
    virtual ~BSM();
    double BSM_Pricer();
    double getDeltaValue();
    double getDerivative() const;

    double getStrikePrice() const;

    double getCurrentPrice() const;

    double getRiskFreeRate() const;

    double getTimeToMaturity() const;

    double getVolatility() const;

    double getDividend() const;

    const string &getFlag() const;
};

#endif //HOMEWORK_3_OPTIONPRICE_H
