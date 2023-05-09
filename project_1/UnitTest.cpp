//
// Created by Ruchit Vithani on 10/8/22.
//

#include "UnitTest.h"
#include "RealDeltaHedging.h"
#include "BSM.h"

#include <iostream>
#include<cstdio>
#include <cmath>
#include<vector>
using namespace std;

// The values of target_volatilises are obtained from https://optioncreator.com/options-calculator
void UnitTest::test_get_implied_volatility() {
    vector<double> S0{100.0, 100.0, 500.0, 500.0};
    vector<double> K{105.0, 105.0, 525.0, 525.0};
    vector<double> maturity{1.00, 1.00, 0.50, 0.50};
    vector<double> r{0.02, 0.02, 0.04, 0.04};
    vector<double> option_price{12.0, 12.0, 20.0, 20.0};
    vector<double> target_volatility{0.332849, 0.259530, 0.186500, 0.078404};
    vector<string> flag{"C", "P", "C", "P"};

    cout<<"S0\tK\tTm\t r\tV\t\tflag\ttarget\t\tcalculated\terror\t\tresult\n";
    for(int i=0;i<4;i++){
        RealDeltaHedging hedge = RealDeltaHedging();
        double iv = hedge.get_implied_volatility(K[i], S0[i], r[i], maturity[i], 0.0, flag[i], option_price[i]);
        double err = fabs(iv - target_volatility[i]);
        if(err<1e-2){
            printf("%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.4f\t\t%s\t%0.6f\t%0.6f\t%0.6f\t%s",S0[i],K[i],maturity[i],r[i],option_price[i],flag[i].c_str(),target_volatility[i], iv, err, "OK\n");
        } else{
            printf("%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.4f\t\t%s\t%0.6f\t%0.6f\t%0.6f\t%s",S0[i],K[i],maturity[i],r[i],option_price[i],flag[i].c_str(),target_volatility[i], iv, err, "FAIL!!\n");
        }
    }
}

void UnitTest::test_get_delta_value() {
    vector<double> S0{100.0, 100.0, 500.0, 500.0};
    vector<double> K{105.0, 105.0, 525.0, 525.0};
    vector<double> maturity{1.00, 1.00, 0.50, 0.50};
    vector<double> r{0.02, 0.02, 0.04, 0.04};
    vector<double> vol{0.332849, 0.332849, 0.186500, 0.186500};
    vector<double> target_delta{0.5319, -0.4681, 0.4395, -0.5605};
    vector<string> flag{"C", "P", "C", "P"};

    cout<<"S0\tK\tTm\t r\tsigma\t\tflag\ttarget\t\tcalculated\terror\t\tresult\n";
    for(int i=0;i<4;i++){
        BSM option = BSM(K[i], S0[i], r[i], maturity[i], vol[i], 0.0, flag[i]);
        double delta = option.getDeltaValue();
        double err = fabs(delta - target_delta[i]);
        if(err<1e-2){
            printf("%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.6f\t%s\t%0.6f\t%0.6f\t%0.6f\t%s",S0[i],K[i],maturity[i],r[i],vol[i],flag[i].c_str(),target_delta[i], delta, err, "OK\n");
        } else{
            printf("%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.6f\t%s\t%0.6f\t%0.6f\t%0.6f\t%s",S0[i],K[i],maturity[i],r[i],vol[i],flag[i].c_str(),target_delta[i], delta, err, "FAIL!!\n");
        }
    }

}

int main(){
    cout<<"Running tests......\n";
    cout<<"\ntest_get_implied_volatility\n";
    UnitTest::test_get_implied_volatility();
    cout<<"Done\n\n\n";

    cout<<"\ntest_get_delta_value\n";
    UnitTest::test_get_delta_value();
    cout<<"Done\n\n\n";
    return 0;
}
