//
// Created by Ruchit Vithani on 9/17/22.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "Bond.h"
#include "UnitTest.h"

using namespace std;



// A generic function to find maturity between any two valid dates
double find_maturity(const string& start_date, const string& end_date){
    int start_day, start_month, start_year, end_day, end_month, end_year;

    start_day =  stoi(start_date.substr(0, 2));
    start_month = stoi(start_date.substr(3, 2));
    start_year = stoi(start_date.substr(6, 4));

    end_day =  stoi(end_date.substr(0, 2));
    end_month = stoi(end_date.substr(3, 2));
    end_year = stoi(end_date.substr(6, 4));

    // ASSUMPTION: Each month is approximately 30 days. Therefore, I used 360 days in a year instead of 365.
    // This assumption gives better approximation to maturity number instead of using exact number of days.
    int total_days_diff = 0;
    int total_number_of_days_in_year = 360;

    // Step 1: Add days remaining in current year
    // First add days remaining in current month

    if (end_year != start_year){
        total_days_diff += 30 - start_day + 1;

        // Add days for remaining months in current year
        total_days_diff += (12 - start_month)*30;
    }

    // Step 2: Add days between start_year + 1 and end_year. We have already added days in the start_year
    if (end_year - start_year >= 1){
        total_days_diff += (end_year - start_year - 1) * total_number_of_days_in_year;
    }

    // Step 3: Add remaining days in the end year
    // Add days for remaining months in the end year
    total_days_diff += (end_month - 1)*30;
    // Add remaining days in the last month
    total_days_diff += end_day - 1;

    // Divide by 360 to get the approximate maturity
    return total_days_diff/double(total_number_of_days_in_year);
}

double find_interest_rate(vector<double> maturity, vector<double> interest_rate, double target_maturity){
    // Binary Search Algorithm to find the target interest rate
    int start = 0;
    int end = int(maturity.size()) - 1;
    int mid;

    while (start <= end){
        mid = (start + end) / 2;
        if (abs(maturity[mid] - target_maturity) <= 0.0001){
            return interest_rate[mid];
        } else if (maturity[mid] > target_maturity){
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return interest_rate[end + 1];
}


int main(){

    /************************************************************************/
    /***************************** QUESTION - 1 *****************************/
    /************************************************************************/
    Bond bond1 = Bond();
    Bond bond2 = Bond("19/11/2035", 0.5, 0.07);

    cout<<"Bond 1 characteristics (Bond initialised by default constructor): "<<bond1.ToString()<<endl;
    cout<<"Bond 2 characteristics: "<<bond2.ToString()<<endl;



    /************************************************************************/
    /***************************** QUESTION - 2 *****************************/
    /************************************************************************/
    // Note: The function to price the bond is implemented in Bond.cpp file
    // Let's check the results for example given in Excel file
    UnitTestBond::test_price_bond();



    /************************************************************************/
    /***************************** QUESTION - 3 *****************************/
    /************************************************************************/

    // Step 1: Read the interest rate time series data
    vector<double> maturity;
    vector<double> interest_rate;

    ifstream infile("./Bond_Ex3.csv");

    // Skip the header file
    string temp;
    getline(infile, temp, '\n');

    while (infile.good()){
        string maturity_value;
        string interest_rate_value;

        getline(infile, maturity_value, ',');
        getline(infile, interest_rate_value, '\n');

        if(interest_rate_value.empty() == 1){
            break;
        }

        maturity.push_back(stof(maturity_value));
        interest_rate.push_back(stof(interest_rate_value));
    }
    infile.close();

    // Step 2: Find the arithmetic average of security from 2016 to 2020
    Bond bond4 = Bond("01/01/2010", 0.5, 0.05);
    double total_bond_value = 0.0;
    cout << "\n\nUnderlying bond matures on: " << "01/01/2020" << endl;
    for(int year = 2016; year <=2020; year++){
        string start_date = "01/01/" + to_string(year);
        double curr_maturity = find_maturity(start_date, "01/01/2020");
        double curr_interest_rate = find_interest_rate(maturity,interest_rate, curr_maturity);
        cout <<"Current Date: "<<start_date <<"\tMaturity Date: 01/01/2020 \tMaturity value: "<<curr_maturity << "\tInterest Rate: " << curr_interest_rate <<endl;
        total_bond_value += bond4.Price(100, curr_maturity, curr_interest_rate);
    }

    double average_bond_value = total_bond_value / 5.0;
    cout << "\nArithmatic average price between 2016 and 2020: "<< average_bond_value<<endl;

    // Step 3: Discount the security
    double curr_maturity = find_maturity("03/08/2015", "31/12/2020");
    double curr_interest_rate = find_interest_rate(maturity, interest_rate, curr_maturity);
    cout <<"Current Date: 03/08/2015 \tMaturity Date: 01/01/2020 \tMaturity value: "<<curr_maturity << "\tInterest Rate: " << curr_interest_rate <<endl;

    double actual_price = average_bond_value * exp(-curr_maturity * curr_interest_rate);

    if (actual_price > 98.0){
        cout << "\n\nActual Price of security is: " << actual_price <<". It's a good investment!!! \n\n\n";
    } else {
        cout << "\n\nActual Price of security is: " << actual_price <<". It's a bad investment :( \n\n\n";
    }

    return 0;
}