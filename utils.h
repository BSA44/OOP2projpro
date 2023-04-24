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
	for (int i = 0; i < 100; i++)
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

int signIn()
{

}

int login()
{

}