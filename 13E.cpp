/*E. Числа одного там чувака
ограничение по времени на тест2 s.
ограничение по памяти на тест256 MB
вводstandard input
выводstandard output
Даны n объектов, вес i-го из них равен ai. Если X — какое-то подмножество этих объектов, его вес определяется формулой weight(X)=|X|⋅∑i∈Xai.

Если P — какое-то разбиение всех объектов на несколько непустых подмножеств, то его вес weight(P)=∑X∈Rweight(S).

Найдите суммарный вес всех разбиений данного множества на k непустых подмножеств по модулю 109+7. Обратите внимание, порядок множеств в разбиении значения не имеет.

Входные данные
В первой строке заданы целые числа n и k (1≤k≤n≤2⋅105) — количество элементов в множестве и количество подмножеств в разбиении.

Во второй строке задано через пробел n целых чисел ai (1≤ai≤109) — веса элементов.

Выходные данные
Выведите единственное число — суммарный вес всех различных разбиений на k непустых подмножеств по модулю 109+7.*/
//Answer is S_{n,k} + (n - 1) * S_{n-1,k}

#include <iostream>
#include <vector>

int mod = 1e9 + 7;

long long binpow(long long base, int deg) {
	if (deg == 1) return base;
	if (deg % 2 == 0) {
		return binpow((base * base) % mod, deg / 2);
	}
	return (base * binpow((base * base) % mod, deg / 2)) % mod;
}

std::vector<long long> reverse(int n, long long mod) {
	std::vector<long long> ans(n + 1);
	ans[1] = 1;
	for (int i = 2; i <= n; ++i) {
		ans[i] = (mod - ((mod / i) * ans[mod % i]) % mod) % mod;
	}
	return ans;
}

long long count_sum_of_weights(int sz, int num) {
	auto rev = reverse(num, mod);
	std::vector<long long> rev_fact(num + 1);
	rev_fact[0] = 1;
	for (int i = 1; i <= num; ++i) {
		rev_fact[i] = (rev_fact[i - 1] * rev[i]) % mod;
	}
	long long ans = 0;
	//S_{n, k} + (n - 1) * S_{n - 1, k} = \sum\limits_{j = 1}{k} (-1)^{k + j} * j^{n - 1} * (j + n - 1) /j!(k - j)!
	for (int j = 0; j <= num; ++j) {
		int exp = (binpow(j, sz - 1) * (j + sz - 1)) % mod;
		long long term = (rev_fact[j] * rev_fact[num - j]) % mod;
		term *= exp;
		ans += ((num + j) % 2 == 0 ? 1 : -1) * term;
		ans %= mod;
	}
	return ans;
}

int main() {
	int n, k;
	std::cin >> n >> k;
	long long sum = 0;
	for (int i = 0; i < n; ++i) {
		int curr;
		std::cin >> curr;
		sum += curr;
	}
	sum %= mod;
	if (n == k) {
		std::cout << sum;
		return 0;
	}
	long long ans = count_sum_of_weights(n, k);
	ans *= sum;
	ans %= mod;
	std::cout << ans;
}
