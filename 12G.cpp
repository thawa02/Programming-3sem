/*G. Ненокку
ограничение по времени на тест2 секунды
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Очень известный автор не менее известной книги решил написать продолжение своего произведения. Он писал все свои книги на компьютере,
подключенном к интернету. Из-за такой неосторожности мальчику Ненокку удалось получить доступ к еще ненаписанной книге. Каждый вечер 
мальчик залазил на компьютер писателя и записывал на свой компьютер новые записи. Ненокку, записав на свой компьютер очередную главу, 
заинтересовался, а использовал ли хоть раз писатель слово "книга". Но он не любит читать книги (он лучше полазает в интернете), и поэтому
он просит вас узнать есть ли то или иное слово в тексте произведения. Но естественно его интересует не только одно слово, а достаточно много.

Входные данные
В каждой строчке входного файла записана одна из двух записей.

? <слово> (<слово> — это набор не более 50 латинских символов): запрос проверки существования подстроки <слово> в произведении;
A <текст> (<текст> — это набор не более 105 латинских символов): добавление в произведение <текст>.
Писатель только начал работать над произведением, поэтому он не мог написать более 105 символов. Суммарная длина всех запросов не 
превосходит 15 мегабайт плюс 12140 байт.

Выходные данные
Выведите на каждую строчку типа 1 "YES", если существует подстрока <слово>, и "NO" в противном случае. Не следует различать регистр букв.
*/
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
