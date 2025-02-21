#pragma once

#include <iostream>
#include "polynoms.h"
#include <string>



int main() {
	//Polynom<int>pol("xyz - xyz");
	setlocale(LC_ALL, "Russian");
	std::cout << "������� ������� � ������� k * x^a * y^b * z^c + ..., ��� a,b,c - ����� �� 0 �� 9\n";
	std::cout << "��������� ������� ����� ����������, \n� ���� ������� ����� ����, �� ����������� ����� �� ������.\n������������ ����� ����� ������ ����� �������\n";
	std::cout << "������� ������ �������:\n";
	std::string st;
	std::getline(std::cin, st);
	Polynom<double> pol1(st);
	pol1.display();
	std::cout << "������� ������ �������:\n";
	std::getline(std::cin, st);
	Polynom<double> pol2(st);
	pol2.display();
	std::cout << "�������� � ����������: \n";
	while (1) {
		std::cout << "0 - �����, 1 - �������, 2 - ������� ������ �� �������, 3 - ������� ������ �� �������, 4 - ��������� ������ ������� �� ���������, 5 - ��������� ������ ������� �� ���������, 6 - �����������\n";
		int inp;
		std::cin >> inp;
		Polynom<double> pol3;
		do {
			if (inp == 0)
				break;
			else if (inp == 1) {
				pol3 = pol1 + pol2;
				pol3.display();
			}
			else if (inp == 2) {
				pol3 = pol1 - pol2;
				pol3.display();
			}
			else if (inp == 3) {
				pol3 = pol2 - pol1;
				pol3.display();
			}
			else if (inp == 4) {
				std::cout << "������� ���������:\n";
				double cnst;
				std::cin >> cnst;
				pol3 = pol1 * cnst;
				pol3.display();
			}
			else if (inp == 5) {
				std::cout << "������� ���������:\n";
				int cnst;
				std::cin >> cnst;
				pol3 = pol2 * cnst;
				pol3.display();
			}
			else if (inp == 6) {
				pol3 = pol1 * pol2;
				pol3.display();
			}
			else
				std::cout << "������������ ����\n";
		} while (!(inp >= 0 && inp <= 6));
		do {
			std::cout << "��������� ���:\n0 - �� ���������, 1 - ������� 1, 2 - ������� 2\n";
			std::cin >> inp;
			if (inp == 0) {}
			else if (inp == 1)
				pol1 = pol3;
			else if (inp == 2)
				pol2 = pol3;
			else
				std::cout << "������������ ����\n";
		} while (!(inp >= 0 && inp <= 2));
	}
}