// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool check_value(int x) {
    return x > 0 ? true : false;
}
bool check_value(double x) {
    return x > 0 ? true : false;
}

struct pipe { //создаем структуру трубы
    int id;   // id
    double dlina;  // длина
    double diametr; // диаметр 
    bool repair;  // статус в ремонте 
};

struct ks { // создаем структуру кс
    int id; // id
    string name;  // имя 
    int ceh; // кол-во цехов
    int ceh_inwork; // кол-во цехов в работе
    double effect; // эффективность
};

pipe InputPipe () // создаем трубу
{
    pipe p; // переменная отвечающая за новую трубу
    cout << "Введите диаметр: "; 
    cin >> p.diametr;  // ввод диаметра
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введите длину: " ;  // ввод длины 
    cin >> p.dlina;
    p.repair = false; // статус в ремонте
    p.id = 0;  // id

    return p;
}

ks InputKs() // создаем кс
{
    ks new_ks; // переменная отвечающая за новую кс
    cout << "Введите имя: " << endl;
    cin >> new_ks.name; // ввод имени
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введите кол-во цехов: " << endl; 
    cin >> new_ks.ceh; // ввод кол-ва цехов
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введите кол-во рабочих цехов: " << endl; // ввод кол-ва рабочих цехов
    cin >> new_ks.ceh_inwork;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "Введите эффективность: " << endl;
    cin >>new_ks.effect;
    new_ks.id = 0;

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


void change_status(bool& status) {
    status = !status;
}

void save_to_filepi(pipe pi) {
    ofstream fout;
    fout.open("DataTruba.txt", ios::out);
    if (fout.is_open()) {
        fout << pi.id << endl << pi.diametr << endl << pi.dlina << endl << pi.repair;
        fout.close();
    }
}

void save_to_fileKS(ks kompresor) {
    ofstream fout;
    fout.open("DataCS.txt", ios::out);
    if (fout.is_open()) {
        fout << kompresor.id << endl << kompresor.name << endl << kompresor.ceh << endl << kompresor.ceh_inwork << endl << kompresor.effect;
        fout.close();
    }
}

void PrintMenu() {
    cout << "1. Создать трубу" << endl;
    cout << "2. Создать компрессорную станцию" << endl;
}



int main()
{
    setlocale(LC_ALL, "Russian");
   // string s;
    ///cout << "Type your name,please" << endl;
    //cin >> s;
    //cout << "Hello  " << s << endl;

    pipe pi = InputPipe();
    PrintPipe(pi);
    ks kompresor = InputKs();
    PrintKs(kompresor);
    int i;
    while (1) {
        cout << "Выберите действие:" << endl;
        PrintMenu();
        cin >> i;
        switch (i)
        {
        case 1:
            pi = InputPipe();
            break;
        case 2:
            kompresor = InputKs();
            break;

        }
    }
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

