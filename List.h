#pragma once
#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include"csv.h"
#include"file.h"
//#include"PhoneApp.h"


using namespace std;
using namespace csv;
using namespace files;

ReadStatus rstat;
string toLower(string str)
{
	for (int i = 0; i < str.length(); i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {        // If the character is Uppercase
			str[i] = ((char)(str[i] - 'A' + 'a'));   // Conversion from uppercase to lowercase, update character value
		}
	}
	return str;
}
//vector<int> string_to_vector(const string& str, char delimiter) { 
//	vector<int> result;
//	stringstream ss(str);
//	string token;
//	while (getline(ss, token, delimiter)) {
//		result.push_back(stoi(token));
//	}
//	return result;
//}
class ListOfStudents
{
private:
	vector<Contact> listOf�ontacts;
public:
	ListOfStudents() {};
	void init() //initialize list from file
	{
		fstream initf("list.dat", ios::in | ios::out | ios::app);
		initf.seekp(0, ios::end);
		int size = initf.tellp();
		if (size != 0)
		{
			initf.read((char*)&listOf�ontacts, sizeof(listOf�ontacts)); //size using tellg()
		}
	}
	void addContact(Contact& cntc)
	{
		
		
	}
};