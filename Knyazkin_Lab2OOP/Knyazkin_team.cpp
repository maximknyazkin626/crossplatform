#include "pch.h"
#include "Knyazkin_player.h"
#include "Knyazkin_team.h"
#include <vector>
void Knyazkin_team::AddPlayer(shared_ptr<Knyazkin_player> player)
{
	Team.push_back(player);
}

void Knyazkin_team::PrintPlayers()
{
	if (Team.empty())
	{
		cout << "Team is empty." << endl;
		return;
	}
	else
	{
		for (auto sptr : Team)
		{
			sptr->PrintPlayers();
		}
	}

}


void Knyazkin_team::WritePlayersToFile()
{
	string filename;
	CString name_of_file;
	cout << "Enter the name of file: ";
	cin.ignore();
	getline(cin, filename);
	name_of_file = filename.c_str();
	CFile f(name_of_file, CFile::modeCreate | CFile::modeWrite); // Режимы открытия: создание и запись
	CArchive ar(&f, CArchive::store); // Режим работы: сохранение
	ar << Team.size();
	for (auto& st : Team) {
		ar << st.get();
	}
	//Team.clear();
}

void Knyazkin_team::ReadPlayersFromFile()
{
	string filename;
	CString name_of_file;
	cout << "Enter the name of file: ";
	cin.ignore();
	getline(cin, filename);
	name_of_file = filename.c_str();
	CFile f(name_of_file, CFile::modeRead);
	CArchive ar(&f, CArchive::load);
	int n;
	ar >> n;
	for (int i = 0; i < n; ++i)
	{
		Knyazkin_player* p;
		ar >> p;
		shared_ptr<Knyazkin_player> strp(p);
		Team.push_back(strp);
	}
}

void Knyazkin_team::DeletePlayers()
{
	Team.clear();
}