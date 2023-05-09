//
// Created by Ruchit Vithani on 9/29/22.
//

#ifndef HOMEWORK_3_OPTIONPRICE_H
#define HOMEWORK_3_OPTIONPRICE_H


#include "Option.h"
#include "PricingMethod.h"
#include <string>

class OptionPrice: public Option, public PricingMethod{
public:
    explicit OptionPrice(double strike_price, double current_price, double risk_free_rate, double time_to_maturity, double volatility, std::string flag);

    std::string flag;

    vector<double> BSM_Pricer() override;
    vector<double> Binomial_Pricer() override;
};


#endif //HOMEWORK_3_OPTIONPRICE_H
