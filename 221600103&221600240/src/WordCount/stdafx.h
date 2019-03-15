// stdafx.h: 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 项目特定的包含文件
//

#pragma once

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<cctype>
#include<iterator>
#include<sstream>
#include<map>
#include<algorithm>
#include<iterator>
using namespace std;

typedef pair<string, int> PAIR;
bool operator< (const PAIR& lhs, const PAIR& rhs) {
	return lhs.second < rhs.second;
}

struct CmpByValue {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		if (lhs.second != rhs.second)
		{
			return lhs.second > rhs.second;
		}
		else
		{
			return lhs.first < rhs.first;
		}
	}
};

inline ostream& operator<<(ostream& out, const PAIR& p) {
	return out << "<" << p.first << ">" << ":" << p.second << "\n";
}

inline void printResult(int chars, int lines, int words, vector<PAIR> &wordSortVec)
{
	ofstream fout("result.txt");
	fout << "characters:" << chars << "\n";
	fout << "words:" << words << "\n";
	fout << "lines:" << lines << "\n";
	if ((int)wordSortVec.size() > 10)
	{
		for (int i = 0; i < 10; ++i) {
			fout << wordSortVec[i];
		}
	}
	else
	{
		for (int i = 0; i < (int)wordSortVec.size(); ++i) {
			fout << wordSortVec[i];
		}
	}
	fout.close();
}
inline int charCount(ifstream &fin, vector<char> &wCount)
{
	char ch;
	int characters = 0;
	while (fin.get(ch) && ch != '\0')
	{
		if (isascii(ch))
		{
			if (isspace(ch) || ispunct(ch))
			{
				characters++;
				wCount.push_back(' ');
			}
			else {
				wCount.push_back(ch);
				characters++;
			}
		}
		else
		{
			characters++;
		}
	}
	return characters;
}

inline int wordCount(vector<char> &wCount, vector<PAIR> &wordSortVec)
{
	string wordTotal;
	int realNum = 0;
	int j = 0, i = 0;
	int characters = wCount.size();
	vector<string> tmpStr;
	vector<string> wordFilter;


	for (i = 0;i < characters;i++)
	{
		if (isalpha(wCount[i]))
			wordTotal += tolower(wCount[i]);
		else
			wordTotal += wCount[i];
	}

	char * cstr = new char[wordTotal.length() + 1];
	strcpy(cstr, wordTotal.c_str());


	char * p = strtok(cstr, " ");
	while (p != 0)
	{
		tmpStr.push_back(p);
		p = strtok(NULL, " ");
	}
	delete[] cstr;

	for (i = 0, j = 0;i < (int)tmpStr.size();i++)
	{
		if (isalpha(tmpStr[i][0]) != 0 &&
			isalpha(tmpStr[i][1]) != 0 &&
			isalpha(tmpStr[i][2]) != 0 &&
			isalpha(tmpStr[i][3]) != 0)
		{
			wordFilter.push_back(tmpStr[i]);
			realNum++;
		}
	}

	map<string, int> wordMap;
	int same = 0;
	for (i = 0;i < (int)wordFilter.size();i++)
	{
		same = 0;
		for (int k = i + 1;k < realNum;k++)
		{
			if (wordFilter[i] == wordFilter[k])
			{
				same++;
			}
		}
		if (wordMap.find(wordFilter[i]) == wordMap.end())
		{
			wordMap.insert(make_pair(wordFilter[i], 1));
		}
		else
		{
			wordMap[wordFilter[i]] += 1;
		}
	}

	vector<PAIR> wordSort(wordMap.begin(), wordMap.end());
	sort(wordSort.begin(), wordSort.end(), CmpByValue());
	for (int i = 0; i != wordSort.size(); ++i)
	{
		wordSortVec.push_back(wordSort[i]);
	}

	return realNum;
}

inline int lineCount(ifstream &file)
{
	file.clear();
	file.seekg(0);
	string str = "";
	int count = 0;
	while (file) {
		str = "";
		getline(file, str);
		for (int i = 0;i < 33;i++)
		{
			str.erase(remove(str.begin(), str.end(), i), str.end());
		}
		str.erase(remove(str.begin(), str.end(), 127), str.end());
		if (!str.empty()) {
			count++;
		}
	}
	return count;
}