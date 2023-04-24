#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include"csv.h"
#include"file.h"
#include"PhoneApp3.h"
#include"List.h"
#include "utils.h"
#include <sstream>

using namespace std;
using namespace csv;
using namespace files;



//class listOfContacts
//{
//private:
//	Contact* arr = new Contact[100];
//public:
//	Contact getContactByID(int i) //to get contacts from id
//	{
//		return arr[i];
//	}
//	string getContactNameByID(string n, int i)
//	{
//		arr[i].getName();
//	}
//		string getContactNameByID(string n, int i)
//	{
//		arr[i].getName();
//	}
//};
//int Contact::counter = 0;
//vector<int> string_to_vector(const string& str) {
//	vector<int> result;
//	stringstream ss(str);
//	int num;
//	while (ss >> num) {
//		result.push_back(num);
//	}
//	return result;
//}

vector<string> kek; 
//add with insertion sort. To be used in listofContacts
void add(string added)
{
	kek.push_back(added);
	int i = kek.size()-1;
	while(i>0)
	{

		if (toLower(kek[i]) < toLower(kek[i-1]))
		{
			swap(kek[i], kek[i - 1]);
		}
		i--;
	}
}

int Contact::counter = 0;
int main()
{
	mask(mask("Sarvar", "bazarov"),"bazarov");
	return 0;
}