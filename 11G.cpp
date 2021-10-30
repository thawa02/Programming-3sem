/*G. Вирусы
ограничение по времени на тест1 секунда
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Комитет По Исследованию Бинарных Вирусов обнаружил, что некоторые последовательности единиц и нулей являются кодами вирусов. Комитет изолировал набор кодов вирусов.
Последовательность из единиц и нулей называется безопасной, если никакой ее подотрезок (т.е. последовательность из соседних элементов) не является кодом вируса. 
Сейчас цель комитета состоит в том, чтобы установить, существует ли бесконечная безопасная последовательность из единиц и нулей.

Входные данные
Первая строка содержит одно целое число N, равное количеству всех вирусных кодов. Каждая из следующих n строк содержит непустое слово, составленное из символов 0 и 1 
— код вируса. Суммарная длина всех слов не превосходит 30000.

Выходные данные
Первая и единственная строка вывода должна содержать слово:

TAK — если бесконечная, безопасная последовательность из нулей и единиц сушествует;
NIE — в противном случае.*/

#include <iostream>
#include <vector>
#include <string>
#include <queue>


struct trie {
	struct node {
		std::vector<int> to;
		int link = -1;
		int color = -1;

		node() : to(std::vector<int>(2, -1)) {};
	};

	std::vector<node> vert;

	trie() : vert(std::vector<node>(1)) {};

	node& operator[](int ind) {
		return vert[ind];
	}

	void add(const std::string& s) {
		int curr_vert = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (vert[curr_vert].to[s[i] - '0'] == -1) {
				vert.push_back(node());
				vert[curr_vert].to[s[i] - '0'] = vert.size() - 1;
			}
			curr_vert = vert[curr_vert].to[s[i] - '0'];
		}
		vert[curr_vert].color = 1;
	}

	void Aho_Corasick() {
		vert[0].link = 0;
		for (int c = 0; c < 2; ++c) {
			if (vert[0].to[c] == -1) {
				vert[0].to[c] = 0;
			}
		}
		std::queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int curr = q.front(); q.pop();
			for (int c = 0; c < 2; ++c) {
				int nxt = vert[curr].to[c];
				if (vert[nxt].link != -1) {
					continue;
				}
				if (curr == 0) {
					vert[nxt].link = 0;
				}
				else {
					vert[nxt].link = vert[vert[curr].link].to[c];
				}
				if (vert[vert[nxt].link].color == 1) {
					vert[nxt].color = 1;
				}
				for (int ch = 0; ch < 2; ++ch) {
					if (vert[nxt].to[ch] == -1) {
						vert[nxt].to[ch] = vert[vert[nxt].link].to[ch];
					}
				}
				q.push(nxt);
			}
		}
	}

	bool if_have_cycle(int ind = 0) {
		node& curr_vert = vert[ind];
		curr_vert.color = 0;
		if (vert[curr_vert.to[0]].color == 0 || vert[curr_vert.to[1]].color == 0) {
			return true;
		}
		if (vert[curr_vert.to[0]].color == -1) {
			if (if_have_cycle(curr_vert.to[0])) return true;
		}
		if (vert[curr_vert.to[1]].color == -1) {
			if (if_have_cycle(curr_vert.to[1])) return true;
		}
		curr_vert.color = 1;
		return false;
	}
};


int main() {
	int n;
	std::cin >> n;
	trie viruses;
	std::string virus;
	for (int i = 0; i < n; ++i) {
		std::cin >> virus;
		viruses.add(virus);
	}
	viruses.Aho_Corasick();
	std::cout << (viruses.if_have_cycle() ? "TAK" : "NIE");
}
