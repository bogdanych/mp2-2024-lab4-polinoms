#pragma once

#include "list.h"

template<class T>
class Polynom
{
	List<T> pol;
public:
	Polynom() {};
	Polynom(std::string st) {
		List<double> lst;
		std::string s;
		for (int i = 0; i < st.size(); i++)
			if (st[i] != ' ')
				s.push_back(st[i]);
		int sgn = 1;
		int i = 0;
		if (s[0] == '-') {
			sgn = -1;
			i++;
		}
		for (; i < s.size();i++) {
			int a = 0, b = 0, c = 0;
			double k = 1.0;
			while (i < s.size() && s[i] != '+' && s[i] != '-') {
				if (s[i] == '*') {
					i++;
				}
				else if (s[i] >= '0' && s[i] <= '9') {
					k = 0.0;
					std::string num;
					while (i < s.size() && (s[i] >= '0' && s[i] <= '9') || s[i] == ',') {
						num.push_back(s[i]);
						i++;
					}
					k = std::stod(num);
				}
				else if (s[i] == 'x') {
					if (i + 1 < s.size() && s[i + 1] == '^') {
						a = (s[i + 2] - '0');
						i = i + 3;
					}
					else {
						a = 1;
						i = i + 1;
					}
					if (i < s.size() && std::isdigit(s[i]))
						throw std::logic_error("Too big degree!");
				}
				else if (s[i] == 'y') {
					if (i + 1 < s.size() && s[i + 1] == '^') {
						b = (s[i + 2] - '0');
						i = i + 3;
					}
					else {
						b = 1;
						i = i + 1;
					}
					if (i < s.size() && std::isdigit(s[i]))
						throw;
				}
				else if (s[i] == 'z') {
					if (i + 1 < s.size() && s[i + 1] == '^') {
						c = (s[i + 2] - '0');
						i = i + 3;
					}
					else {
						c = 1;
						i = i + 1;
					}
					if (i < s.size() && std::isdigit(s[i]))
						throw;
				}
				else {
					throw std::logic_error("Invalid input!");
				}
			}
			//std::cout << k << ' ' << a << ' ' << b << ' ' << c << '\n';
			lst.append(k * sgn, a * 100 + b * 10 + c);
			if (s[i] == '-') {
				sgn = -1;
			}
			else
				sgn = 1;
		}
		for (auto it = lst.begin(); it != lst.end(); ++it) {
			if (*it != 0)
				pol.append(*it, it.ind()); // сортируем ненулевые элементы списка
		}
	}
	Polynom(const List<T>& sec) {
		for (auto it = sec.begin(); it != sec.end(); ++it) {
			if (*it != 0)
				pol.append(*it, it.ind()); // сортируем ненулевые элементы списка
		}
	};

	void operator =(const Polynom& sec) {
		pol.clear();
		for (auto it = sec.pol.begin(); it != sec.pol.end(); ++it) {
			pol.push_back(*it, it.ind());
		}
	}

	bool operator==(const Polynom& p) {
		return (pol == p.pol);
	}
	
	bool operator!=(const Polynom& p) {
		return (p != p.pol);
	}

	Polynom operator +(const Polynom& sec) {
		Polynom<T> res;
		auto it1 = pol.begin();
		auto it2 = sec.pol.begin();
		while (it1 != pol.end() && it2 != sec.pol.end()) {
			if (it1.ind() > it2.ind()) {
				if (*it2 != 0)
					res.pol.push_back(*it2, it2.ind()); //используем push_back, т.к. pol отсортирован
				++it2;
			}
			else if (it1.ind() < it2.ind()) {
				if (*it1 != 0)
					res.pol.push_back(*it1, it1.ind());
				++it1;
			}
			else {
				if (*it1 + *it2 != 0)
					res.pol.push_back(*it1 + *it2, it1.ind());
				++it1;
				++it2;
			}
		}
		while (it1 != pol.end()) {
			if (*it1 != 0)
				res.pol.push_back(*it1, it1.ind());
			++it1;
		}
		while (it2 != sec.pol.end()) {
			if (*it2 != 0)
				res.pol.push_back(*it2, it2.ind());
			++it2;
		}
		return res;
	}

	Polynom operator *(T cnst) {
		Polynom<T> res;
		if (cnst != 0)
			for (auto it = pol.begin(); it != pol.end(); ++it){
				res.pol.push_back(*it * cnst, it.ind());
			}
		return res;
	}

	Polynom operator-(const Polynom& sec) {
		Polynom<T> cur = sec;
		return *this + cur * (-1);
	}

	Polynom operator *(const Polynom& sec) {
		Polynom<T> res;
		for (auto it1 = pol.begin(); it1 != pol.end(); ++it1) {
			for (auto it2 = sec.pol.begin(); it2 != sec.pol.end(); ++it2) {
				int ind1 = it1.ind();
				int ind2 = it2.ind();
				for (int i = 1; i <= 100; i *= 10) {
					int res1 = ind1 % 10;
					int res2 = ind2 % 10;
					if (res1 + res2 >= 10)
						throw std::logic_error("Too big degree of number!");
					ind1 /= 10;
					ind2 /= 10;
				}
				if (*it1 != 0 && *it2 != 0)
					res.pol.append(*it1 * (*it2), it1.ind() + it2.ind());
			}
		}
		return res;
	}

	std::string to_string() {
		std::string res;
		int i = 0;
		for (auto it = pol.begin(); it != pol.end(); ++it, i++) {
			if (i != 0)
				res += (" + ");
			if (*it == 1 && it.ind() == 0)
				res += "1";
			else if (*it == -1)
				res += ('-');
			else if (*it != 1)
				res += std::to_string(*it);
			int ind = it.ind();
			if (ind / 100 != 0) {
				res += ('x');
				if (ind / 100 != 1)
					res += ('^' + std::to_string(ind / 100));
			}
			if ((ind / 10) % 10 != 0) {
				res +=("y");
				if ((ind / 10) % 10 != 1)
					res += ("^" + std::to_string((ind / 10) % 10));
			}
			if (ind % 10 != 0) {
				res += ("z");
				if (ind % 10 != 1)
					res += ("^" + std::to_string(ind % 10));
			}
		}
		if (res == "")
			res = "0";
		return res;
	}
	
	void display() {
		std::cout << to_string() << '\n';
	}
};