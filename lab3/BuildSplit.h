//
// Created by Elizaveta Kolesnikova on 07.12.2022.
//

#ifndef LAB3_BUILDSPLIT_H
#define LAB3_BUILDSPLIT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "math.h"

using namespace std;
const double PI = 3.141592653589793;
const double EPS = 0.00000001;

bool CheckInfo(double left, double right, int nodeCount) {
    bool isEnd = false;
    do {
        if (abs(right - left) < EPS) {
            cout << "Правая граница меньше левой. Введите границы заново";
            cin >> left >> right;
            continue;
        } else if (nodeCount <= 0) {
            cout << "Количество узлов интерполяции не натуральное. Введите  заново";
            cin >> nodeCount;
            continue;
        } else {
            isEnd = true;
        }

    } while (!isEnd);
    return true;
}

vector<double> BuildPartitionChebyshev(double left, double right, int nodeCount) {
    vector<double> partitionRes;
    if (CheckInfo(left, right, nodeCount)) {
        for (int i = 0; i < nodeCount; ++i) {
            // x[i] = (a+b)/2 − (b−a)/2 · cos((2i+1)/(2n+2) · π)
            partitionRes.push_back(
                    (left + right) / 2.0 - (right - left) / 2.0 *
                                           cos((2.0 * i + 1.0) / (2.0 * nodeCount + 2.0) * PI));
        }
    }
    return partitionRes;
}

vector<double> BuildPartitionUniform(double left, double right, int nodeCount) {
    vector<double> partitionRes;
    if (CheckInfo(left, right, nodeCount)) {

        for (int i = 0; i < nodeCount; ++i) {
            //x[i] = a + (b−a)·i/n
            partitionRes.push_back(left + (right - left) * i / nodeCount);
        }
    }
    return partitionRes;
}


#endif //LAB3_BUILDSPLIT_H
