//
// Created by Ruchit Vithani on 10/1/22.
//

#include <iostream>
#include <vector>
#include "UnitTest.h"
#include "OptionPrice.h"

using namespace std;

bool UnitTest::test_BSM_Pricer() {
    double K[] = {250, 250, 58, 58};
    double S0[]=  {300, 300, 60, 60};
    double T[] = {1, 1, 0.5, 0.5};
    double sigma[] = {0.15, 0.15, 0.2, 0.2};
    double r[] = {0.03, 0.03, 0.035, 0.035};
    string flag[] = {"C", "P", "C", "P"};
    double target_prices[] = {58.82, 1.43, 5.02, 2.01};

    for(int i=0;i<sizeof(K)/sizeof K[0]; i++){
        OptionPrice op = OptionPrice(K[i], S0[i], r[i], T[i], sigma[i], flag[i]);
        vector<double> test_price = op.BSM_Pricer();
        if (abs(test_price[0] - target_prices[i]) < 1e-2){
            cout << "S0: " << S0[i] << "\tK: " << K[i] << "\tT: " << T[i] << "\t\tsigma: " << sigma[i] << "\t\tr: " << r[i] << "\t\tflag: " << flag[i] << "\t\tCalculated Price: " << test_price[0] << "\t\tTarget Price: " << target_prices[i] << "\t\tResult: " << "OK!" << endl;
        } else {
            cout << "S0: " << S0[i] << "\tK: " << K[i] << "\tT: " << T[i] << "\t\tsigma: " << sigma[i] << "\t\tr: " << r[i] << "\t\tflag: " << flag[i] << "\t\tCalculated Price: " << test_price[0] << "\t\tTarget Price: " << target_prices[i] << "\t\tResult: " << "Fail!" << endl;
        }
    }
    return false;
}

bool UnitTest::test_Binomial_Pricer() {
    double K[] = {250, 250, 58, 58};
    double S0[]=  {300, 300, 60, 60};
    double T[] = {1, 1, 0.5, 0.5};
    double sigma[] = {0.15, 0.15, 0.2, 0.2};
    double r[] = {0.03, 0.03, 0.035, 0.035};
    string flag[] = {"C", "P", "C", "P"};
    double target_prices[] = {58.82, 1.43, 5.02, 2.01};

    for(int i=0;i<sizeof(K)/sizeof K[0]; i++){
        OptionPrice op = OptionPrice(K[i], S0[i], r[i], T[i], sigma[i], flag[i]);
        vector<double> test_price = op.Binomial_Pricer();
        if (abs(test_price[0] - target_prices[i]) < 1e-2){
            cout << "S0: " << S0[i] << "\tK: " << K[i] << "\tT: " << T[i] << "\t\tsigma: " << sigma[i] << "\t\tr: " << r[i] << "\t\tflag: " << flag[i] << "\t\tCalculated Price: " << test_price[0] << "\t\tTarget Price: " << target_prices[i] << "\t\tResult: " << "OK!" << endl;
        } else {
            cout << "S0: " << S0[i] << "\tK: " << K[i] << "\tT: " << T[i] << "\t\tsigma: " << sigma[i] << "\t\tr: " << r[i] << "\t\tflag: " << flag[i] << "\t\tCalculated Price: " << test_price[0] << "\t\tTarget Price: " << target_prices[i] << "\t\tResult: " << "Fail!" << endl;
        }
    }
    return false;
}
