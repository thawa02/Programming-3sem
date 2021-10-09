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