#pragma once 
#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<set>
#include<vector>
#include<queue>

using namespace std;
using index = map<string, set<int>>;
using index_it = map<string, set<int>>::iterator;

bool judgenumber(char c);
bool judgeletter(char c);

/*bool judgef(char i) {
	if (i == '(' || i == ')' || i == '#' || i == '<' || i == '>' || i == '=' || i == '+' || i == '*' || i == '&')
		return 1;
	else
		return 0;
}*/