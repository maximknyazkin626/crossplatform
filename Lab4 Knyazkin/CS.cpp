#include "CS.h"

int CS::csMaxId = 0;
std::string Name;
int ShopsCount;
int WorkingShopsCount;
float Efficiency;


CS::CS(std::ifstream& fin)
{
	fin.ignore();
	std::getline(fin, Name);
	fin >> ShopsCount
		>> WorkingShopsCount
		>> Efficiency;
}

std::string CS::GetName() const
{
	return Name;
}

float CS::GetPercentUnusedShops() const
{
	return (1 - (WorkingShopsCount * 1.0f / ShopsCount)) * 100;
}

void CS::RecountShopsCount()
{
	std::cout << "������ � �� ���� " << ShopsCount << " �����.\n";
	std::cout << "1 - ��������� ���������� �����\n"
		<< "2 - ��������� ���������� �����\n"
		<< "0 � ��. - ������\n";
	int input;
	CheckValue(input, "�������: ");
	switch (input)
	{
	case 1:
		ShopsCount++;
		std::cout << "���������� ����� ������� ��������� �� " << ShopsCount << "\n";
		break;
	case 2:
		ShopsCount--;
		if (WorkingShopsCount > ShopsCount)
			WorkingShopsCount = ShopsCount;
		std::cout << "���������� ����� ������� ��������� �� " << ShopsCount << "\n";
	default:
		std::cout << "�� ����� �� ������ ��������������.";
		break;
	}
}

void CS::RecountWorkingShopsCount()
{
	std::cout << "������ � �� �������� " << WorkingShopsCount << "/" << ShopsCount << " �����\n";
	int workingShopsCount;
	CheckValue(workingShopsCount, "������� ����� ���������� ���������� �����: ");
	while (workingShopsCount > ShopsCount)
	{
		std::cout << "������! ���������� ���������� ����� �� ����� ���� ������ ������ ���������� �����\n";
		CheckValue(workingShopsCount, "������� ����� ���������� ���������� �����: ");
	}
	WorkingShopsCount = workingShopsCount;
}

void CS::SaveToFile(std::ofstream& fout)
{
	fout << Name << '\n'
		<< ShopsCount << '\n'
		<< WorkingShopsCount << '\n'
		<< Efficiency << '\n';
}

std::ostream& operator << (std::ostream& out, const CS& cs)
{
	std::cout << " ���: " << cs.Name << "\n"
		<< " �������� " << cs.WorkingShopsCount << "/" << cs.ShopsCount << " �����" "\n"
		<< " �������������: " << cs.Efficiency << "\n";
	return out;
}

std::istream& operator>>(std::istream& in, CS& cs)
{
	std::cout << "������� ��� ������������� �������: ";
	std::cin.ignore();
	std::getline(std::cin, cs.Name);
	CheckValue(cs.ShopsCount, "������� ����� ���-�� �����: ");
	CheckValue(cs.WorkingShopsCount, "������� ���-�� ���������� �����: ");
	while (cs.WorkingShopsCount > cs.ShopsCount) {
		std::cout << "������! ���-�� ���������� ����� �� ����� ���� ������ ������ ���-�� �����\n";
		CheckValue(cs.WorkingShopsCount, "����������, ������� ���������� ���-�� ���������� �����: ");
	}
	CheckValue(cs.Efficiency, "������� ������������ ������������� �������: ");
	return in;
}

CS::CS()
{
}