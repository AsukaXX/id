#include"sort.h"

int main() {
	ifstream c_f;
	c_f.open("D:\\t\\t2\\condec.cpp");
	string line,word,word_t;
	Sort s;
	while (getline(c_f, line)) {
		for (int i = 0; i < (int)line.size(); ++i) {
			if (judgeletter(line[i])) {
				word.push_back(line[i]);
			}
			else if (judgenumber(line[i])) {
				word.push_back(line[i]);
			}
			else if (line[i] != ' ' && line[i] != '\t'&&line[i]!='\n') {
				if (word.size() != 0) {
					s.wordlist_p(word);
					//cout << word<<endl;
					word.clear();
				}
				word.push_back(line[i]);
				s.wordlist_p(word);
				//cout << word << endl;
				word.clear();
			}
			else if (line[i] == '/'&&line[i - 1] == '/') {
				word_t = line.substr(i+1);
				continue;
			}else if (word.size() != 0) {
				word_t = word;
				s.wordlist_p(word);
				//cout << word << endl;
				word.clear();
			}
		}
		if (word.size() != 0) {
			word_t = word;
			s.wordlist_p(word);
			//cout << word << endl;
			word.clear();
		}
	}
	s.sortword();
	s.print();
	return 0;
}