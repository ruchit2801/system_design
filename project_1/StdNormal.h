//
// Created by Ruchit Vithani on 10/8/22.
//

#ifndef PROJECT_1_STDNORMAL_H
#define PROJECT_1_STDNORMAL_H




class StdNormal {
private:
    double a1 = 0.319381530;
    double a2 = -0.356563782;
    double a3 = 1.781477937;
    double a4 = -1.821255978;
    double a5 = 1.330274429;
    double p = 0.2316419;

    double R_(double z) const;

public:
    StdNormal(){}
    double operator() (double);
    static double gen_normal();
    ~StdNormal(){}

};




#endif //PROJECT_1_STDNORMAL_H
