#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

double average(vector<double> v)
{
    // code for calculating average of members of v
    // and returning the average
    double sum = 0.0;
    for(int i=0; i<v.size(); i++){
        sum += v[i];
    }

    return sum/v.size();
}

double find_rate(vector<double> rate_vec, vector<string> date_vec, string date)
{
    for(int i=0; i<date_vec.size(); i++){
        if (date_vec[i] == date){
            return rate_vec[i];
        }
    }
    cout<<"Date not found in the table\n";
    return 0.0;
}


// This function checks if the date entered by the user is valid or not
bool validate_date(string date) {
    string year, month;
    if (date.length() != 7) {
        cout<<"Length of the date string must be 7\n";
        return false;
    }
    if (date.substr(4, 1) != "-") {
        cout<<"Invalid date. Date must be in format yyyy-mm\n";
        return false;
    }

    year = date.substr(0, 4);
    month = date.substr(5, 2);

    int int_year, int_month;
    int_year = atof(year.c_str());
    int_month = atof(month.c_str());

    if (!(int_year>=1919 && int_year<=2013)){
        cout <<"Year must be between 1919 to 2013\n";
        return false;
    }

    if (!(int_month>=1 && int_month<=12)){
        cout << "Month must be between 1 to 12\n";
        return false;
    }

    if (int_year == 2013 && int_month>7){
        cout << "Date must be between 1919-01 to 2013-07\n";
        return false;
    }
    return true;
}

int main() {
    vector<double> rate;
    vector<string> date;
    ifstream infile("./hw1_H.15_Baa_Data.csv");

    // We want to drop the first six rows as they contain some metadata
    // which we do not want to store in our vectors
    for(int i=0; i<6; i++){
        string temp;
        getline(infile, temp, '\n');
    }
    // code for loading rate and date vectors from the file hw1_H.15_Baa_Data.csv
    // the headers should be handled properly. do not delete them manually
    while (infile.good()){
        string date_value;
        string rate_value;

        getline(infile, date_value, ',');
        getline(infile, rate_value, '\n');

        date.push_back(date_value);
        rate.push_back(atof(rate_value.c_str()));
    }


   infile.close();

// code for prompting user for a date and returning the rate
// and the difference between the rate for that date and the
// average rate
//
// This code should allow the user to continue to input dates
// until the user inputs the EOF (End-of-file), namely control-d (in linux/mac) or control-z (in windows)
// This should not crash if a bad date is entered.

    double avg = average(rate);

    string line;
    cout<<"Press enter key to start\n";
    while(getline(cin, line)){
        string inp_date;
        cout << "Enter date in yyyy-mm format: ";
        cin>> inp_date;
        if (!validate_date(inp_date)){
            cout<<"Please try again\n";
            continue;
        }

        double curr_rate = find_rate(rate, date, inp_date);
        cout<<"Rate on "<<inp_date<<": "<<curr_rate<<" | ";
        cout<<"Average: "<<avg<<" | ";
        cout<<"Difference: "<<curr_rate - avg<<endl;
    }
}

