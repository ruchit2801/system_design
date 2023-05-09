//
// Created by Ruchit Vithani on 9/17/22.
//

#ifndef HOMEWORK_2_BOND_H
#define HOMEWORK_2_BOND_H

#include<iostream>
#include<string>

using namespace std;

class Bond {
private:
    string expiration_date;
    double frequency;
    double coupon_rate;
public:
    Bond();
    virtual ~Bond();
    Bond(const Bond &bond_obj);
    Bond(string expirationDate, double frequency, double couponRate);

    string ToString();

    double Price(double face_value, double maturity_time, double interest_rate) const;
};


#endif //HOMEWORK_2_BOND_H
