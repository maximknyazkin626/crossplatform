#include "pch.h"
#include "Knyazkin_coach.h"
#include "Knyazkin_utils.h"
IMPLEMENT_SERIAL(Knyazkin_coach, Knyazkin_player, VERSIONABLE_SCHEMA | 0)


void Knyazkin_coach::ReadPlayers()
{
	cout << "Type the FirstName: ";
	cin >> FirstName;
	cout << "Type the LastName: ";
	cin >> LastName;
	cout << "Type the Age: ";
	cin >> Age;
	cout << "Type the Country: ";
	cin >> Country;
	cout << "Type the Experience: ";
	cin >> experience;
	cout << "Type the Former Team: ";
	cin >> former_team;
}

void Knyazkin_coach::PrintPlayers()
{
	cout << "FirstName " << FirstName << endl;
	cout << " Last Name" << LastName << endl;
	cout << " Age " << Age << endl;
	cout << " Country " << Country << endl;
	cout << " Experience " << experience << endl;
	cout << " Former Team " << former_team << endl;
	cout << "++++++++++++++++++++++++++" << endl;
}

Knyazkin_coach::Knyazkin_coach()
{
	//cout << "constr coach" <<endl;
}

Knyazkin_coach::~Knyazkin_coach()
{
	//cout << "deconstr coach" << endl;
}

void Knyazkin_coach::Serialize(CArchive& ar)
{
	Knyazkin_player::Serialize(ar);
	if (ar.IsStoring()) {
		ar << experience;
		ar << former_team;
	}
	else {
		ar >> experience;
		ar >> former_team;
		if (ar.GetObjectSchema() > 0) {}
	}
}