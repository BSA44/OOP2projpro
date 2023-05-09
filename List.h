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
		}


		ReadStatus prstat;
		readFile("./data/.psw", prstat);
		if (prstat == ReadStatus::ERROR)
		{
			WriteStatus pwstat;
			writeFile("./data/.psw", "12345", pwstat);
		}

		if (rstat == ReadStatus::ERROR) return;

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

	void updateContact(string oldID, Contact& newData)
	{
		getContactByID(oldID) = newData;
		int i = listOf—ontacts.size() - 1;
		while (i > 0)
		{

			if (toLower(listOf—ontacts[i].getDisplayName()) < toLower(listOf—ontacts[i - 1].getDisplayName()))
			{
				swap(listOf—ontacts[i], listOf—ontacts[i - 1]);
			}
			i--;
		}
		WriteStatus cwstat;
		writeFile("./data/" + oldID, mask(csv::convert(toCSV(getContactByID(oldID))), password), cwstat);
	}

	void createContact(Contact contact) // only contact data matters, id will be modified
	{
		this->count++;
		contact.setID(to_string(count));
		ReadStatus rstat;
		csv::csv_t initdata = csv::parse(mask(readFile("./data/.init", rstat), password));
		initdata[0][0] = to_string(this->count);
		if (initdata.size() == 1) initdata.resize(2);
		initdata[1].push_back(contact.getID());
		WriteStatus iwstat;
		writeFile("./data/.init", mask(csv::convert(initdata), password), iwstat);
		WriteStatus cwstat;
		writeFile("./data/" + contact.getID(), mask(csv::convert(toCSV(contact)), password), cwstat);
		addContact(contact);
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

	vector<Contact>& getVector()
	{
		return listOf—ontacts;
	}

	vector<string> search(string searched)
	{
		searched = toLower(searched);
		vector<string> candidateList;
		for (int i=0; i < listOf—ontacts.size(); i++)
		{
			if (toLower(listOf—ontacts[i].getDisplayName()).find(searched) != std::string::npos)
			{
				candidateList.push_back(listOf—ontacts[i].getID());
			}
		}
		for (int i = 0; i < listOf—ontacts.size(); i++)
		{
			for (int ii = 0; ii < listOf—ontacts[i].phoneNumbersCount(); ii++)
			{
				if (listOf—ontacts[i].getPhoneNumByID(ii).getNumber().find(searched) != std::string::npos)
				{
					bool alreadyAdded = false;
					for (int iii = 0; iii < candidateList.size(); iii++)
					{
						if (candidateList[iii] == listOf—ontacts[i].getID())
						{
							alreadyAdded = true;
							break;
						}
					}
					if (!alreadyAdded) candidateList.push_back(listOf—ontacts[i].getID());
				}
			}
		}
		return candidateList;
	}

	Contact& getContactByIndex(int i)
	{
		return listOf—ontacts[i];
	}

	int length()
	{
		return listOf—ontacts.size();
	}

	bool numberExists(string number)
	{
		for (auto& cont : listOf—ontacts)
		{
			for (int i = 0; i < cont.phoneNumbersCount(); i++)
			{
				if (cont.getPhoneNumByID(i).getNumber() == number)
				{
					return true;
				}
			}
		}

		return false;
	}

	Contact& getContactByID(string givenID)
	{
		for (auto& i : listOf—ontacts)//for...of cycle, i stores value instead of index
		{
			if (i.getID() == givenID)
			{
				return i;
			}
		}
	}

};