#pragma once
#include<vector>
#include<string>
#include<iostream>
#include"csv.h"
#include"contact_csv.h"
#include"file.h"
#include"utils.h"
#include"PhoneApp3.h"


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
	static int count;
	vector<Contact> listOf—ontacts;
	string password;
public:
	string getPassword() const
	{
		return password;
	}

	void setPassword(string newValue)
	{
		password = newValue;
	}

	ContactsList() {};
	void init(string password)
	{
		this->password = password;

		ReadStatus rstat;
		csv::csv_t initdata = csv::parse(mask(readFile("./data/.init", rstat), password));

		if (rstat == ReadStatus::ERROR)
		{
			createdir("./data");
			WriteStatus iwstat;
			csv::csv_t empty = { { "0" } };
			writeFile("./data/.init", mask(csv::convert(empty), password), iwstat);
			return;
		}

		this->count = stoi(initdata[0][0]);

		if (this->count == 0)
		{
			return;
		}

		for (int i = 0; i < initdata[1].size(); i++)
		{
			ReadStatus crstat;
			string content = mask(readFile("./data/" + initdata[1][i], crstat), password);
			Contact contact = toContact(csv::parse(content));
			this->addContact(contact);
		}
	}
	void addContact(Contact cntc)
	{
		listOf—ontacts.push_back(cntc);
		int i = listOf—ontacts.size() - 1;
		while (i > 0)
		{

			if (toLower(listOf—ontacts[i].getDisplayName()) < toLower(listOf—ontacts[i - 1].getDisplayName()))
			{
				swap(listOf—ontacts[i], listOf—ontacts[i - 1]);
			}
			i--;
		}
		
	}
	void display() //for debug
	{
		for (int i = 0; i < listOf—ontacts.size(); i++)
		{
			cout << listOf—ontacts[i].getDisplayName() << endl;
		}
	}

	void createContact(Contact contact) // only contact data matters, id will be modified
	{
		this->count++;
		contact.setID(to_string(count));
		ReadStatus rstat;
		csv::csv_t initdata = csv::parse(mask(readFile("./data/.init", rstat), password));
		initdata[0][0] = to_string(this->count);
		initdata[1].push_back(contact.getID());
		WriteStatus iwstat;
		writeFile("./data/.init", mask(csv::convert(initdata), password), iwstat);
		
		WriteStatus cwstat;
		writeFile("./data/" + contact.getID(), mask(csv::convert(toCSV(contact)), password), cwstat);

	}

	void deleteContact(string ID)
	{
		for (int i = 0; i < listOf—ontacts.size(); i++)
		{
			if (listOf—ontacts[i].getID() == ID)
			{
				listOf—ontacts.erase(listOf—ontacts.begin() + i);
				ReadStatus rstat;
				csv::csv_t initdata = csv::parse(mask(readFile("./data/.init", rstat), password));
				for (int j = 0; j < initdata.size(); j++)
				{
					if (initdata[1][j] == ID)
					{
						initdata[1].erase(initdata[1].begin() + j);
					}
				}
				WriteStatus iwstat;
				writeFile("./data/.init", mask(csv::convert(initdata), password), iwstat);
			}
		}
	}

	vector<Contact> searchByName(string searched)
	{
		vector<Contact> candidateList;
		for (int i=0; i < listOf—ontacts.size(); i++)
		{
			if (listOf—ontacts[i].getDisplayName().find(searched) != std::string::npos)
			{
				candidateList.push_back(listOf—ontacts[i]);
			}
		}
		return candidateList;
	}
	vector<Contact> searchByEmail(string searched)
	{
		vector<Contact> candidateList;
		for (int i = 0; i < listOf—ontacts.size(); i++)
		{
			for (int k = 0; k < listOf—ontacts[i].emailsCount(); k++)
			{
				if (listOf—ontacts[i].getEmailByID(k).getstr().find(searched) != std::string::npos)
				{
					candidateList.push_back(listOf—ontacts[i]);
				}
			}
			
		}
		return candidateList;
	}

};