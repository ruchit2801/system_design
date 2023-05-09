//
// Created by Ruchit Vithani on 9/26/22.
//

#include "Option.h"

double Option::getStrikePrice() const {
    return strike_price;
}

double Option::getCurrentPrice() const {
    return current_price;
}

double Option::getRiskFreeRate() const {
    return risk_free_rate;
}

double Option::getTimeToMaturity() const {
    return time_to_maturity;
}

double Option::getVolatility() const {
    return volatility;
}

void Option::setStrikePrice(double strikePrice) {
    strike_price = strikePrice;
}

void Option::setCurrentPrice(double currentPrice) {
    current_price = currentPrice;
}

void Option::setRiskFreeRate(double riskFreeRate) {
    risk_free_rate = riskFreeRate;
}

void Option::setTimeToMaturity(double timeToMaturity) {
    time_to_maturity = timeToMaturity;
}

void Option::setVolatility(double vol) {
    volatility = vol;
}

Option Option::init() {
    Option res = Option(0.0, 0.0, 0.0, 0.0, 0.0);
    return res;
}

Option::Option(double strikePrice, double currentPrice, double riskFreeRate, double timeToMaturity, double volatility)
        : strike_price(strikePrice), current_price(currentPrice), risk_free_rate(riskFreeRate),
          time_to_maturity(timeToMaturity), volatility(volatility) {}

Option::Option(){
    this->init();
}

Option::~Option() = default;
