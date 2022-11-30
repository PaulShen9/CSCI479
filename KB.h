#pragma once
#ifndef KB_H
#define KB_H
#include <list>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

bool isNegation(string);

//class used to mange the input and get ouput to the user
class EasyMap
{
public:
	EasyMap();
	void insert(pair<string,string>);
	list<string> find(string);
	int query(string);
	list<string> split(const string& str, const string& delim);
	int RecursiveQuery(list<string>);
	
private:
	pair<string, list<string>>* m_hashMap;
	bool m_result;
	bool m_hasOther;
	int count ;
};



//class contains only ask and tell
class HF_KB
{
public:
	void TELL(string,string);
	bool ASK(string);
private:
	EasyMap m_map;
};
#endif
