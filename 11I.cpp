/*I. Z-функция
ограничение по времени на тест1 секунда
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Найдите z-функцию заданной строки s.

Входные данные
Единственная строка содержит строку s длины от 1 до 106. Строка может содержать только латинские буквы и цифры.

Выходные данные
Выведите через пробел все значения z-функции строки s.*/

#include <iostream>
#include <string>
#include <vector>

std::vector<int> z_function(const std::string& s) {
	std::vector<int> z(s.size(), 0);
	int l = -1, r = -1;
	for (int i = 1; i < s.size(); ++i) {
		if (l <= i && i <= r) {
			z[i] = std::min(z[i - l], r - i + 1);
		}
		while (i + z[i] < s.size() && s[z[i]] == s[z[i] + i]) ++z[i];
		if (i + z[i] - 1 > r) {
			l = i; r = i + z[i] - 1;
		}
	}
	return z;
}

int main() {
	std::string s;
	std::cin >> s;
	auto z = z_function(s);
	for (int i = 0; i < s.size(); ++i) {
		std::cout << z[i] << ' ';
	}
}
