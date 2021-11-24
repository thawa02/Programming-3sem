#include <iostream>
#include <vector>
#include <string>
#include <map>

class sufavtomat {
private:
	struct Node {
		std::vector<int> to;
		int link = -1;
		int len = 0;
		bool term = false;

		Node() : to(std::vector<int>(26, -1)) {};
		Node(const Node& other) = default;
	};

	std::vector<Node> vert;
	int last = 0;

	void AddChar(char c) {
		int next = (int(c) < 97 ? int(c) - 65 : int(c) - 97);
		vert.push_back(Node());
		int new_vert = vert.size() - 1;
		int prev = last;
		while (prev != -1 && vert[prev].to[next] == -1) {
			vert[prev].to[next] = new_vert;
			prev = vert[prev].link;
		}
		if (prev == -1) {
			vert[new_vert].link = 0;
			last = new_vert;
			return;
		}
		int curr = vert[prev].to[next];
		if (vert[curr].len == vert[prev].len + 1) {
			vert[new_vert].link = curr;
			last = new_vert;
			return;
		}
		vert.push_back(Node(vert[curr]));
		int clone = vert.size() - 1;
		vert[clone].len = vert[prev].len + 1;
		while (prev != -1 && vert[prev].to[next] == curr) {
			vert[prev].to[next] = clone;
			prev = vert[prev].link;
		}
		vert[new_vert].link = vert[curr].link = clone;
		last = new_vert;
	}

public:
	sufavtomat() : vert(std::vector<Node>(1)) {};

	void add(std::string to_add) {
		for (auto c : to_add) {
			AddChar(c);
		}
	}

	bool if_substr(std::string pattern) {
		int curr = 0;
		for (auto c : pattern) {
			int next = (int(c) < 97 ? int(c) - 65 : int(c) - 97);
			if (vert[curr].to[next] == -1) {
				return false;
			}
			curr = vert[curr].to[next];
		}
		return true;
	}
};

int main() {
	sufavtomat sufavt;
	char command;
	std::string str;
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	while (std::cin >> command >> str) {
		if (command == '?') {
			std::cout << (sufavt.if_substr(str) ? "YES" : "NO") << '\n';
		}
		else {
			sufavt.add(str);
		}
	}
}