//
// Created by Elizaveta Kolesnikova on 07.12.2022.
//

#ifndef LAB3_POLYNOM_H
#define LAB3_POLYNOM_H


#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <cmath>
using namespace std;

class Polynom {
    friend vector<double> GetValuesFunction(double f(double), const vector<double>& x);
private:
    double a;
    double b;
    int n;
    vector<double> x;
    vector<double> diff;

public:
    Polynom(double a, double b, int n) {
        this->a = a;
        this->b = b;
        this->n = n;
    }
    double GetValue(double X)
    {
        double res = diff[0];
        double phi = 1;

        for (int i = 1; i < n; i++)
        {
            phi *= (X - x[i - 1]);
            res += diff[i] * phi;
        }
        return res;
    }
    vector<double> GetPolynom(const vector<double> xVal, vector<double> y){
        this->x = xVal;
        vector<double> polynom;
        polynom.push_back(y[0]);
        for (int i = 1; i < xVal.size(); i++){
            polynom.push_back(GetDividedDifferences(xVal, y, i));
        }
        this->diff = polynom;
        return polynom;

    }
    double GetDividedDifferences(const vector<double> xVal, vector<double>& y, int pow){
        vector<double> res;
        for (int i = 0; i < xVal.size(); ++i) {
            res.push_back(
                    (y[i+1] - y[i]) / (xVal[i + pow] - xVal[i])
            );
        }
        y = res;
        return res[0];
    }


};
vector<double> GetValuesFunction(double f(double), const vector<double>& x){
    vector<double> yRes;
    for (double i : x)
    {
        yRes.push_back(f(i));
    }
    return yRes;
}


#endif //LAB3_POLYNOM_H
