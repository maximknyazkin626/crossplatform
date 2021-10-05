#include <iostream>
#include "Knyazkin_player.h"
#include "Knyazkin_team.h"
#include <fstream>
using namespace std;

void printMenu() {
	cout << "1. Add element." << endl;
	cout << "2. Show list. " << endl;
	cout << "3. Read from file." << endl;
	cout << "4. Write to file." << endl;
	cout << "5. Clear list." << endl;
	cout << "6. Exit" << endl;
}

int main()
{
	int choice;
	Knyazkin_team team;
	while (true) {
		printMenu();
		cin >> choice;
		switch (choice) /// 
		{
		case 1:
		{
			Knyazkin_player* pl = new Knyazkin_player();
			pl->readFromConsole();
			team.add(pl);
		}
		break;
		case 2:
			team.writeToConsole();
			break;
		case 3:
			team.readFromFile("test.txt");
			break;
		case 4:
			team.writeToFile("test.txt");
			break;
		case 5:
			team.clear();
			break;
		case 6:
			return 0;
		default:
			break;
		}
	}
}


