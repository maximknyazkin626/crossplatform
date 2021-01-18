#pragma once
#include <iostream>
#include "utils.h"
#include <fstream>
#include <cmath>

class Pipe
{
	float Length;
	float Diameter;
	bool IsRepairing;

public:
	static int pMaxId;
	int outCsId;
	int inCsId;
	friend std::ostream& operator << (std::ostream& out, const Pipe& p);
	friend std::istream& operator >> (std::istream& in, Pipe& p);
	Pipe();
	Pipe(std::ifstream& fin);
	int GetProductivity() const;
	bool GetRepairing() const;
	float GetLength() const;
	void Edit();
	void SaveToFile(std::ofstream& fout);
	void Repair();
};
