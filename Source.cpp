#include<vector>
#include<string>
#include<iostream>
#include"csv.h"
#include"file.h"
#include"PhoneApp3.h"
//#include"Header.h"
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

vector<string> kek = { "Abbos" };

void add(string added)
{
	kek.push_back(added);
	for (auto i = kek.rbegin(); i > kek.rend(); i++)
	{

	}
}

int Contact::counter = 0;
int main()
{
	//PhoneNumber tt;
	//string lolll;
	//vector<PhoneNumber> listOfNumbers;
	//for (int i = 0; i < 3; i++)
	//{
	//	cin >> lolll;
	//	tt.setNumber(lolll);
	//	listOfNumbers.push_back(tt);
	//}

	//for (auto& i : listOfNumbers)
	//{
	//	cout << i;
	//}
/*	Contact abc, cbae, edca;
	vector<Contact> loConts;
	loConts.push_back(abc);
	loConts.push_back(cbae);
	loConts.push_back(edca);
	for (auto i = loConts.rbegin(); i < loConts.rend(); i++)
	{
		cout << (* i).getID() << endl;
	}*/
		
	// , "Sarvar Bazarov", "ALen 007", "Amirchik", "Mama"};
	

	return 0;
}