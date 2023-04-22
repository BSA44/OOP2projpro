#pragma once
#include<vector>
#include<string>
#include<iostream>
#include"csv.h"
#include"file.h"
#include"PhoneApp.h"


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
vector<int> string_to_vector(const string& str, char delimiter) { 
	vector<int> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter)) {
		result.push_back(stoi(token));
	}
	return result;
}
class ListOfStudents
{
private:
	vector<int> listOfIDs;
public:
	ListOfStudents()
	{
		listOfIDs={ 0 };
	}
	void init() //initialize list from file
	{
		string IDs = readFile("./core/list.csv", rstat);
		if (rstat != ReadStatus::SUCCESS)
		{
			cout << "Error while reading" << endl;

		}
		else
		{
			listOfIDs = string_to_vector(IDs, ',');
		}
	}
	void addContact(Contact& cntc)
	{
		Contact sample;
		int lenOfIDs = listOfIDs.size();
		listOfIDs.push_back(cntc.getID());
		
	}
};