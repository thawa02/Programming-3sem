#include <iostream>
#include <string>
#include <vector>

struct sufmas {
private:
	const int symb = 59;
	const int first_symb = 64;
	std::vector<int> clss;

	void CountFirstStep() {
		std::vector<int> cnt(symb, 0);
		for (int i = 0; i < str.size(); ++i) {
			++cnt[int(str[i]) - first_symb];
		}
		for (int i = 1; i < cnt.size(); ++i) {
			cnt[i] += cnt[i - 1];
		}
		for (int i = str.size() - 1; i >= 0; --i) {
			pref[--cnt[int(str[i]) - first_symb]] = i;
		}
	}

	void CountNextStep(int classes, int step) {
		std::vector<int> cnt(symb, 0);
		std::vector<int> new_pref(str.size());
		for (int i = 0; i < str.size(); ++i) {
			new_pref[i] = (pref[i] - (1 << step) + str.size()) % str.size();
		}
		cnt = std::vector<int>(classes, 0);
		for (int i = 0; i < str.size(); ++i) {
			++cnt[clss[new_pref[i]]];
		}
		for (int i = 1; i < cnt.size(); ++i) {
			cnt[i] += cnt[i - 1];
		}
		for (int i = str.size() - 1; i >= 0; --i) {
			pref[--cnt[clss[new_pref[i]]]] = new_pref[i];
		}
	}

	int CalcClssFirst() {
		int classes = 1;
		clss[pref[0]] = 0;
		for (int i = 1; i < str.size(); ++i) {
			if (str[pref[i]] != str[pref[i - 1]]) {
				++classes;
			}
			clss[pref[i]] = classes - 1;
		}

		return classes;
	}

	int CalcClssNext(int step) {
		std::vector<int> new_clss(str.size());
		int classes = 1;
		new_clss[pref[0]] = 0;
		for (int i = 1; i < str.size(); ++i) {
			int mid1 = (pref[i] + (1 << step)) % str.size(),
				mid2 = (pref[i - 1] + (1 << step)) % str.size();
			if (clss[pref[i]] != clss[pref[i - 1]] || clss[mid1] != clss[mid2]) {
				++classes;
			}
			new_clss[pref[i]] = classes - 1;
		}
		clss = std::move(new_clss);

		return classes;
	}

	void CountLCP() {
		std::vector<int> pos(str.size());
		for (int i = 0; i < str.size(); ++i) {
			pos[pref[i]] = i;
		}

		int cur_lcp = 0;
		for (int i = 0; i < str.size(); ++i) {
			int ind = pos[i];
			if (ind == str.size() - 1) {
				cur_lcp = 0;
				continue;
			}
			int next_pref = pref[ind + 1];
			cur_lcp = std::max(cur_lcp - 1, 0);
			while (i + cur_lcp < str.size() && next_pref + cur_lcp < str.size() && 
				str[i + cur_lcp] == str[next_pref + cur_lcp]) {
				++cur_lcp;
			}
			lcp[ind] = cur_lcp;
		}
	}

public:
	const std::string str;
	std::vector<int> pref;
	std::vector<int> lcp;

	sufmas(const std::string& str): str(str), clss(std::vector<int>(str.size())), 
		pref(std::vector<int>(str.size())), lcp(std::vector<int>(str.size())) {
		CountFirstStep();
		int classes = CalcClssFirst();

		for (int i = 0; (1 << i) < str.size(); ++i) {
			CountNextStep(classes, i);
			classes = CalcClssNext(i);
		}
	}
};

int main() {
	std::string str;
	long long num;
	std::cin >> str >> num;
	str += char(64);
	sufmas ms(str);
	int ind = 1;
	while (ind < str.size() - 1 && 
		num > int(str.size()) - ms.pref[ind] - 1 - ms.lcp[ind - 1]) {
		num -= int(str.size()) - ms.pref[ind] - 1 - ms.lcp[ind - 1];
		++ind;
	}
	if (num > int(str.size()) - ms.pref[ind] - 1 - ms.lcp[ind - 1]) {
		for (int i = ms.pref[ind]; i < str.size() - 1; ++i) {
			std::cout << str[i];
		}
		return 0;
	}
	for (int i = ms.pref[ind]; i < ms.pref[ind] + ms.lcp[ind - 1] + num; ++i) {
		std::cout << str[i];
	}
}