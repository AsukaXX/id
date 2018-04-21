#pragma once
#include"id.h"

class Sort {
public:
	Sort();
	void wordlist_p(string s);
	void sortword();
	bool judgef();
	bool judges();
	bool judgel();
	bool judgecl();
	bool judgefu();
	bool judgeou();
	void print();
private:
	map<string, int> sysword, f_map, flag;
	queue<string> wordlist;
	string word;
	pair<string, int> l_w, r_w;
	vector<string> fun, veri, sys, cla, out;
	map<string, int>::iterator s;
	vector<string>::iterator s_v;
}; 
