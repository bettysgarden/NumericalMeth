//
// Created by Elizaveta Kolesnikova on 14.11.2022.
//

#ifndef LAB1_CHECKED_VECTOR_CLASS_H
#define LAB1_CHECKED_VECTOR_CLASS_H



#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

// константа для сравнения векторов

class vector_class {
    // Функцию, получающую файл на вход, и возвращающую последовательный контейнер, заполненный числами из файла.

    // Функцию вывода результата в файл и на экран (опционально).
public:

    vector<double> vec;
    int size;

    vector_class();
    vector_class(int n);

    // переопределение операций сложения и вычитания, скалярного умножения

    void FillVectorConsole();
    void FillVectorFile(ifstream& file); //заполнение вектора из файла

//    vector_class operator+ (const vector_class& sub);
//    vector_class operator- (const vector_class& sub);
    vector_class Multiply(const vector_class& sub);
    vector_class Minus(const vector_class& sub);
    double VecNorm();
    void GenerateVec(int m, int n);

    // вставить вывод
    void OutInConsole();


};
vector_class::vector_class() {
    size = 0;

}
vector_class::vector_class(int n) {
    size = n;
    for (int i = 0; i <= size; ++i) {
        vec.push_back(0);
    }
}

void vector_class::FillVectorFile(ifstream &file) {
    for (int i = 1; i <= size || !file.eof(); i++)
    {
        if (!file.eof())
            file >> vec[i];
    }
}

void vector_class::FillVectorConsole() {
    cout << "Введите вектор, из n элементов: \n";
    for (int i = 1; i <= size; i++)
    {
        cin >> vec[i];
    }
}

//vector_class vector_class::operator+(const vector_class &sub) {
//    for (int i = 1; i <= size; ++i)
//        this->vec[i] += sub.vec[i];
//}
//
//vector_class vector_class::operator-(const vector_class &sub) {
//    for (int i = 1; i <= size; ++i)
//        this->vec[i] -= sub.vec[i];
//}

vector_class vector_class::Multiply(const vector_class& sub) {
    vector_class res = vector_class(size);
    for (int i = 1; i <= size; ++i)
        this->vec[i] *= sub.vec[i];
    return res;
}
vector_class vector_class::Minus(const vector_class& sub) {
    vector_class res = vector_class(size);
    if (vec.size() == sub.vec.size()) {
        for (int i = 1; i <= size; ++i)
            res.vec[i] = vec[i] - sub.vec[i];
    }
    return res;
}

double vector_class::VecNorm() {
    double max = abs(vec[1]);
    for (int i = 1; i <= size; ++i) {
        if  (abs(vec[i]) > max)
            max = abs(vec[i]);
    }
    return max;
}

void vector_class::GenerateVec(int left, int right) {
    srand(time(NULL));
    for (int i = 1; i <= size; i++)
        this->vec[i] = ((double)rand() / (double)RAND_MAX * (right - left) + left);
}
void vector_class::OutInConsole() {
    for (int i = 1; i <= size; ++i)
        cout << vec[i]  << ' ';
}

// ввод границ с клавиатуры при генерации матрицы



#endif //LAB1_CHECKED_VECTOR_CLASS_H
