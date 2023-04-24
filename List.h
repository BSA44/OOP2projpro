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
class ContactsList
{
private:
	vector<Contact> listOf—ontacts;
public:
	ContactsList() {};
	void init() //initialize list from file
	{
		
	}
	void addContact(Contact cntc)
	{
		
		
	}
};