//
// Created by Ruchit Vithani on 9/17/22.
//

#include "UnitTest.h"
#include "Bond.h"
#include <vector>
#include <cmath>
using namespace std;
const double tolerance = 1e-2;


bool UnitTestBond::test_price_bond(){
//    vector<double> maturity, interest_rate, face_value, coupon_rate, frequency, target_price;
    double maturity[] = {4.2, 6, 1};
    double interest_rate[] = {0.07, 0.08, 0.09};
    double coupon_rate[] = {0.08, 0.1, 0.04};
    double face_value[] = {100.0, 100.0, 100.0};
    double frequency[] = {0.5, 0.3, 0.4};
    double target_price[] = {103.144, 108.961, 95.156};

    cout <<"\n\nRunning tests....\n";
    bool flag = true;
    for(int i=0;i<3;i++){
        Bond test_bond = Bond("01/01/2020", frequency[i], coupon_rate[i]);
        double test_price = test_bond.Price(face_value[i], maturity[i], interest_rate[i]);

        cout<<"Face Value: "<<face_value[i] <<"\tMaturity: "<<maturity[i]<<"\tInterest Rate: "<<interest_rate[i]<<"\tCoupon Rate: "<<coupon_rate[i]<<"\tFrequency: "<<frequency[i] << "\tTarget Price: "<<target_price[i];
        if(abs(test_price - target_price[i]) < tolerance){
            cout<<"\t Achieved Price: "<<test_price<<"\t OK!\n";
        } else {
            flag = false;
            cout<<"\t Achieved Price: "<<test_price<<"\t Failed!\n";
        }
    }
    return flag;
}







