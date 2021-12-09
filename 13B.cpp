/*B. Суммирование по составным
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Задано целое число N (4≤N≤106). Найти сумму наименьших простых делителей всех составных чисел, больших 2 и не превосходящих N.

Входные данные
Первая строка входных данных содержит одно целое число N.

Выходные данные
Выведите одно целое число — ответ к задаче.*/

#include <iostream>
#include <vector>

std::vector<int> count_mindiv(int last) {
	std::vector<int> mindiv(last + 1), primes;
	for (int i = 1; i <= last; ++i) {
		mindiv[i] = i;
	}
	for (int curr = 2; curr <= last; ++curr) {
		if (mindiv[curr] == curr) {
			primes.push_back(curr);
		}
		for (int p : primes) {
			if (p * curr > last || p > mindiv[curr]) {
				break;
			}
			mindiv[p * curr] = p;
		}
	}
	return mindiv;
}

int main() {
	int n;
	std::cin >> n;
	auto mindiv = count_mindiv(n);
	long long ans = 0;
	for (int i = 2; i <= n; ++i) {
		if (mindiv[i] != i) {
			ans += mindiv[i];
		}
	}
	std::cout << ans;
}
