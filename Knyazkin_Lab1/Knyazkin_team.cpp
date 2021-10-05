#include "Knyazkin_team.h"

void Knyazkin_team::add(Knyazkin_player* ptr)
{
	vec.push_back(ptr);
}

void Knyazkin_team::writeToConsole()
{
	for (Knyazkin_player* ptr : vec) {
		ptr->writeToConsole();
	}
}

void Knyazkin_team::readFromFile(string filename)
{
	ifstream in;
	in.open(filename, ios::in);
	int count;
	in >> count;
	for (int i = 0; i < count; i++)
	{
		Knyazkin_player* curPlayer = new Knyazkin_player(); // ”казатель
		curPlayer->readFromFile(in);
		this->add(curPlayer);
	}

	in.close();
}

void Knyazkin_team::writeToFile(string filename)
{
	ofstream out;
	out.open(filename, ios::out);
	out << this->vec.size() << endl;
	for (auto ptr : this->vec) {
		ptr->writeToFile(out);
	}
	out.close();
}

void Knyazkin_team::clear()
{
	for (auto ptr : this->vec) {
		delete ptr;
	}
	this->vec.clear();
}