#include"sort.h"

void createindex(index& index_m,const string word,const int line) {
	index_it it_in;
	set<int> set_t;
	it_in = index_m.find(word);
	if (it_in == index_m.end()) {
		set_t.insert(line);
		index_m.insert(make_pair(word, set_t));
	}
	else {
		it_in->second.insert(line);
	}
}

int main() {
	ifstream c_f;
	ofstream i_f;
	string line,word,word_t,path;
	index index_m;
	index_it index_it;
	int line_s=0;
	Sort s;
	do {
		cin >> path;
		//path = "D:\\C++\\serach\\serach\\simil_fuction.cpp";
		c_f.open(path);
	}while(!c_f);
	s.dirctory(path.substr(0, path.find("\\")));
	while (getline(c_f, line)) {
		++line_s;
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
					createindex(index_m, word, line_s);
					word.clear();
				}
				word.push_back(line[i]);
				s.wordlist_p(word);
				//cout << word << endl;
				//createindex(index_m, word, line_s);
				word.clear();
			}
			else if (line[i] == '/'&&line[i + 1] == '/') {
				word_t = line.substr(i+2);
				continue;
			}else if (word.size() != 0) {
				word_t = word;
				s.wordlist_p(word);
				//cout << word << endl;
				createindex(index_m, word, line_s);
				word.clear();
			}
		}
		if (word.size() != 0) {
			word_t = word;
			s.wordlist_p(word);
			//cout << word << endl;
			createindex(index_m, word, line_s);
			word.clear();
		}
	}
	c_f.close();
	i_f.open("d:\\t\\index.txt", ios::ate);
	for (index_it = index_m.begin(); index_it != index_m.end(); ++index_it) {
		i_f << index_it->first << ":";
		for (int i : index_it->second)
			i_f << i << " ";
		i_f << endl;
	}
	i_f.close();
	s.sortword();
	s.print();
	return 0;
}