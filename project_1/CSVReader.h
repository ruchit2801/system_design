//
// Created by Ruchit Vithani on 10/8/22.
//

#ifndef PROJECT_1_CSVREADER_H
#define PROJECT_1_CSVREADER_H

#include<iostream>
#include<vector>
using namespace std;

class CSVReader {
public:
    static void read_csv(vector<vector<string>> &res, const string& path, int ncols, const string& t0, const string& tn);
    static void to_csv(vector<vector<string>> &res, const string &path, const string& header);
    static void cast_to_double(const vector<string>& source, vector<double>& target);
    static void cast_to_string(const vector<double>& source, vector<string>& target);
};


#endif //PROJECT_1_CSVREADER_H
