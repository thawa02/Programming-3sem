/*D. Сортировка слов
ограничение по времени на тест1 секунда
ограничение по памяти на тест256 мегабайт
вводстандартный ввод
выводстандартный вывод
Одна из новых возможностей текстового редактора «World XP» – это сортировка слов в предложении. Выход новой бета-версии редактора должен состоятся не позднее, 
чем через пять часов, а заявленная функция еще не реализована.

Требуется написать программу, осуществляющую сортировку слов в предложении. При этом все символы, отличные от букв, должны сохраниться и не поменять своего
положения относительно вхождений слов. Для упрощения при подаче входных данных на вход вашей программы все такие символы будут заменены на символ «.» (точка).
Таким образом символ «.» имеет смысл разделителя между словами. Например, строка «..aba.a..ba» после сортировки пример вид «..a.aba..ba», а строка «c..bb.a» 
примет вид «a..bb.c». Слова следует сортировать лексикографически, как в словаре.

Входные данные
Входной файл содержит единственную строку, содержащую только прописные латинские буквы и символ «.». Слова могут разделяться любым количеством символов «.»,
строка может как начинаться, так и заканчиваться последовательностью точек. Длина заданной строки не менее 1 символа и не превосходит 106 символов.

Выходные данные
В выходной файл выведите строку после сортировки слов в ней.*/

#include <iostream>
#include <string>
#include <map>
#include <vector>

struct node {
	std::map<char, int> to;
	int term = 0;
};


struct trie {
private:
	std::vector<node> words;
	std::vector<int> dots;

	void print_next_word(int v, int& printed, std::string& word) {
		for (int i = 0; i < words[v].term; ++i) {
			std::cout << word;
			++printed;
			print_dots(printed);
		}
		for (auto to : words[v].to) {
			word += to.first;
			print_next_word(to.second, printed, word);
		}
		if (word.empty()) return;
		word.pop_back();
	}

public:
	trie(const std::string& s) :
		words(std::vector<node>(1)), dots(std::vector<int>(1)) {
		int v = 0;
		for (int i = 0; i < s.size(); ++i) {
			if (s[i] == '.') {
				++dots[dots.size() - 1];
				continue;
			}
			if (!words[v].to.count(s[i])) {
				words.push_back(node());
				words[v].to[s[i]] = words.size() - 1;
			}
			v = words[v].to[s[i]];
			if (i == s.size() - 1 || s[i + 1] == '.') {
				dots.push_back(0);
				++words[v].term;
				v = 0;
			}
		}
	}

	void print_dots(int ind) {
		std::cout << std::string(dots[ind], '.');
	}

	void print_sorted() {
		print_dots(0);
		std::string word("");
		int printed = 0;
		print_next_word(0, printed, word);
	}
};

int main() {
	std::string s;
	std::cin >> s;
	trie words(s);
	words.print_sorted();
}
