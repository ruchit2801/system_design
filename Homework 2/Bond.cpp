//
// Created by Ruchit Vithani on 9/17/22.
//

#include "Bond.h"

#include <utility>
#include <cmath>

using namespace std;

// Custom constructor
Bond::Bond(string expirationDate, double frequency, double couponRate) : expiration_date(std::move(expirationDate)),
                                                                                frequency(frequency),
                                                                                coupon_rate(couponRate) {}
// Default constructor
Bond::Bond(){
    expiration_date = "00/00/0000";
    frequency = 0.0;
    coupon_rate = 0.0;
}

// Copy constructor
Bond::Bond(const Bond &bond_obj){
    expiration_date = bond_obj.expiration_date;
    frequency = bond_obj.frequency;
    coupon_rate = bond_obj.coupon_rate;
}

// Define destructor and set it to default destructor
Bond::~Bond(){};

string Bond::ToString(){
    return "Bond(" + this->expiration_date + "," + to_string(this->frequency) + "," + to_string(this->coupon_rate) + ")";
}

double Bond::Price(double face_value, double maturity_time, double interest_rate) const {
    double present_value = 0;

    int n =  floor(maturity_time / this->frequency);
    double regular_coupon = face_value * this-> coupon_rate * this->frequency;
    double last_coupon = (maturity_time - n * this->frequency) * this->coupon_rate * face_value;
    double last_amount = last_coupon + face_value;

    double discount_factor;
    for (int i=1; i <= n; i++){
        discount_factor = exp(-1 * interest_rate * this->frequency * i);
        present_value += discount_factor*regular_coupon;
    }

    discount_factor = exp(-1 * interest_rate * maturity_time);
    present_value += discount_factor * last_amount;

    return present_value;
}



