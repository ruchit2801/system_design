#include <iostream>
#include <vector>

#include "OptionPrice.h"
#include "UnitTest.h"

using namespace std;


int main() {

    // Running unit tests for BSM model
    cout<<"Running unit tests for BSM pricer model...."<<endl;
    UnitTest::test_BSM_Pricer();

    cout<<"\n\nRunning unit tests for Binomial pricer model"<<endl;
    // Running unit tests for binomial model
    UnitTest::test_Binomial_Pricer();
    cout<<"\n\n\n Pricing for custom input:\n";

    double strike_price, current_price, risk_free_rate, time_to_maturity, volatility;
    string option_flag;
    cout << "Enter Current Price of Underlying Asset: \n";
    cin >> current_price;
    cout << "Enter Strike Price: \n";
    cin >> strike_price;
    cout << "Enter Risk Free Rate: \n";
    cin >> risk_free_rate;
    cout << "Enter Time to Maturity: \n";
    cin >> time_to_maturity;
    cout << "Enter Volatility: \n";
    cin >> volatility;

    cout<< "Enter Option flag: \n";
    cin >> option_flag;


    OptionPrice option_pricer = OptionPrice(strike_price, current_price, risk_free_rate, time_to_maturity, volatility, option_flag);
    vector<double> binomial_prices = option_pricer.Binomial_Pricer();
    vector<double> bsm_prices = option_pricer.BSM_Pricer();
    cout << "\n\nS0: " << current_price << "\tK: " << strike_price << "\tT: " << time_to_maturity << "\t\tsigma: " << volatility << "\t\tr: " << risk_free_rate << "\t\tflag: " << option_flag <<endl;
    cout << "Binomial Price: "<<binomial_prices[0]<<endl;
    cout << "BSM Price: "<< bsm_prices[0]<<endl;
    if(option_flag == "C" || option_flag == "c"){
        cout << "Delta value: "<<bsm_prices[1]<< "  (N(d1), N(d1) - 1) = (" << bsm_prices[1] << ", " << bsm_prices[2] << ")" <<endl;
    } else {
        cout << "Delta value: "<<bsm_prices[2]<< "  (N(d1), N(d1) - 1) = (" << bsm_prices[1] << ", " << bsm_prices[2]  << ")" <<endl;
    }

    return 0;
}
