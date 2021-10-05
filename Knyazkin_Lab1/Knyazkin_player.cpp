#include "Knyazkin_player.h"
#pragma once
#include <fstream>


void Knyazkin_player::readFromConsole()
{
	cout << "Enter a firstname " << endl;
	cin >> this->firstName;
	cout << "Enter a lastname " << endl;
	cin >> this->lastName;
	cout << "Enter an age " << endl;
	cin >> this->age;
	cout << "Enter a country" << endl;
	cin >> this->country;
}

void Knyazkin_player::writeToConsole() // 
{
	cout << "firstname: " << this->firstName <<" |"<< " lastname: " << this->lastName << " |"  << " age: " << this->age << " |"  << " country: " << this->country << endl;
}

void Knyazkin_player::readFromFile(ifstream& in) 
{
	in >> this->firstName >> this->lastName >> this->age >> this->country; // 
}

void Knyazkin_player::writeToFile(ofstream& out)
{
	out << this->firstName << endl << this->lastName << endl << this->age << endl << this->country << endl;
}