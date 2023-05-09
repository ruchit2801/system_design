//
// Created by Ruchit Vithani on 10/14/22.
//

#ifndef PROJECT_1_UTILS_H
#define PROJECT_1_UTILS_H

#include <iostream>

using namespace std;

class Utils {
public:
    static void read_inputs(string &flag, string &t0, string &tn, string &tm, double &strike_price);
    static void convert_percent_to_decimal(vector<double> &v);
    static void get_op_prices(vector<double> bids, vector<double> offers, vector<double> &res);
};


#endif //PROJECT_1_UTILS_H
