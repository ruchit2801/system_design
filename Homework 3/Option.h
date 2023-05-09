//
// Created by Ruchit Vithani on 9/26/22.
//

#ifndef HOMEWORK_3_OPTION_H
#define HOMEWORK_3_OPTION_H


class Option {
private:
    double strike_price{};
    double current_price{};
    double risk_free_rate{};
    double time_to_maturity{};
    double volatility{};

    static Option init();
public:
    double getStrikePrice() const;

    double getCurrentPrice() const;

    double getRiskFreeRate() const;

    double getTimeToMaturity() const;

    double getVolatility() const;

    void setStrikePrice(double strikePrice);

    void setCurrentPrice(double currentPrice);

    void setRiskFreeRate(double riskFreeRate);

    void setTimeToMaturity(double timeToMaturity);

    void setVolatility(double volatility);


    Option();
    Option(double strikePrice, double currentPrice, double riskFreeRate, double timeToMaturity, double volatility);

    virtual ~Option();
};


#endif //HOMEWORK_3_OPTION_H
