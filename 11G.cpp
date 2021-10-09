#include <iostream>
#include <vector>
#include <string>
#include <queue>

struct node {
	std::vector<int> to;
	int link = -1;
	int color = -1;

	node() : to(std::vector<int>(2, -1)) {};
};

struct trie {
	std::vector<node> vert;

	trie() : vert(std::vector<node>(1)) {};

	node& operator[](int ind) {
		return vert[ind];
	}

	void add(const std::string& s) {
		int v = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (vert[v].to[s[i] - '0'] == -1) {
				vert.push_back(node());
				vert[v].to[s[i] - '0'] = vert.size() - 1;
			}
			v = vert[v].to[s[i] - '0'];
		}
		vert[v].color = 1;
	}

	void Aho_Corasick() {
		vert[0].link = 0;
		for (int ch = 0; ch < 2; ++ch) {
			if (vert[0].to[ch] == -1) vert[0].to[ch] = 0;
		}
		std::queue<int> q;
		q.push(0);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (int c = 0; c < 2; ++c) {
				int nxt = vert[v].to[c];
				if (vert[nxt].link != -1) {
					continue;
				}
				if (v == 0) {
					vert[nxt].link = 0;
				}
				else {
					vert[nxt].link = vert[vert[v].link].to[c];
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
};

bool dfs(trie& tr, int ind = 0) {
	node& v = tr[ind];
	v.color = 0;
	if (tr[v.to[0]].color == 0 || tr[v.to[1]].color == 0) {
		return true;
	}
	if (tr[v.to[0]].color == -1) {
		if(dfs(tr, v.to[0])) return true;
	}
	if (tr[v.to[1]].color == -1) {
		if (dfs(tr, v.to[1])) return true;
	}
	v.color = 1;
	return false;
}

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
	std::cout << (dfs(viruses) ? "TAK" : "NIE");
}