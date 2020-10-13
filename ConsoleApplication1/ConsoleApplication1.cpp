// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

bool check_value(int x) {
    return x > 0 ? true : false;
}
bool check_value(double x) {
    return x > 0 ? true : false;
}
struct pipe {
    string id;
    double dlina;
    double diametr;
    bool remont;
};

struct ks {
    string id;
    string name;
    int ceh;
    int ceh_inwork;
    double effect;
};

pipe InputPipe ()
{
    pipe p;
    cout << "Введите диаметр: ";
    cin >> p.diametr;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введит длину: " ;
    cin >> p.dlina;
    p.remont = false;
    p.id = -1;


    return p;
}

ks InputKs()
{
    ks new_ks;
    cout << "Введите имя: " << endl;
    cin >> new_ks.name;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введите кол-во цехов: " << endl;
    cin >> new_ks.ceh;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введите кол-во рабочих цехов: " << endl;
    cin >> new_ks.ceh_inwork;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введите эффективность: " << endl;
    cin >> new_ks.effect;
    new_ks.id = -1;

    

    return new_ks;
}


void PrintPipe(pipe p)
{
    cout << "Диаметр: " << p.diametr << endl;
    cout << "Длина: " << p.dlina << endl;
}

void PrintKs(ks new_ks)
{
    cout << "Имя:" << new_ks.name << endl;
    cout << "Кол-во цехов: " << new_ks.ceh << endl;
    cout << "Кол-во рабочих цехов: " << new_ks.ceh_inwork << endl;
    cout << "Эффективность: " << new_ks.effect << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    string s;
    ///cout << "Type your name,please" << endl;
    //cin >> s;
    //cout << "Hello  " << s << endl;

    pipe pi = InputPipe();
    PrintPipe(pi);
    ks kompresor = InputKs();
    PrintKs(kompresor);

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

