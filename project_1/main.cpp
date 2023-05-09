//
// Created by Ruchit Vithani on 10/8/22.
//

#include <iostream>
#include <vector>
#include<cmath>
#include <boost/algorithm/string.hpp>
#include "CSVReader.h"
#include "Utils.h"
#include "StockPriceSimulator.h"
#include "RealDeltaHedging.h"

using namespace std;

void task_1(int i){
    const string header = "stock_price,option_price,delta,hedging_error,pnl,pnl_with_hedge\n";
    vector<vector<double>> res;
    vector<vector<string>> res_str;
    StockPriceSimulator simulator = StockPriceSimulator(100.0, 0.4, 0.05, 0.24, 0.025, 105.0, 0.0, 100, "c");
    simulator.SimulateStockPrice(res);
    for(auto & re : res){
        vector<string> target;
        CSVReader::cast_to_string(re, target);
        res_str.push_back(target);
    }
    CSVReader::to_csv(res_str, "results/stock_simulations/stock_simulation_" + to_string(i) + ".csv", header);res.clear();
}

vector<vector<string>> filter_csv_1(vector<vector<string>>& source, const string& start, const string& end){
    vector<vector<string>> res{vector<string>{}, vector<string>{}};
    bool green = false;
    for(int i=0;i<source[0].size();i++){
        if(source[0][i] == start)green = true;

        if(green){
            res[0].push_back(source[0][i]);
            res[1].push_back(source[1][i]);
        }
        if(source[0][i] == end)break;
    }
    return res;
}

vector<vector<string>> filter_csv_2(vector<vector<string>>& source,
                                    const string& start,
                                    const string& mat,
                                    const string& end,
                                    const string& flag,
                                    double K){
    vector<vector<string>> res{vector<string>{}, vector<string>{}, vector<string>{}, vector<string>{}, vector<string>{}, vector<string>{}};
    bool green = false;
    bool last = false;
    for(int i=0;i<source[0].size();i++){
        if(source[0][i] == start)green = true;

        if(green){
            string c1, c2;
            c1 = flag;
            c2 = source[2][i];
            boost::algorithm::to_lower(c1);
            boost::algorithm::to_lower(c2);
            double d1 = stod(source[3][i]);

            if(source[1][i] == mat && c1 == c2 && fabs(d1 - K) < 1e-4){
                res[0].push_back(source[0][i]);
                res[1].push_back(source[1][i]);
                res[2].push_back(source[2][i]);
                res[3].push_back(source[3][i]);
                res[4].push_back(source[4][i]);
                res[5].push_back(source[5][i]);
            }

            if((source[0][i] == end) && !last)last=true;
            if((source[0][i] != end) && last)break;
        }
    }
    return res;
}


void task_2(){
    string flag, t0, tn, t_maturity;
    double strike_price;

    Utils::read_inputs(flag, t0, tn, t_maturity, strike_price);
//    flag = "c";
//    t0 = "2011-07-05";
//    tn = "2011-07-29";
//    t_maturity = "2011-09-17";
//    strike_price = 500.0;

    vector<vector<string>> interest_rates_data_tmp, sec_data_tmp, op_data_tmp;

    CSVReader::read_csv(interest_rates_data_tmp, "data/interest.csv", 2, t0, tn);
    CSVReader::read_csv(sec_data_tmp, "data/sec_GOOG.csv", 2, t0, tn);
    CSVReader::read_csv(op_data_tmp, "data/op_GOOG.csv", 6, t0, tn);

    vector<vector<string>> interest_rates_data, sec_data, op_data;
    interest_rates_data = filter_csv_1(interest_rates_data_tmp, t0, tn);
    sec_data = filter_csv_1(sec_data_tmp, t0, tn);
    op_data = filter_csv_2(op_data_tmp, t0, t_maturity, tn, flag, strike_price);

    vector<double> interest_rates, sec_prices, strike_prices, op_bid_prices, op_offer_prices, op_prices;

    CSVReader::cast_to_double(interest_rates_data[1], interest_rates);
    CSVReader::cast_to_double(sec_data[1], sec_prices);
    CSVReader::cast_to_double(op_data[3], strike_prices);
    CSVReader::cast_to_double(op_data[4], op_bid_prices);
    CSVReader::cast_to_double(op_data[5], op_offer_prices);

    Utils::convert_percent_to_decimal(interest_rates);
    Utils::get_op_prices(op_bid_prices, op_offer_prices, op_prices);

    vector<vector<double>> res;
    RealDeltaHedging hedge = RealDeltaHedging();
    hedge.run_delta_hedging_on_real_data(t0, t_maturity, flag, strike_price, 0.0, interest_rates, sec_prices, op_prices, res);

    vector<vector<string>> res_final{sec_data[0]};
    for(auto & re : res){
        vector<string> target;
        CSVReader::cast_to_string(re, target);
        res_final.push_back(target);
    }

    const string header = "date,stock_price,option_price,implied_volatility,delta,hedging_error,pnl,pnl_with_hedge\n";
    CSVReader::to_csv(res_final, "results/task_2/task_2_result.csv", header);
}


int main() {
    cout<<"Running task 1\n";
    for(int i=1;i<=1000;i++)
        task_1(i);
    cout<<"Task 1 done, results are saved in results/stock_simulatios folder\n";

    cout<<"Running task 2\n";
    task_2();
    cout<<"Task 2 done, results are saved in results/task_2 folder\n";
    cout<<"done\n";


    return 0;
}
