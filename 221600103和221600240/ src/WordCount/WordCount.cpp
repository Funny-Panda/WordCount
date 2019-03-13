// WordCount.cpp : 定义 DLL 应用程序的导出函数。
//
#define _CRT_SECURE_NO_WARNINGS
#include "WordCount.h"
#include "stdafx.h"
#include <iostream>
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

ostream& operator<<(ostream& out, const PAIR& p) {
	return out << "<" << p.first << ">" << ":" << p.second << "\n";
}

int charCount(ifstream &fin, vector<char> &wCount)
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

void printResult(int chars, int lines, int words, vector<PAIR> &wordSortVec)
{
	ofstream fout("result.txt");
	fout << "characters:" << chars << "\n";
	fout << "words:" << words << "\n";
	fout << "lines:" << lines << "\n";
	for (int i = 0; i < 10; ++i) {
		fout << wordSortVec[i];
	}
	fout.close();
}

int wordCount(vector<char> &wCount, vector<PAIR> &wordSortVec)
{
	int num = 0, realNum = 0;
	int j = 0, i = 0;
	int characters = wCount.size();
	int row = characters / 4;
	char *wordTotal = new char[characters];
	char **wordList = new char *[row];
	for (i = 0;i < row;i++)
		wordList[i] = new char[characters];
	for (i = 0;i < (int)wCount.size();i++)
	{
		wordTotal[i] = wCount[i];
	}
	wordTotal[i] = '\0';

	char *substr = strtok(wordTotal, " ");
	while (substr != NULL)
	{
		strcpy(wordList[j], substr);
		j++;
		substr = strtok(NULL, " ");
	}
	num = j;

	char **wordFilter = new char *[num];
	for (i = 0;i < num;i++)
		wordFilter[i] = new char[characters];

	for (i = 0;i < num;i++)
	{
		for (j = 0;j < num;j++)
		{
			wordFilter[i][j] = '\0';
		}
	}

	for (i = 0, j = 0;i < num;i++)
	{
		if (isalpha(wordList[i][0]) != 0 &&
			isalpha(wordList[i][1]) != 0 &&
			isalpha(wordList[i][2]) != 0 &&
			isalpha(wordList[i][3]) != 0)
		{
			wordFilter[j++] = wordList[i];
			realNum++;
		}
	}

	map<string, int> wordMap;
	int same = 0;
	for (i = 0;i < realNum;i++)
	{
		same = 0;
		for (int k = i + 1;k < realNum;k++)
		{
			for (int m = 0; m < characters; m++)
			{
				wordFilter[i][m] = tolower(wordFilter[i][m]);
				wordFilter[k][m] = tolower(wordFilter[k][m]);
			}

			if (wordFilter[i] == wordFilter[k])
			{
				for (int m = 0; m < characters; m++)
				{
					wordFilter[k][m] = wordFilter[i][m];
				}
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
	for (int i = 0; i != wordSort.size(); ++i) {
		wordSortVec.push_back(wordSort[i]);
	}
	return realNum;
}

int lineCount(ifstream &file)
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

