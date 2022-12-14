//
// Created by Elizaveta Kolesnikova on 07.12.2022.
//

#ifndef LAB3_ERRORCAL_H
#define LAB3_ERRORCAL_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "cmath"
#include "Polynom.h"
#include "BuildSplit.h"

using namespace std;
const int k = 30;

//class ErrorCal {
//private:
//    const int k = 30; // Кол-во подотрезков
//
//    Polynom polynom = Polynom(0, 0, 0);
//    int countPart;
//    int n;
//    int a;
//    int b;
//
//public:
//    ErrorCal(double a, double b, int n, double f(double)){
//        this->a = a;
//        this->b = b;
//        this->n = n;
//        countPart = n * k;
//        polynom =  Polynom(a, b, n);
////        vector<double> part = BuildPartitionUniform(a, b , n);
////
////        polynom.GetPolynom()
//
//    }

    double MaxError(vector<double> seg, double f(double), Polynom pol){
        vector<double> fVal;
        vector<double> polVal;
        // int countPart = k * n;
        for (double i : seg)
            fVal.push_back(f(i));
        for (double i : seg)
            polVal.push_back(pol.GetValue(i));
        vector<double> errors;
        for (int i = 0; i < fVal.size(); i++)
            errors.push_back(abs(polVal[i] - fVal[i]));
        double _max;
        for (double i : errors)
            _max = _max < i ? i : _max;
        return _max;
    }
    double UniformMaxError(double f(double), int n, double a, double b){
        auto partition = BuildPartitionUniform(a, b, n);
        Polynom pol = Polynom(a, b, n);
        pol.GetPolynom(partition, GetValuesFunction(f, partition));
        vector<double> intermediateSegments;
        for (int i = 0; i < n; ++i) {
            vector<double> x = BuildPartitionUniform(partition[i], partition[i + 1], k);
            for (int j = 0; j < k; ++j) {
                intermediateSegments.push_back(x[j]);
            }
        }
        return MaxError(intermediateSegments, f, pol);
    }
    double ChebyshevMaxError(double f(double), int n, double a, double b){
        auto partition = BuildPartitionChebyshev(a, b, n);
        Polynom pol = Polynom(a, b, n);
        pol.GetPolynom(partition, GetValuesFunction(f, partition));
        vector<double> intermediateSegments;
        for (int i = 0; i < n; ++i) {
            vector<double> x = BuildPartitionUniform(partition[i], partition[i + 1], k);
            for (int j = 0; j < k; ++j) {
                intermediateSegments.push_back(x[j]);
            }
        }
        return MaxError(intermediateSegments, f, pol);
    }

//};


#endif //LAB3_ERRORCAL_H
