#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include"csv.h"
#include"file.h"
#include"PhoneApp3.h"
#include"List.h"
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
	
	/*add("Sarvar Bazarov");
	add("ALen 007");
	add("Amirchik");
	add("mama");
	add("AAron");
	for (auto& i : kek)
	{
		cout << i << endl;
	}*/
	fstream initff("init.dat",ios::out|ios::app);
	string ll = "adagr\n";
	initff.seekg(0, ios::end);
	cout << initff.tellg() << endl;
//	initff.clear();
	initff.write((char*)&ll, sizeof(ll));
	initff.write((char*)&ll, sizeof(ll));
	initff.write((char*)&ll, sizeof(ll));
	initff.write((char*)&ll, sizeof(ll));
	initff.close();
	initff.open("init.dat", ios::in | ios::out);
	initff.seekg(0, ios::end);
	ll = "works 2";
	initff.write((char*)&ll, sizeof(ll));
	return 0;
}