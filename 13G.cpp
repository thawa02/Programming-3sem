/*G. Быстрое преобразование Фурье
ограничение по времени на тест1 секунда
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Даны два многочлена

A(x)=anxn+an−1xn−1+⋯+a0
B(x)=bmxm+bm−1xm−1+⋯+b0
Вычислите C(x)=A(x)⋅B(x)
Входные данные
n,an,an−1,…,a0
m,bm,bm−1,…,b0
0≤n,m<216, |ai|,|bj|≤9
an≠0,bm≠0
Выходные данные
Выведите коэффициенты C в том же формате*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <complex>
#include <vector>
#include <cmath>

using compl = std::complex<double>;

void fft(std::vector<compl>& coef, bool inverse) {
	int sz = coef.size();
	if (sz == 1) {
		return;
	}
	std::vector<compl> coef0(sz / 2), coef1(sz / 2);
	for (int i = 0; i < sz; i += 2) {
		coef0[i/2] = coef[i];
		coef1[i/2] = coef[i + 1];
	}
	fft(coef0, inverse);
	fft(coef1, inverse);
	double angle = M_PI * 2 / sz * (inverse ? -1 : 1);
	compl curr(1), prime_root(cos(angle), sin(angle));
	for (int i = 0; i < sz / 2; ++i) {
		coef[i] = coef0[i] + curr * coef1[i];
		coef[i + sz / 2] = coef0[i] - curr * coef1[i];
		curr *= prime_root;
		if (inverse) {
			coef[i] /= 2;
			coef[i + sz / 2] /= 2;
		}
	}
}

std::vector<compl> multiply(std::vector<compl> p, std::vector<compl> q) {
	int deg = 0;
	while ((1 << deg) < p.size() + q.size()) {
		++deg;
	}
	p.resize(1 << deg, 0);
	q.resize(1 << deg, 0);
	fft(p, false);
	fft(q, false);
	for (int i = 0; i < (1 << deg); ++i) {
		p[i] *= q[i];
	}
	fft(p, true);
	return p;
}

int main() {
	int n, m;
	std::cin >> n;
	std::vector<compl> p(n + 1);
	for (int i = n; i >= 0; --i) {
		std::cin >> p[i];
	}
	std::cin >> m;
	std::vector<compl> q(m + 1);
	for (int i = m; i >= 0; --i) {
		std::cin >> q[i];
	}
	auto product = multiply(p, q);
	std::cout << n + m << ' ';
	for (int i = n + m; i >= 0; --i) {
		std::cout << int(llround(product[i].real())) << ' ';
	}
}
