#include <iostream>
#include "ErrorCal.h"

void Test(double f(double), const string& s) {
    cout << "\nФункция: " << s;
    cout << "\nВведите отрезок (правую и левую границу)\n";
    cout << "-> ";
    double a, b;
    cin >> a >> b;
    cout << "Введите количество разбиений (n)\n";
    cout << "-> ";
    int n;
    cin >> n;
    cout << "\nУзлов интерполяции:" << n;
    cout << "\nПогрешность при равномерном распределении: " << UniformMaxError(f, n, a, b);
    cout << "\nПогрешность при Чебышевском распределении: " << ChebyshevMaxError(f, n, a, b);
    cout << endl;
}
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


int main() {
    int typeChoice;
    do {
        cout << "\nНачало работы\n";
        cout << "[1] 1/(x + 1) \n";
        cout << "[2] Cos(x)\n";
        cout << "[3] |x|\n";
        cout << "[4] 2x^3 + 5x^2 + 7x + 3\n";
        cout << "[0] Завершить работу\n";
        cout << "-> ";

        typeChoice = SpellCheck(0, 4);
        switch (typeChoice) {
            case 1: {
                Test([](double (x)) {return (1 / (x + 1));}, "1/(x + 1)");
                break;
            }
            case 2: {
                Test(cos, "Cos(x)");
                break;
            }
            case 3: {
                Test(abs, "|x|");
                break;
            }
            case 4: {
                Test([](double (x)) {return(2 * pow(x, 3) + 5 * pow(x, 2) + 7 * x + 3);},
                              "2x^3 + 5x^2 + 7x + 3");
                break;
            }
            default:
                cout << "Произошла ошибка ввода";

        }
    } while (typeChoice != 0);


    return 0;
}
