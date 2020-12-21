// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Truba.h"
#include "CS.h"
#include "utils.h"
using namespace std;



void save_to_file(const unordered_map<int, Truba>& t, const unordered_map<int, CS>& c) {
	ofstream fout;
	string filename;
	cout << "Введите название файла: " << std::endl;
	cin.ignore(256, '\n');
	getline(cin, filename, '\n');
	fout.open(filename, ios::out);
	if (fout.is_open()) {
		fout << t.size() << endl << c.size() << endl;
		for (const auto& it : t)
		{
			fout << it.second;
		}
		for (const auto& it : c)
		{
			fout << it.second;
		}
		fout.close();
	}
}

void load_from_file(unordered_map <int, Truba>& t, unordered_map <int, CS>& c) {
	ifstream fin;
	int countT, countC;
	string filename;
	cout << "Введите название файла: " << std::endl;
	cin.ignore(256, '\n');
	getline(cin, filename, '\n');
	fin.open(filename, ios::in);
	if (fin.is_open()) {
		fin >> countT >> countC;
		t.reserve(countT);
		c.reserve(countC);
		for (int i = 0; i < countT; i++)
		{
			Truba LoadedTruba;
			fin >> LoadedTruba;
			t.insert({ LoadedTruba.Getid(),LoadedTruba });
		}
		for (int i = 0; i < countC; i++)
		{
			CS LoadedCS;
			fin >> LoadedCS;
			c.insert({ LoadedCS.Getid(), LoadedCS });
		}
		fin.close();
	}
}




template<typename T>
bool del(unordered_map<int, T>& map, int id) {
	return map.erase(id);
}

template<typename T>
using FilterT = bool(*)(const Truba& t, T param);

bool CheckByName(const Truba& t, string param) {
	return t.GetName() == param;
}
bool CheckByStatus(const Truba& t, bool param) {
	return t.GetStatus() == param;
}

template <typename T>
vector<int> FindTrubaByFilter(const unordered_map<int, Truba>& map, FilterT<T> f, T param)
{
	vector<int> res;
	for (const auto& it : map) {
		if (f(it.second, param)) {
			res.push_back(it.first);
		}
	}
	return res;
}

template<typename T>
using FilterC = bool(*)(const CS& c, T param);

bool CheckByName(const CS& c, string param) {
	return c.GetName() == param;
}
bool CheckByPercent(const CS& c, double param) {
	return (100.0 * (c.GetWork() - c.GetInWork()) / c.GetWork() >= param);
}

template <typename T>
vector<int> FindCSByFilter(const unordered_map<int, CS>& map, FilterC<T> f, T param) {
	vector<int> res;
	for (const auto& it : map) {
		if (f(it.second, param)) {
			res.push_back(it.first);
		}
	}
	return res;
}


void PacketRedactTrub(unordered_map<int, Truba>& map) {
	cout << "\tВыберите какие трубы редактировать: " << endl;
	cout << "\t1. По статусу в ремонте" << endl;
	cout << "\t2. По статусу не в ремонте" << endl;
	cout << "\t3. По выбору пользователя" << endl;
	cout << "\t0. Назад" << endl;
	switch (get_value(0, 3))
	{
	case 1:
	{
		for (int i : FindTrubaByFilter(map, CheckByStatus, true))
			map.find(i)->second.change_status();
		break;
	}
	case 2:
	{
		for (int i : FindTrubaByFilter(map, CheckByStatus, false))
			map.find(i)->second.change_status();
		break;
	}
	case 3: {
		vector<int> vec;
		while (1) {
			cout << "Введите id" << endl;
			vec.push_back(get_value(0, Truba::GetMaxid()));
			cout << "Добавить?" << endl << "\t 0. Нет" << endl << "\t 1. Да" << endl;
			if (get_value(0, 1) == 0)
				break;
		}
		for (auto i : vec) {
			if (map.find(i) != map.end())
				map.find(i)->second.change_status();
		}
		break;
	}
	case 0: {
		return;
	}
	}
}



void PrintMenu() {
	cout << "1. Создать трубу" << endl
		<< "2. Создать компрессорную станцию" << endl
		<< "3. Сохранить в файл" << endl
		<< "4. Загрузить из файла" << endl
		<< "5. Вывести информацию" << endl
		<< "6. Изменить статус трубы" << endl
		<< "7. Изменить компрессорную станцию" << endl
		<< "8. Множественное редактирование труб" << endl
		<< "9. Удалить трубу" << endl
		<< "10. Удалить компрессорную станцию" << endl
		<< "11. Поиск трубы по имени" << endl
		<< "12. Поиск трубы по статусу" << endl
		<< "13. Поиск компрессорной станции по имени" << endl
		<< "14. Поиск компрессорной станции по проценту рабочих цехов" << endl
		<< endl
		<< "0. Выход" << endl;
}




int main()
{
	setlocale(LC_ALL, "Russian");

	unordered_map <int, Truba> Trubas;
	unordered_map <int, CS> CSs;

	while (1)
	{
		cout << "Выберите действие:" << endl;
		PrintMenu();
		switch (get_value(0, 14))
		{

		case 1:
		{
			while (1)
			{
				Truba t;
				cin >> t;
				Trubas.insert({ t.Getid(), t });
				cout << "Добавить?" << endl << "\t 0. Нет" << endl << "\t 1. Да" << endl;
				if (get_value(0, 1) == 0)
					break;
			}
			break;
		}

		case 2:
		{
			while (1)
			{
				CS c;
				cin >> c;
				CSs.insert({ c.Getid(), c });
				cout << "Добавить?" << endl << "\t 0. Нет" << endl << "\t 1. Да" << endl;
				if (get_value(0, 1) == 0)
					break;
			}
			break;
		}

		case 3:
		{
			save_to_file(Trubas, CSs);
			break;
		}

		case 4:
		{
			load_from_file(Trubas, CSs);
			break;
			break;
		}

		case 5:
		{
			for (const auto& it : Trubas) {
				cout << it.second;
			}
			for (const auto& it : CSs) {
				cout << it.second;
			}
			break;
			break;
		}

		case 6:
		{
			cout << "id Трубы: " << endl;
			unordered_map<int, Truba>::iterator iter = Trubas.find(get_value(0, Truba::GetMaxid()));
			if (iter == Trubas.end())
				cout << "Труба не найдена!" << endl;
			else
				iter->second.change_status();
			break;
		}

		case 7:
		{
			cout << "id компрессорной станици: " << endl;
			unordered_map<int, CS>::iterator iter = CSs.find(get_value(0, CS::GetMaxid()));
			if (iter == CSs.end()) {
				cout << "Компрессорная станция не найдена!" << endl;
			}
			else {
				cout << "\t Выберите действие:" << endl;
				cout << "\t 1. Начать работы" << endl;
				cout << "\t 2. Прекратить работу" << endl;
				switch (get_value(1, 2))
				{
				case 1:
					iter->second.continue_work();
					break;
				case 2:
					iter->second.stop_work();
					break;
				default:
					cout << "Выберите существующее действие!" << endl;
					break;
				}
			}
			break;
		}

		case 8:
		{
			PacketRedactTrub(Trubas);
			break;
		}

		case 9:
		{
			while (1)
			{
				cout << "Ввдеите id " << endl;
				if (del(Trubas, get_value(0, Truba::GetMaxid())))
					cout << "Труба удалена" << endl;
				else
					cout << "Труба не удалена" << endl;
				cout << "Удалить?" << endl << "\t 0. Нет" << endl << "\t 1. Да" << endl;
				if (get_value(0, 1) == 0)
					break;
			}
			break;
		}

		case 10:
		{
			while (1)
			{
				cout << "Введите id " << endl;
				if (del(CSs, get_value(0, CS::GetMaxid())))
					cout << "Компрессорная станция удалена" << endl;
				else
					cout << "Компрессорная станция не удалена" << endl;
				cout << "Удалить?" << endl << "\t 0. Нет" << endl << "\t 1. Да" << endl;
				if (get_value(0, 1) == 0)
					break;
			}
			break;
		}

		case 11:
		{
			cout << "Введите имя трубы: " << endl;
			string name;
			cin.ignore(256, '\n');
			getline(cin, name, '\n');
			for (int i : FindTrubaByFilter<string>(Trubas, CheckByName, name)) {
				cout << Trubas.find(i)->second << endl;
			}
			break;
		}

		case 12:
		{
			for (int i : FindTrubaByFilter(Trubas, CheckByStatus, true)) 	cout << Trubas.find(i)->second << endl;

			break;
		}

		case 13:
		{
			cout << "Введите имя " << endl;
			string name;
			cin.ignore(256, '\n');
			getline(cin, name, '\n');
			for (int i : FindCSByFilter<string>(CSs, CheckByName, name))    cout << CSs.find(i)->second << endl;

			break;
		}

		case 14:
		{
			cout << "Введите процент нерабочих цехов  " << endl;
			for (int i : FindCSByFilter(CSs, CheckByPercent, get_value(0.0, 100.0))) 	cout << CSs.find(i)->second << endl;

			break;
		}
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

