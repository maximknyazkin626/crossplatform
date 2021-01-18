#pragma once
#include <iostream>

template <typename T>
void CheckValue(T& input, std::string inputText)
{
	std::cout << inputText;
	while ((std::cin >> input).fail() || input < 0) {
		std::cout << "������� ������ ��������\n";
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}
}