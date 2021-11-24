/*A. Суффиксный массив
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Постройте суффиксный массив для заданной строки s.

Входные данные
Первая строка входного файла содержит строку s (1≤|s|≤400000). Строка состоит из строчных латинских букв.

Выходные данные
Выведите |s| различных чисел — номера первых символов суффиксов строки s так, чтобы соответствующие суффиксы 
были упорядочены в лексикографически возрастающем порядке.*/

#include <iostream>
#include <string>
#include <vector>

struct sufmas {
private:
	const int symb = 27;
	const int first_symb = 96;
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

	sufmas(const std::string& str): str(str + char(first_symb)), 
			clss(std::vector<int>(str.size() + 1)), 
			pref(std::vector<int>(str.size() + 1)), 
			lcp(std::vector<int>(str.size() + 1)) {
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
	std::cin >> str;
	sufmas sm(str);
	for (int i = 1; i <= str.size(); ++i) {
		std::cout << sm.pref[i] + 1 << ' ';
	}
}
