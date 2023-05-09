//
// Created by Ruchit Vithani on 10/14/22.
//

#include "Utils.h"
#include<iostream>
#include<vector>
using namespace std;

void Utils::read_inputs(string &flag, string &t0, string &tn, string &tm, double &strike_price){
    cout << "Enter option flag (c or p): \n";
    cin>>flag;

    cout << "Enter t0 (yyyy-mm-dd): \n";
    cin>>t0;

    cout << "Enter tn (yyyy-mm-dd): \n";
    cin>>tn;

    cout << "Enter t_maturity (yyyy-mm-dd): \n";
    cin>>tm;

    cout << "Enter strike_price: \n";
    cin>> strike_price;
}

void Utils::convert_percent_to_decimal(vector<double> &v){
    for(double & i : v){
        i = i*0.01;
    }
}

void Utils::get_op_prices(vector<double> bids, vector<double> offers, vector<double> &res){
    res.reserve(bids.size());
    for(int i=0;i<bids.size();i++){
        res.push_back((bids[i] + offers[i])/2.0);
    }
}