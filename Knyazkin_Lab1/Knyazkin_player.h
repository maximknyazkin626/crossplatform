#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
class Knyazkin_player
{
private:
	string firstName;
	string lastName;
	int age;
	string country;
public:


	void readFromConsole();
	void writeToConsole();
	void readFromFile(ifstream& in);
	void writeToFile(ofstream& out);

	
};

