#pragma once
#include <vector>
#include "Knyazkin_player.h"
class Knyazkin_team
{
private:
	vector <Knyazkin_player*> vec;


public:
	void add(Knyazkin_player* ptr);
	void writeToConsole();
	void readFromFile(string filename);
	void writeToFile(string filename);
	void clear();
};

