#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<vector>
#include<sstream>

using namespace std;
typedef pair<string, int> PAIR;

int __declspec(dllexport) charCount(ifstream &fin, vector<char> &wCount);
void __declspec(dllexport) printResult(int chars, int lines, int words, vector<PAIR> &wordSort);
int __declspec(dllexport) lineCount(ifstream &fin);
int __declspec(dllexport) wordCount(vector<char> &wCount, vector<PAIR> &wordSortVec);