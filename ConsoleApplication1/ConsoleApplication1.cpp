// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct pipe { //создаем структуру трубы
    int id = 0;   // id
    double dlina = 0;  // длина
    double diametr = 0; // диаметр 
    bool repair = false;  // статус в ремонте 
};

struct ks { // создаем структуру кс
    int id = 0; // id
    string name = "" ;  // имя 
    int ceh = 0; // кол-во цехов
    int ceh_inwork = 0; // кол-во цехов в работе
    double effect = 0; // эффективность
};

template <typename T>  /// проверка вводимых данных
T GetCorrectNumber(T min, T max)
{
    T x;
    cin >> x;
    while (cin.fail() || x<min || x>max)
    {
        cin.clear();
        cin.ignore(1000000, '\n');
        cin >> x;
    }
    return x;
} 

pipe InputPipe () // создаем трубу
{
    pipe p; // переменная отвечающая за новую трубу
    ///bool IsPipe = true;
    cout << "Введите диаметр: "; 
    p.diametr = GetCorrectNumber(0, 100000);  // ввод диаметра
    cin.clear();
    cout << "Введите длину: " ;  // ввод длины 
    p.dlina= GetCorrectNumber(0,100000);
    p.repair = false; // статус в ремонте
    p.id = 0;  // id

    return p;
}


ks InputKs() // создаем кс
{
    ks new_ks; // переменная отвечающая за новую кс
   // bool IsKs = true;
    cout << "Введите имя: " << endl;
    cin >> new_ks.name ; // ввод имени
    cin.clear();
    cout << "Введите кол-во цехов: " << endl; 
    new_ks.ceh = GetCorrectNumber(0, 10000); // ввод кол-ва цехов
    cin.clear();
    cout << "Введите кол-во рабочих цехов: " << endl; // ввод кол-ва рабочих цехов
     new_ks.ceh_inwork = GetCorrectNumber(0, 10000);;
    cin.clear();
    cout << "Введите эффективность: " << endl;
    new_ks.effect = GetCorrectNumber(0, 10000);
    new_ks.id = 0;

    return new_ks;
}


void PrintPipe( pipe p) // вывод информации о трубе в консоль
{
    cout << "Диаметр: " << p.diametr << endl; 
    cout << "Длина: " << p.dlina << endl; 
    cout << "id: " << p.id << endl;
    cout << (p.repair ? "В ремонте" : "Не в ремонте") << endl;
}

void PrintKs(ks new_ks) // вывод информации о кс в консоль
{
    cout << "Имя:" << new_ks.name << endl;
    cout << "Кол-во цехов: " << new_ks.ceh << endl;
    cout << "Кол-во рабочих цехов: " << new_ks.ceh_inwork << endl;
    cout << "Эффективность: " << new_ks.effect << endl;
}

void change_status(bool& status) {
    status = !status;
}

void stop_work(ks& new_ks)
{
    if (new_ks.ceh_inwork > 0) {
        new_ks.ceh_inwork--;
    }
    else {
        cout << "Число работающих цехов: 0" << endl;
    }
   //new_ks.ceh_inwork--;
}

void start_work(ks& new_ks)
{
    if (new_ks.ceh_inwork < new_ks.ceh)
    {
        new_ks.ceh_inwork++;
    }
    else
    {
        cout << "Все цеха работают" << endl;
    }
   // new_ks.ceh_inwork++;
}

void SaveFile(const pipe& p, const ks& new_ks) // сохранение информации о трубе и кс в файл
{
    ofstream fout;
    fout.open("Data.txt", ios::out);
    if (fout.is_open()) 
    {
        fout << p.id << endl << p.diametr << endl << p.dlina << endl << p.repair;
        fout << new_ks.id << endl << new_ks.name << endl << new_ks.ceh << endl << new_ks.ceh_inwork << endl << new_ks.effect;
        fout.close();
    }
}

////void SaveKs(ks& new_ks) // сохранение информации о кс в файл
///{
   //// ofstream fout;
   /// fout.open("DataCS.txt", ios::out);
   // if (fout.is_open()) 
   // {
        
   ///     fout.close();
   // }
////}

pipe ReadFilePipe(ifstream& fin) //чтение информации о трубе из файла
{
    pipe p;
    fin >> p.id;
    fin >> p.diametr;
    fin >> p.dlina;
    fin >> p.repair;
    return p;
}

ks ReadFileKs(ifstream& fin) //чтение информаци о кс из файла
{
    ks new_ks;
    fin >> new_ks.id;
    fin >> new_ks.name;
    fin >> new_ks.ceh;
    fin >> new_ks.ceh_inwork;
    fin >> new_ks.effect;
    return new_ks;
}

void ReadFromFilePKs(pipe& p, ks& new_ks) ///загрузка информации из файла
{
    ifstream fin;
    fin.open("Data.txt", ios::in);
    if (fin.is_open()) {
        p = ReadFilePipe (fin);
        new_ks = ReadFileKs(fin);
        fin.close();
    }
}

void Menu() {  ///создание меню
    cout << "1. Создать Трубу" << endl;
    cout << "2. Создать компрессорную станцию " << endl;
    cout << "3. Вывести информацию" << endl;
    cout << "4. Изменить состояние трубы" << endl;
    cout << "5. Загрузить из файла " << endl;
    cout << "6. Сохранить в файл" << endl;
    cout << "7. Обновить компрессорную станцию" << endl;
    cout << "0. Выход" << endl;
}




int main()
{
    setlocale(LC_ALL, "Russian");
   // string s;
    ///cout << "Type your name,please" << endl;
    //cin >> s;
    //cout << "Hello  " << s << endl;

    //pipe pi = InputPipe();
    //PrintPipe(pi);
    //ks kompresor = InputKs();
    //PrintKs(kompresor);
    pipe p;
    ks new_ks; 
    int i;
    bool InPipe = false;
    bool IsKs = false;
    while (1) {
        cout << "Выберите действие:" << endl;
        Menu();
        cin >> i;
        switch (i)
        {
        case 1:
            p = InputPipe();
            /// p = ReadFilePipe ();  
            /// new_ks = ReadFileKs (); 
            break;
        case 2:
            new_ks = InputKs();
            break;
        case 3:
            //if (InPipe == true)
           // {
                PrintPipe(p);
           // }
           // else
           // {
           //     cout << "Трубы не существует" << endl;
           // }
          //  if (IsKs == true)
           // {
                PrintKs(new_ks);
           // }
          //  else
          //  {
          //      cout << "Компрессорной станции не существует" << endl;
           // }
            break;
        case 4:
            if (p.id == 1) {
                change_status(p.repair);
            }
            else {
                cout << "Трубы не существет" << endl;
            }
            break;
        case 5:
            ReadFromFilePKs(p, new_ks);
            break;
        case 6:
            SaveFile(p, new_ks);
            break;
        case 7:
            cout << "\t Выберите действие:" << endl;
            cout << "\t 1. Начало работы" << endl;
            cout << "\t 2. Прекращение работы" << endl;
            cout << "\t 0. Назад" << endl;
            cin >> i;
            switch (i)
            {
            case 1:
                start_work(new_ks);
                break;
            case 2:
                stop_work(new_ks);
                break;
            case 0:
                break;
            default:
                cout << "Выберите действие: " << endl;
                break;
            }
             ////else {
              ///    cout << "Компрессорной станции не существует" << endl;
              // }
             // break;
        case 0:
            return 0;
            break;
        default:
            cout << "Выберите действие: " << endl;
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

