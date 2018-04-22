#include"sort.h"
bool judgeletter(char c) {
	if (c >= 'a'&&c <= 'z' || c >= 'A'&&c <= 'Z' || c == '_')
		return 1;
	else
		return 0;
}

bool judgenumber(char c) {
	if (c >= '0'&&c <= '9')
		return 1;
	else
		return 0;
}
inline int stringtoint(const string s) {
	int i = 0;
	istringstream ss(s);
	ss >> i;
	return i;
}

Sort::Sort() {
	ifstream f_sys;
	string line;
	f_sys.open("sysword.txt");
	while (getline(f_sys, line)) {
		int i = line.find(" ");
		string l = line.substr(0, i);
		int r = stringtoint(line.substr(i + 1, line.size()));
		sysword.insert(pair<string, int>(l, r));
	}
	f_sys.close();
	f_sys.open("f.txt");
	while (getline(f_sys, line)) {
		int i = line.find(" ");
		string l = line.substr(0, i);
		int r = stringtoint(line.substr(i + 1, line.size()));
		f_map.insert(pair<string, int>(l, r));
	}
	f_sys.close();
	flag["class"] = 0;
	flag["function"] = 0;
	flag["output"] = 0;
	flag["cycle"] = 0;
}

void Sort::wordlist_p(string s) {
	wordlist.push(s);
}

void Sort::sortword() {
	r_w.first = wordlist.front();
	wordlist.pop();
	while (!wordlist.empty()) {
		word = r_w.first;
		r_w.first = wordlist.front();
		wordlist.pop();
		if (judgef())
			continue;
		if (judgeou())
			continue;
		for (char w : word) {
			if (judgenumber(w)) {
				if (word_t.size() != 0 && l_w.second == 903) {
					if (flag["function"] != 0)
						veri_c.push_back(word_t);
					else
						veri.push_back(word_t);
					word_t.clear();
				}
				l_w.first = word;
				l_w.second = 5;//变量
				if (flag["function"] != 0) {
					veri_c.push_back(word);
				}
				else
					veri.push_back(word);
				word.clear();
				break;
			}
		}
		if (word.empty())
			continue;
		if (judges())
			continue;
		if (judgecl())
			continue;
		if (judgefu())
			continue;
		if (judgel())
			continue;
		if (judgev())
			continue;
	}
}

bool Sort::judgef() {
	if (word.size() == 1) {
		if (!judgeletter(word[0]) && !judgenumber(word[0])) {
			if (flag["output"] == 1) {
				if (word[0] == '"'&&l_w.second != '\\')
					flag["output"] = 0;
				l_w.first = word;
				l_w.second = 8;//输出
				return 1;
			}
			if (word[0] == '&'&&l_w.second == 105) {
				l_w.first = word;
				l_w.second = 105;
				return 1;
			}
			s = f_map.find(word);
			if (s != f_map.end()) {
				l_w.first = word;
				l_w.second = s->second;//符号
				if (word[0] == '{') {
					if (stack_f.size() != 0&&stack_f.back() == " ")
						stack_f.pop_back();
					stack_f.push_back(word);
				}
				if (word[0] == '}'&&stack_f.size() != 0) {
					stack_f.pop_back();
					if (stack_s.back() == "cl")
						flag["class"] -= 1;
					if (stack_s.back() == "fu")
						flag["function"] -= 1;
					if (stack_s.back() == "cy")
						flag["cycle"] -= 1;
					stack_s.pop_back();
				}
				if (word[0] == ';'&&stack_f.size()!=0) {
					while (stack_f.size() != 0&&stack_f.back() == " ") {
						if (stack_s.back() == "cl")
							flag["class"] -= 1;
						if (stack_s.back() == "fu")
							flag["function"] -= 1;
						if (stack_s.back() == "cy")
							flag["cycle"] -= 1;
						stack_f.pop_back();
						stack_s.pop_back();
					}
				}
				if (word_t.size() != 0 && word[0] == ')') {
					fun.push_back(word_t);
					flag["function"] += 1;
					stack_s.push_back("fu");
					stack_f.push_back(" ");
					word_t.clear();
				}
				return 1;
			}
			else {
				l_w.first = word;
				l_w.second = 9;//符号
				return 1;
			}
		}
	}
	return 0;
}

bool Sort::judgecl() {
	s_v = find(cla.begin(), cla.end(), word);
	if (s_v != cla.end() && flag["output"] == 0) {
		if (l_w.second == 917) {
			fun.push_back(l_w.first.append(word));
			l_w.first = word;
			l_w.second = 4;//函数名
			flag["function"] += 1;
			stack_s.push_back("fu");
			stack_f.push_back(" ");
			return 1;
		}
		if (r_w.first[0] == '(') {
			fun.push_back(word);
			l_w.first = word;
			l_w.second = 4;//函数名
			flag["function"] += 1;
			stack_s.push_back("fu");
			stack_f.push_back(" ");
			return 1;
		}
		l_w.first = word;
		l_w.second = 105;//类名
		return 1;
	}
	if (l_w.second == 104) {
		cla.push_back(word);
		l_w.first = word;
		l_w.second = 105;//类名
		flag["class"] += 1;
		stack_s.push_back("cl");
		stack_f.push_back(" ");
		word.clear();
		return 1;
	}
	return 0;
}

bool Sort::judges() {
	s = sysword.find(word);
	if (s != sysword.end() && flag["output"] == 0) {
		if (word_t.size() != 0 && l_w.second == 903) {
			fun.push_back(word_t);
			flag["function"] += 1;
			stack_s.push_back("fu");
			stack_f.push_back(" ");
			word_t.clear();
		}
		l_w.first = word;
		l_w.second = s->second;//系统保留字
		sys.push_back(word);
		if (s->second == 106) {
			stack_f.push_back(" ");
			stack_s.push_back("cy");
			flag["cycle"] += 1;
		}
		if (s->second == 109) {
			stack_f.push_back(" ");
			stack_s.push_back("fu");
			flag["function"] += 1;
		}
		return 1;
	}
	return 0;
}

bool Sort::judgefu() {
	if (flag["output"] == 0) {
		s_v = find(fun.begin(), fun.end(), word);
		if (s_v != fun.end()) {
			l_w.first = word;
			l_w.second = 4;//函数名
			fun.push_back(word);
			flag["function"] += 1;
			stack_s.push_back("fu");
			stack_f.push_back(" ");
			word.clear();
			return 1;
		}
		if (l_w.second == 105 && r_w.first[0] == '(') {
			l_w.first = word;
			l_w.second = 20;//函数名或变量名
			word_t = word;
			return 1;
		}
		if (r_w.first[0] == '('&&l_w.first == ".") {
			fun.push_back(word);
			l_w.first = word;
			l_w.second = 4;//函数名
			flag["function"] += 1;
			stack_s.push_back("fu");
			stack_f.push_back(" ");
			word.clear();
			return 1;
		}
	}
	return 0;
}

bool Sort::judgeou() {
	if (l_w.second == 915 || l_w.second == 8) {
		flag["output"] = 1;
		out.push_back(word);
		l_w.first = word;
		l_w.second = 8;//输出
		word.clear();
		return 1;
	}
	if (flag["output"] == 1) {
		out.push_back(word);
		l_w.first = word;
		l_w.second = 8;//输出
		word.clear();
		return 1;
	}
	return 0;
}

bool Sort::judgel() {
	for (char w : r_w.first) {
		if (!judgeletter(w) && !judgenumber(w)) {
			if (w == '>'&&l_w.first == "<") {
				l_w.first = word;
				l_w.second = 100;//头文件
				sys.push_back(word);
				word.clear();
				return 1;
			}
			if (w == ';'&&l_w.second == 103) {
				l_w.first = word;
				l_w.second = 120;//命名空间
				sys.push_back(word);
				word.clear();
				return 1;
			}
		}
	}
	return 0;
}

bool Sort::judgev() {
	if (flag["function"] != 0) {
		if (word_t.size() != 0) {
			veri_c.push_back(word_t);
			word_t.clear();
		}
		veri_c.push_back(word);
		l_w.first = word;
		l_w.second = 5;//变量
		word.clear();
		return 1;
	}
	else {
		if (word_t.size() != 0) {
			veri.push_back(word_t);
			word_t.clear();
		}
		veri.push_back(word);
		l_w.first = word;
		l_w.second = 5;//变量
		word.clear();
		return 1;
	}
	return 0;
}

void Sort::print() {
	cout << "sys:" << endl;
	for (string s : sys)
		cout << s << endl;
	cout << "fun:" << endl;
	for (string s : fun)
		cout << s << endl;
	cout << "ver:" << endl;
	for (string s : veri)
		cout << s << endl;
	cout << "cla:" << endl;
	for (string s : cla)
		cout << s << endl;
	cout << "out:" << endl;
	for (string s : out)
		cout << s << endl;
	cout << "ver_c:" << endl;
	for (string s : veri_c)
		cout << s << endl;
}
