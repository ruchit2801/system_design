//
// Created by Ruchit Vithani on 10/14/22.
//

#include "RealDeltaHedging.h"
#include <ql/quantlib.hpp>
#include<cmath>
#include<vector>

using namespace std;

double RealDeltaHedging::get_implied_volatility(double K, double S0, double r, double tm, double q, const string &flag,
                                                double target_price) const {
    double left = this->L;
    double right = this->R;

    double sigma = 0.5*(left + right);
    BSM option = BSM(K, S0, r, tm, sigma, q, flag);
    double cal_price = option.BSM_Pricer();

    do {
        if(cal_price < target_price){
            left = sigma;
        }

        if(cal_price > target_price){
            right = sigma;
        }
        sigma = 0.5*(left + right);
        option = BSM(K, S0, r, tm, sigma, q, flag);
        cal_price = option.BSM_Pricer();
    } while (fabs(cal_price-target_price) > tolerance);

    return sigma;
}


int date_diff(const string &t0, const string &tn) {
    QuantLib::Calendar calendar = QuantLib::UnitedStates(QuantLib::UnitedStates::Settlement);
    QuantLib::Date d_t0, d_tn;

    d_t0 = QuantLib::DateParser::parseFormatted(t0, "%Y-%m-%d");
    d_tn = QuantLib::DateParser::parseFormatted(tn, "%Y-%m-%d");

    return calendar.businessDaysBetween(d_t0, d_tn, true, true);
}

void RealDeltaHedging::run_delta_hedging_on_real_data(const string &t0,
                                                      const string &tm,
                                                      const string &flag,
                                                      double K,
                                                      double q,
                                                      vector<double> &interest_rates,
                                                      vector<double> &sec_prices,
                                                      vector<double> &op_prices,
                                                      vector<vector<double>> &res) {
    vector<double> implied_volatilities;
    vector<double> delta_values;
    vector<double> beta_values;
    vector<double> h_error_values;
    vector<double> daily_error_values;
    vector<double> pnl;

    double vol, beta, h_error, dt, duration;
    dt = 1.0 / 252.0;

    duration = date_diff(t0, tm) / 252.0;

    for (int i = 0; i < interest_rates.size(); i++) {
        vol = this->get_implied_volatility(K, sec_prices[i], interest_rates[i], duration - dt * i, q, flag,
                                           op_prices[i]);
        implied_volatilities.push_back(vol);

        BSM option = BSM(K, sec_prices[i], interest_rates[i], duration - dt * i, vol, q, flag);
        delta_values.push_back(option.getDeltaValue());

        if (i == 0) {
            beta = op_prices[i] - (delta_values[i] * sec_prices[i]);
        } else {
            beta = delta_values[i - 1] * sec_prices[i] + beta_values[i - 1] * exp(1.0 * interest_rates[i - 1] * dt) -
                   delta_values[i] * sec_prices[i];
        }
        beta_values.push_back(beta);

        if (i == 0) {
            h_error = 0.0;
        } else {
            h_error = delta_values[i - 1] * sec_prices[i] + beta_values[i - 1] * exp(1.0 * interest_rates[i - 1] * dt) -
                      op_prices[i];
        }
        h_error_values.push_back(h_error);

        if (i == 0) {
            daily_error_values.push_back(h_error_values[i]);
        } else {
            daily_error_values.push_back(h_error_values[i] - h_error_values[i - 1]);
        }
        pnl.push_back(op_prices[0] - op_prices[i]);
    }

    res.push_back(sec_prices);
    res.push_back(op_prices);
    res.push_back(implied_volatilities);
    res.push_back(delta_values);
    res.push_back(h_error_values);
    res.push_back(pnl);
    res.push_back(h_error_values);
}
