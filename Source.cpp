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
#include <cstdlib>
#include <regex>
using namespace std;
using namespace csv;
using namespace files;

//this will check if user created  and on this basis willopen either login or signin
int PasswordSet()
{
	string passwd;
	fstream shadowF("shadow", ios::in);
	getline(shadowF, passwd);
	if (passwd == "")
	{
		return 1; //make ui read this. So if passwd (password) is empty - open sign in
	}
	return 0; //if not empty - open log in
}

void signIn()
{
	string username,passwd, cpasswd;
	cout << "Please enter a username." << endl;
	cout << "It can contain upper and lower case letter, numbers, and underscores only: ";
	//check this  validation Aziz
	while (true)
	{
		cin>> username;
		regex pattern("(\\w+)?");

		if (regex_match(username, pattern)) {
			cout << "Correct username!" << endl;
			break;
		}
		cout << "Incorrect!Try again" << endl;
	}
	//setting passwd
	
	while (true)
	{
		cout << "Please input password, length should be at least 6 symbols: ";
		cin >> passwd;
		if (passwd.length() >= 6)
		{
				cout << "Confirm password: ";
				cin >> cpasswd;
				if (passwd==cpasswd)
				{
					cout << "Password set succesfully!" << endl;
					break;
				}
				cout << "Passwords do not match!" << endl;
		}
		cout << "Incorrect!Try again" << endl;
	}
	fstream shadowF("shadow", ios::out | ios::trunc); //file to store password in "protected" way
	fstream passwdF("passwd", ios::out | ios::trunc); //file to store username
	//files are replicating /etc/shadow and /etc/passwd
	shadowF << mask(passwd, "shadow");
	passwdF << username;
	shadowF.close();
	passwdF.close();
}

int logIn()
{
	string passwd, username, cpasswd, cusername;
	fstream shadowF("shadow", ios::in);
	fstream passwdF("passwd", ios::in);
	getline(shadowF, cpasswd); //getting userna,e and password from files
	getline(passwdF, cusername);
	cout << "Wellcome!" << endl;
	for (int i = 0; i < 3; i++) //we will give 3 attemps for log in, to avoid bruteforce
	{
	cout << "Login:";
	cin >> username;
	cout << "Password: ";
	cin >> passwd;
	if ((mask(passwd, "shadow") == cpasswd) && (username == cusername))
	{
		cout << "Successful login!" << endl;
		shadowF.close();
		passwdF.close();
		return 0; //on successful login

	}
	cout << "Incorrect credentials!" << endl; //I do not specify what is wrong for more safety
	}
	cout << "Closing app..." << endl;
	shadowF.close();
	passwdF.close();
	return 1; //after 3 unseccesful logins close app
}


//add with insertion sort. To be used in listofContacts
void add(string added, vector<string> strArr)
{
	strArr.push_back(added);
	int i = strArr.size()-1;
	while(i>0)
	{

		if (toLower(strArr[i]) < toLower(strArr[i-1]))
		{
			swap(strArr[i], strArr[i - 1]);
		}
		i--;
	}
}

int Contact::counter = 0;
int main()
{
	if (PasswordSet() == 1)
	{
		signIn();
		return 0;
	}
	logIn();
//	mask(mask("Sarvar", "bazarov"),"bazarov");
	return 0;
}