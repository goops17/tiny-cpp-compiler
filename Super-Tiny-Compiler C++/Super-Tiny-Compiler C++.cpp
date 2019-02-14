#include "pch.h"
#include<stdlib.h>
#include<string.h>
#include<string>
#include<ctype.h>
#include<fstream>
#include<iostream>
#include<vector>
using namespace std;


bool isKeyword(char buffer[]) {
	char keywords[32][10] =
	{"char","else","float","for","if","int","while" };
	int i; 
	bool flag=false;
	for (i = 0; i < 32; ++i) {
		if (strcmp(keywords[i], buffer) == 0) {
			flag = true;
			break;
		}
	}
	return flag;
}

bool isOther(char test) {
	string other = ",;\(){}[]'':";
	return (other.find(string(1,test))!=-1);
}

bool isNumeric(char test) {
	string number = ".0123456789";
	return (number.find(string(1, test)) != -1);
}

bool isMath(char test) {
	string math = "+ -*/=";
	return (math.find(string(1, test)) != -1);
}

int main() {
	char ch, temp[30], tempKeyword[15];
	string str;
	int mark[1000] = { 0 };
	int num_count=0, keywordCount=0;
	vector<char>other;
	vector<string>num;
	vector<char>logical;
	vector<char>math;
	vector<string> keywords;
	vector<string> ids;
	ifstream fread("test.wsc");
	ofstream fwrite("test.wsc.lex");
	if (!fread.is_open()) {
		cout << "error while opening the file\n";
		exit(0);
	}
	

	while (!fread.eof())
	{
		ch = fread.get();
		
		//finding others
		if (isOther(ch)) {
			int aa = ch;
			if (mark[aa] != 1)
			{
				mark[aa] = 1;
				other.push_back(ch);
			}
		}

		//finding numeric 
		if (isNumeric(ch) || ch == ' ' || ch == '\n' || ch == ';') {
			if (isNumeric(ch)) temp[num_count++] = ch;
			if ((ch == ' ' || ch == ';') && (num_count != 0)) {
				temp[num_count] = '\0';
				num_count = 0;
				num.push_back(temp);
			}
		}

		//finding logical
			if (ch == '>' || ch=='<') 
			{
				int aa = ch;
				if (mark[aa] != 1) {
					logical.push_back(ch);
					mark[aa] = 1;
				}
			}

		//finding mathamatical 
			if (isMath(ch))
			{
				int aa = ch;
				if (mark[aa] != 1) {
					math.push_back(ch);
					mark[aa] = 1;
				}
			}

		//finding keywords or variable
			if (isalnum(ch)) {
				tempKeyword[keywordCount++] = ch;
			}
			else if ((ch == ' ' || ch == '\n') && (keywordCount != 0)) {
				tempKeyword[keywordCount] = '\0';
				keywordCount = 0;

				if (isKeyword(tempKeyword)) keywords.push_back(tempKeyword);
				else {
					if (tempKeyword[0] >= 97 && tempKeyword[0] <= 122) {
						if (mark[tempKeyword[0]] != 1) {
							ids.push_back(string(1,tempKeyword[0]));
							mark[tempKeyword[0]] = 1;
						}
					}
				}

			}

	}
	
		cout << "Other :";
		fwrite << "Other: ";
		for (int i=0; i < other.size(); i++)
		{
			fwrite << other[i];
			cout << other[i];
		}
		fwrite << "\n";
		cout << endl;

		cout << "Numeric :";
		fwrite << "Numeric: ";
		for (int i = 0; i < num.size(); i++)
		{
			fwrite << num[i];
			cout << num[i] << ", ";
		}
		fwrite << "\n";
		cout << endl;

		cout << "Logical :";
		fwrite << "Logical: ";
		for (int i = 0; i < logical.size(); i++)
		{
			fwrite << logical[i];
			cout << logical[i] << ", ";
		}
		fwrite << "\n";
		cout << endl;

		cout << "Math :";
		fwrite << "Math: ";
		for (int i = 0; i < math.size(); i++)
		{
			fwrite << math[i];
			cout << math[i] << ", ";
		}
		fwrite << "\n";
		cout << endl;

		cout << "Keywords :";
		fwrite << "Keywords: ";
		for (int i = 0; i < keywords.size(); i++)
		{
			fwrite << keywords[i];
			cout << keywords[i] << ", ";
		}
		fwrite << "\n";
		cout << endl;

		cout << "Identifier :";
		fwrite << "Identifier: ";
		for (int i = 0; i < ids.size(); i++)
		{
			fwrite << ids[i];
			cout << ids[i] << ", ";
		}
		fwrite << "\n";

		fread.close();
		fwrite.close();
		return 0;
}