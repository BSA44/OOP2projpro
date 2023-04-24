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

vector<string> kek; 

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
	vector<string> maxik;// = { 1,23,4,45,5 };
	maxik.reserve(5);
	//PhoneNumber tt;
	//string lolll;
	//vector<PhoneNumber> listOfNumbers;
	//for (int i = 0; i < 3; i++)
	//{
	//	cin >> lolll;
	// 
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
	//
	maxik.push_back("Sarvar Bazarov");
	maxik.push_back("ALen 007");
	maxik.push_back("Amirchik");
	maxik.push_back("mama");
	maxik.push_back("AAron");
	//for (auto& i : kek)
	//{
	//	cout << i << endl;
	//}
	fstream initff("init.dat",ios::in|ios::out| ios::binary|ios::trunc);
	fstream sizee("size.dat", ios::out| ios::binary | ios::trunc);
	initff.write((char*)&maxik, sizeof(maxik));
	//cout << to_string(sizeof(kek)) << endl;
	int size = sizeof(maxik);
	sizee.write((char*)&size, sizeof(int));
	initff.seekg(0, ios::end);
	cout << initff.tellg() << endl;
	initff.close();
	sizee.close();

	size = 1000000;

	sizee.open("size.dat", ios::in | ios::binary);
	initff.open("init.dat", ios::in | ios::binary);
	/*string size;
	getline(sizee, size);
	cout << size << endl;*/

	//maxik.clear();

	sizee.read((char*)&size, sizeof(int));
	cout << size << endl;
	initff.read((char*)&maxik,size);
	cout << maxik[0] << endl;
	initff.close();
	sizee.close();
	
	/*initff.write((char*)&ll, sizeof(ll));
	initff.write((char*)&ll, sizeof(ll));
	initff.close();
	initff.open("init.dat", ios::in | ios::out);
	initff.seekg(0, ios::end);
	ll = "works 2";
	initff.write((char*)&ll, sizeof(ll));*/
	return 0;
}