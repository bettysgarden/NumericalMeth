//
// Created by Elizaveta Kolesnikova on 14.11.2022.
//

#ifndef LAB1_CHECKED_MATR_CLASS_H
#define LAB1_CHECKED_MATR_CLASS_H

/*
 * • для работы с трёхдиагональными матрицами (сложение, вычитание, умножение на вектор,
 * считывание из файла / с экрана, вывод в файл / на экран; при задании матриц
 * предусматривать, что a1 = сn = 0 ).
 * Требования к реализации класса/процедур для работы с трёхдиагональными матрицами:
 * • хранение матрицы как трёх векторов;
 * • индексация элементов начиная с единицы;
 * • нумерация диагональных векторов по номеру строки;
 * • запрет на использование двумерного индексатора для матрицы.
 */
#include <iomanip> // библиотека манипулирования вводом/выводом
#include "vector_class.h"

class Matr_class {
    friend class vector_class;
    friend vector_class SweepMethod(Matr_class& matrix); // метод прогонки

    // нужно иниц size, чтобы создавать вектора автоматически заданного размера
    vector_class a;
    vector_class b;
    vector_class c;
public:
    int size;

    vector_class d;

    Matr_class();
    explicit Matr_class(int n);

    void CreateMatrixFromConsole();
    void CreateMatrixFromFile(ifstream &file);
    void GenerateMatrix();
    void GenerateMatrixExtra(int a, int b, int c, int d, int x, int y);

    void OutputToConsole();
    void OutputToFile();

    vector_class MultiplyMatrVec(const vector_class& v);

};

Matr_class::Matr_class() {
    size = 0;
    a = vector_class(size);
    b = vector_class(size);
    c = vector_class(size);
    d = vector_class(size);
}

Matr_class::Matr_class(int n) {
    size = n;
    a = vector_class(size);
    b = vector_class(size);
    c = vector_class(size);
    d = vector_class(size);
}

void Matr_class::CreateMatrixFromConsole() {
    cout << "Введите матрицу размерности " << size << " с консоли\n";
    a.FillVectorConsole();
    b.FillVectorConsole();
    c.FillVectorConsole();
    d.FillVectorConsole();

    // a1 = сn = 0
    a.vec[1] = c.vec[size] = 0;
}

void Matr_class::CreateMatrixFromFile(ifstream &file) {
    if (file.is_open())
    {
        for (int i = 1; i <= size && !file.eof(); i++)
        {
            if (!file.eof())
                file >> a.vec[i];
        }
        for (int i = 1; i <= size && !file.eof(); i++)
        {
            if (!file.eof())
                file >> b.vec[i];
        }
        for (int i = 1; i <= size && !file.eof(); i++)
        {
            if (!file.eof())
                file >> c.vec[i];
        }
        for (int i = 1; i <= size && !file.eof(); i++)
        {
            if (!file.eof())
                file >> d.vec[i];
        }

        // a1 = сn = 0
        a.vec[1] = c.vec[size] = 0;
    }
    else
        cout << "проблемы с открытием файла";
    file.close();
}

void Matr_class::GenerateMatrix() {
    cout << "Введите границы диапазона для генерирования вектора a: ";
    int n, m; cin  >> n >> m;
    a.GenerateVec(n,m);
    cout << "Введите границы диапазона для генерирования вектора b: ";
    cin  >> n >> m;
    b.GenerateVec(n,m);
    cout << "Введите границы диапазона для генерирования вектора c: ";
    cin  >> n >> m;
    c.GenerateVec(n,m);


    // a1 = сn = 0
    a.vec[1] = c.vec[size] = 0;
}
void Matr_class::GenerateMatrixExtra(int q, int w, int e, int r, int x, int y) {

    a.GenerateVec(q,w); // нижняя диагональ
    b.GenerateVec(e, r);
    c.GenerateVec(x, y);


    // a1 = сn = 0
    a.vec[1] = c.vec[size] = 0;
}

void Matr_class::OutputToConsole() {
    const int HalfSize = size / 2;
    for (int i = 1; i <= size; ++i) {
        //for (int j = 1; j <= size ; ++j) {
            // заполнение нулями когда они стоят в начале строк (с 3)
            if (i > HalfSize){
                for (int k = 0; k < i - HalfSize; ++k) {
                    cout << ' ' << '0' << ' ';
                }
            }
            // вывод диагональных векторов
            if (i != 1) // чтобы не учитывать а1
            {
                cout << ' ' << setprecision(3) << a.vec[i] << ' ';
            }
            cout << ' ' << setprecision(3) << b.vec[i] << ' ';
            if (i != size) {
                cout  << ' ' << setprecision(3) << c.vec[i] << ' ';
            }
            // заполнение нулями
            if (i <= HalfSize+1){
                for (int k = i + HalfSize; k <= size; ++k) {
                    cout << ' ' << '0' << ' ';
                }
            }
            // cout << "  " << d.vec[i];

        //}
        cout << endl;
    }

}
void Matr_class::OutputToFile() { // исправить открытие файла
    const int ElemCount = 3;
    for (int i = 1; i <= size; ++i) {
        for (int j = 1; j <= size ; ++j) {
            // заполнение нулями
            if (i >= ElemCount){
                for (int k = 1; k < i - k; ++k) {
                    cout << '0' << ' ';
                }
            }
            // вывод диагональных векторов
            if (i != 1) // чтобы не учитывать а1
            {
                cout << a.vec[i];
            }
            cout << b.vec[i];
            if (i != size) {
                cout << ' ' << c.vec[i];
            }
            // заполнение нулями
            if (i < 3){
                for (int k = ElemCount; k < k - i; ++k) {
                    cout << '0' << ' ';
                }
            }
            cout << "  " << d.vec[i];
        }
    }

}

vector_class Matr_class::MultiplyMatrVec(const vector_class &v) {
    if (v.size != size)
        cout << "ошибка. размерность вектора не совпадает с размерностью матрицы";
    else {
        vector_class res = vector_class(size);
        for (int i = 1; i <= size; ++i) {
            if (i != 1)
                res.vec[i] += a.vec[i] * v.vec[i-1];
            res.vec[i] += b.vec[i] * v.vec[i];
            if (i != size)
                res.vec[i] += c.vec[i] * v.vec[i+1];
        }
        if (res.size != size)
            cout << "ошибка при умножении вектора на матрицу";
        else
            return res;
    }
}


#endif //LAB1_CHECKED_MATR_CLASS_H
