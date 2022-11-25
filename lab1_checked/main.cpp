#include <iostream>
#include <string>
#include "Matr_class.h"
#include "Interface.h"

const auto EPSILON = 0.00001;

void menu();
void Solution(Matr_class &matrix);
void ComputationalExperiment(Matr_class& matrix, vector_class xExactS); // вычислительный эксперимент
void Error(vector_class& exact, vector_class& countedSol);
void tableExperiment(int q, int w, int e, int r, int x, int y);


int main() {

//    cout << "Введите размерность вектора: ";
//    int n; cin >> n;
//    vector_class cur = vector_class(n);
//    cur.FillVectorConsole();
//    cur.OutInConsole();
    menu();

    return 0;
}
void menu() {
    int choice;
    do
    {
        cout << "\nНачало работы\n";
        cout << "[1] Начать работу -- метод прогонки \n";
        cout << "[2] Вычислительный эксперимент\n";
        cout << "[0] Завершить работу\n";
        cout << "-> ";
        choice = SpellCheck(0, 2);
        if (choice == 1)
        {
            // выбрать способ заполнения
            cout << "\nВыберите способ ввода исходных данных\n";
            cout << "[1] С клавиатуры\n";
            cout << "[2] Чтение из файла\n";
            cout << "[3] Сгенерировать случайным образом\n";
            cout << "-> ";
            int typeChoice = SpellCheck(1, 3);
            cout << "Введите размерность матрицы: "; int n = getInt();
            const int MatrSize = n;
            // создать объект класса матрицы
            Matr_class matr = Matr_class(MatrSize);
            switch (typeChoice)
            {
                case 1:
                {
                    matr.CreateMatrixFromConsole();
                    Solution(matr);

                    break;
                }
                case 2:
                {
                    // сделать работу с файлом

                    string fileName;
                    cout << "Введите имя файла: ";
                    cin >> fileName;
                    ifstream file(fileName);
                    if (file.is_open())
                        matr.CreateMatrixFromFile(file);
                    else cout << "произошла ошибка с открытием файла";
                    file.close();
                    Solution(matr);

                    break;
                }
                case 3:
                {
                    // ввести границы
                    // отредактировать функцию, чтобы генерировала double
                    matr.GenerateMatrix();
                    Solution(matr);

                    break;
                }
                default:
                    choice = 2;
            }

        }
        else if (choice == 2){
            cout << "\nВыберите действие\n";
            cout << "[1] Тестовый пример\n";
            cout << "[2] Вычислительный эксперимент (таблицы погрешностей)\n";
            cout << "-> ";
            int typeChoice = SpellCheck(1, 2);
            switch (typeChoice) {
                case 1: {
                    const int MatrSize = 5;
                    // создать объект класса матрицы
                    Matr_class matr = Matr_class(MatrSize);

                    ifstream in1("test1.txt");
                    ifstream in2("test2.txt");
                    vector_class x = vector_class(MatrSize);
                    if (in1.is_open() && in2.is_open()) {
                        matr.CreateMatrixFromFile(in1);
                        x.FillVectorFile(in2);
                    }
                    else cout << "произошла ошибка с открытием файла";
                    in1.close();
                    in2.close();
                    cout << endl;
//                    cout << "Данная матрица: \n";
//                    matr.OutputToConsole();
                    ComputationalExperiment(matr, x);

                    break;
                }
                case 2: {
                    cout << "\nМатрица с перегруженной главной диагональю.\n\n";
                    tableExperiment(20, 30,
                                    200, 300,
                                    20, 30);

                    cout << "\nМатрица с перегруженной нижней диагональю.\n\n";
                    tableExperiment(20, 30,
                                    20, 30,
                                    200, 300);
                    cout << "\nМатрица с перегруженной верхней диагональю.\n\n";
                    tableExperiment(200, 300,
                                    20, 30,
                                    20, 30);
                    cout << endl;
                    cout << "\nМатрица с перегруженной верхней и нижней диагоналями.\n\n";
                    tableExperiment(200, 300,
                                    20, 30,
                                    200, 300);
                    cout << endl;
                    cout << "\nМатрица с близкими значений диагоналей\n\n";
                    tableExperiment(20, 30,
                                    22, 33,
                                    19, 29);
                    cout << endl;
                    break;
                }
            }


        }
    } while (choice != 0);

}
void tableExperiment(int q, int w, int e, int r, int x, int y){
    cout<< setw(33) << left  << "Размер системы" << "| Погрешность метода прогонки";
    for (int i = 4; i <= 4096;) {
        cout << "\n-------------------------------------------------\n";

        Matr_class curM(i);
        curM.GenerateMatrixExtra(q, w, e, r, x, y);

        vector_class xExact = vector_class(curM.size);
        xExact.GenerateVec(0,100);
        curM.d = curM.MultiplyMatrVec(xExact);
        vector_class sol =  SweepMethod(curM);

        cout << setw(20) << left << i <<  setw(10) << left << '|';
        Error(xExact, sol);
        i *= 4;
    }
    cout << endl;
}

vector_class SweepMethod(Matr_class &matrix) { // метод прогонки
    vector_class solution = vector_class(matrix.size);
    const int size = matrix.size+1;
    // прямой ход -- считаем векторы M и L
    vector_class L = vector_class(size);
    vector_class M = vector_class(size);
// теперь по реккурентным формулам рассчитаем остальные коэффициенты
    for (int i = 1; i < size; ++i) {

        if ((matrix.b.vec[i] - matrix.a.vec[i] * L.vec[i]) != 0)
        {
            L.vec[i+1] = matrix.c.vec[i] / (matrix.b.vec[i] - matrix.a.vec[i] * L.vec[i]);
            M.vec[i+1] = (matrix.d.vec[i] - matrix.a.vec[i] * M.vec[i]) /
                         (matrix.b.vec[i] - matrix.a.vec[i] * L.vec[i]);

        }
    }

    L.vec[size] = 0;
    M.vec[size+1] = (matrix.d.vec[1] - matrix.a.vec[size-1] * M.vec[size-1]) /
                  (matrix.b.vec[size-1] - matrix.a.vec[size-1] * L.vec[size-1]);

    cout << "Вспомогательные векторы:\n";
    cout << "Вектор L   :";
    L.OutInConsole();
    cout << "\nВектор M   :";
    M.OutInConsole();

    //обратный ход -- считаем вектор-решение
    solution.vec[size - 1] = M.vec[size];
    for (int i = size - 1; i >= 1; --i) {
        solution.vec[i] = M.vec[i+1] - L.vec[i+1] * solution.vec[i+1];
    }
    return solution;
}

void ComputationalExperiment(Matr_class &matrix, vector_class xExactS) {
    // мы получаем также матрицу, но здесь нам известно точное решение x,
    // по нему мы должны посчитать вектор d, и потом соответственно вызвать прогонку как обычно
    // то есть по факту два решения и мы должны их сравнить
    cout << "Данная матрица: \n";
    matrix.OutputToConsole();
    cout << endl;
    matrix.d = matrix.MultiplyMatrVec(xExactS);
    vector_class sol =  SweepMethod(matrix);
    cout << endl;



    cout << endl;
    cout << "Результаты вычислительного эксперимента  \n";
    //cout << endl;
    cout << "Точное решение: ";
    xExactS.OutInConsole();
    cout << endl;
    cout << endl;
    cout << "Результат метода прогонки: ";
    sol.OutInConsole();
    cout << endl;
    cout << "Погрешность: ";
    Error(xExactS, sol);
    cout << endl;


}

void Solution(Matr_class &matrix) {
    cout << "\nВыберите действие\n";
    cout << "[1] Найти решение\n";
    cout << "[2] Вычислительный эксперимент -- генерирование точного вектора-решения\n";
    //cout << "[3] Сравнение\n";
    cout << "[0] Выйти\n";
    cout << "-> ";
    int typeChoice = SpellCheck(0, 2);
    switch (typeChoice){
        case 1:{
            cout << "Введите границы диапазона для генерирования вектора d: ";
            int n, m;
            cin >> n >> m;
            matrix.d.GenerateVec(n,m);

            cout << "Результат метода прогонки: ";
            vector_class sol = SweepMethod(matrix);
            sol.OutInConsole();
            break;
        }
        case 2:{
            cout << "Введите границы диапазона для генерирования вектора-решения: ";
            int n, m;
            cin >> n >> m;
            vector_class xExact = vector_class(matrix.size);
            xExact.GenerateVec(n,m);
            ComputationalExperiment(matrix, xExact);
            break;
        }
        default:
            typeChoice = 0;
    }

}

void Error(vector_class& exact, vector_class& countedSol) { // считаем погрешность
    vector_class error = exact.Minus(countedSol);
    cout << error.VecNorm();
}

