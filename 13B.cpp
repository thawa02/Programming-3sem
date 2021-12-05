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

int main() {
	int n;
	std::cin >> n;
	std::vector<int> mindiv(n + 1), primes;
	for (int i = 1; i <= n; ++i) {
		mindiv[i] = i;
	}
	long long ans = 0;
	for (int curr = 2; curr <= n; ++curr) {
		if (mindiv[curr] == curr) {
			primes.push_back(curr);
		}
		for (int p : primes) {
			if (p * curr > n || p > mindiv[curr]) {
				break;
			}
			ans += p;
			mindiv[p * curr] = p;
		}
	}
	std::cout << ans;
}
