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
#include "UI.h"
using namespace std;
using namespace csv;
using namespace files;

//this will check if user created  and on this basis willopen either login or signin


//add with insertion sort. To be used in listofContacts


int ContactsList::count = 0;
int main()
{
	UI ui;
	/*if (PasswordSet() == 1)
	{
		signIn();
		return 0;
	}
	logIn();*/
	ui.start();
	return 0;
}