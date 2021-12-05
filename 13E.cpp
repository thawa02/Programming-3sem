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

int main() {
	int n, k;
	std::cin >> n >> k;
	auto rev = reverse(k, mod);
	std::vector<long long> rev_fact(k + 1);
	rev_fact[0] = 1;
	for (int i = 1; i <= k; ++i) {
		rev_fact[i] = (rev_fact[i - 1] * rev[i]) % mod;
	}
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
	long long ans = 0;
	//S_{n, k} + (n - 1) * S_{n - 1, k} = \Sigma_{j = 1}^k (-1)^{k + j} * j^{n - 1} * (j + n - 1) /j!(k - j)!
	for (int j = 0; j <= k; ++j) {
		int exp = (binpow(j, n - 1) * (j + n - 1)) % mod;
		long long term = (rev_fact[j] * rev_fact[k - j]) % mod;
		term *= exp;
		ans += ((k + j) % 2 == 0 ? 1 : -1) * term;
		ans %= mod;
	}
	ans %= mod;
	ans *= sum;
	ans %= mod;
	std::cout << ans;
}