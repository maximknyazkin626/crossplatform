#include "pch.h"
#include "Knyazkin_player.h"
#include "Knyazkin_utils.h"

IMPLEMENT_SERIAL(Knyazkin_player, CObject, VERSIONABLE_SCHEMA | 0) ///CObject ближайший предок


void Knyazkin_player::ReadPlayers()
{
	cout << "Type the FirstName: ";
	cin >> FirstName;
	cout << "Type the LastName: ";
	cin >> LastName;
	cout << "Type the Age: ";
	cin >> Age;
	cout << "Type the Country: ";
	cin >> Country;
	
}

Knyazkin_player::Knyazkin_player()
{
	//cout<< "constr player" << endl;
}

Knyazkin_player::~Knyazkin_player()
{
	//cout << "destr player" << endl;
}

void Knyazkin_player::PrintPlayers()
{
	cout << "FirstName " << FirstName << endl;
	cout << " Last Name" << LastName << endl;
	cout << " Age " << Age << endl;
	cout << " Country " << Country << endl;
	cout << "++++++++++++++++++++++++++" << endl;
}

void Knyazkin_player::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar << FirstName << LastName << Age << Country ;
	}
	else
	{
		ar >> FirstName >> LastName >> Age >> Country ;
		if (ar.GetObjectSchema() > 0) {}
	}

}