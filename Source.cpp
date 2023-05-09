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


int ContactsList::count = 0;
int main()
{
	UI ui;
	ui.start();
	return 0;
}