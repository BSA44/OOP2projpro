#pragma once
#include <string>
#include<iostream>


using namespace std;

//works!
string mask(string plaintext, string passwd)
{
	string key = "";
	string ciphertext = plaintext; //so the cipher text has the same len
	//generating key, making sure that it is enough long
	if(passwd=="")
	{
		return plaintext;
	}
	for (int i = 0; i < plaintext.length() / passwd.length() + 1; i++)
	{
		key = key + passwd;
	}
	//applying mask
	for (int i = 0; i < plaintext.length(); i++)
	{
		ciphertext[i] = plaintext[i] ^ key[i];
	}
	return ciphertext;
}

bool isBetween(const int min, const int x, const int max)
{
	return ((x >= min) && (x <= max));
}
string validNumber()
{
	string phoneNum;
	do
	{
		cout << "Input phone number: " << endl;
		cin.ignore();
		getline(cin, phoneNum);
		bool allNumber = true;


		for (int i = 0; i < phoneNum.length(); i++)
		{
			if (phoneNum[i] < 48 || phoneNum[i] > 57) // Fix 0 and 9 be out of range
			{
				allNumber = false;
				break;
			}

		}
		if (allNumber)
		{
			return phoneNum;
		}
		cout << "Only numbers allowed! Try again!" << endl;
	} while (true);
}