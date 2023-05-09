//
// Created by Ruchit Vithani on 10/8/22.
//

#include "CSVReader.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void CSVReader::read_csv(vector<vector<string>> &res, const string &path, int ncols, const string& t0, const string& tn) {
    for (int i = 0; i < ncols; i++) {
        vector<string> tmp;
        res.push_back(tmp);
    }

    ifstream infile(path);

    string val;
    getline(infile, val, '\n');
    while (infile.good()) {
        for (int i = 0; i < ncols; i++) {
            if (i == ncols-1) {
                getline(infile, val, '\n');
            } else {
                getline(infile, val, ',');
            }
            res[i].push_back(val);
        }
    }
}

void CSVReader::to_csv(vector<vector<string>> &res, const string &path, const string& header) {
    ofstream outfile(path);
    outfile << header;
    for (int i = 0; i < res[0].size(); i++) {
        for (int j = 0; j < res.size(); j++) {
            outfile << res[j][i];
            if (j == res.size() - 1) {
                outfile << "\n";
            } else {
                outfile << ", ";
            }
        }
    }
    outfile.close();
}

void CSVReader::cast_to_double(const vector<string> &source, vector<double> &target) {
    for (const auto &s: source) {
        target.push_back(stod(s));
    }
}

void CSVReader::cast_to_string(const vector<double> &source, vector<string> &target) {
    for (const auto &s: source) {
        target.push_back(to_string(s));
    }
}
