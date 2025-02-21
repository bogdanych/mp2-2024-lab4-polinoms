#pragma once

#include <iostream>
#include "polynoms.h"
#include <string>



int main() {
	//Polynom<int>pol("xyz - xyz");
	setlocale(LC_ALL, "Russian");
	std::cout << "Введите полином в формате k * x^a * y^b * z^c + ..., где a,b,c - цифры от 0 до 9\n";
	std::cout << "Написание единицы можно пропустить, \nа если степень равна нулю, то коэффициент можно не писать.\nВещественную часть числа писать через запятую\n";
	std::cout << "Введите первый полином:\n";
	std::string st;
	std::getline(std::cin, st);
	Polynom<double> pol1(st);
	pol1.display();
	std::cout << "Введите второй полином:\n";
	std::getline(std::cin, st);
	Polynom<double> pol2(st);
	pol2.display();
	std::cout << "Операции с полиномами: \n";
	while (1) {
		std::cout << "0 - выйти, 1 - сложить, 2 - вычесть второй из первого, 3 - вычесть первый из второго, 4 - домножить первый полином на константу, 5 - домножить второй полином на константу, 6 - перемножить\n";
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
				std::cout << "Введите константу:\n";
				double cnst;
				std::cin >> cnst;
				pol3 = pol1 * cnst;
				pol3.display();
			}
			else if (inp == 5) {
				std::cout << "Введите константу:\n";
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
				std::cout << "Некорректный ввод\n";
		} while (!(inp >= 0 && inp <= 6));
		do {
			std::cout << "Сохранить как:\n0 - не сохранять, 1 - полином 1, 2 - полином 2\n";
			std::cin >> inp;
			if (inp == 0) {}
			else if (inp == 1)
				pol1 = pol3;
			else if (inp == 2)
				pol2 = pol3;
			else
				std::cout << "Некорректный ввод\n";
		} while (!(inp >= 0 && inp <= 2));
	}
}