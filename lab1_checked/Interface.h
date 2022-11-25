//
// Created by Elizaveta Kolesnikova on 14.11.2022.
//

#ifndef LAB1_CHECKED_INTERFACE_H
#define LAB1_CHECKED_INTERFACE_H


#include <iostream>
#include <string>
using namespace std;

int getInt()
{
    int res;
    cin >> res;
    while (!cin.good())
    {
        cout << "Ошибка ввода, повторите попытку\n";
        cin.clear();
        cin.ignore(255, '\n');
        cin >> res;
    }
    return res;
}
double getDouble(int n)
{
    double res;
    cin >> res;
    while (!cin.good())
    {
        cout << "Ошибка ввода, повторите попытку\n";
        cin.clear();
        cin.ignore(255, '\n');
        cin >> res;
    }
    return res;
}

int SpellCheck(int left, int right)
{
    int res = getInt();
    while (!(res >= left && res <= right))
    {
        cout << "Недопустимый номер, повторите попытку\n";
        res = getInt();
    }
    return res;
}


#endif //LAB1_CHECKED_INTERFACE_H
