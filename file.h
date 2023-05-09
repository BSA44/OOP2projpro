#pragma once

#include<fstream>
#include<string>
#include<vector>

#include <direct.h>

using namespace std;

namespace files
{

	enum class WriteStatus //to control read write status
	{
		SUCCESS = 0,
		ERROR
	};

	void writeFile(string path, string data, WriteStatus& status)
	{
		ofstream file;
		file.open(path.c_str());
		if (!file.is_open())
		{
			status = WriteStatus::ERROR;
			return;
		}
		file << data;
		file.close();
		status = WriteStatus::SUCCESS;
	}

	enum class ReadStatus
	{
		SUCCESS = 0,
		ERROR
	};

	string readFile(string path, ReadStatus& status)
	{
		ifstream file;
		file.open(path.c_str());
		if (!file.is_open())
		{
			status = ReadStatus::ERROR;
			return "";
		}

		file.seekg(0, ios::end);
		int length = 1 + file.tellg();

		file.seekg(ios::beg);
		char* data = new char[length];
		file.getline(data, length, EOF);
		file.close();
		status = ReadStatus::SUCCESS;
		return data;
	}

	void createdir(string path)
	{
		_mkdir(path.c_str());
	}

	void deletedir(string path)
	{
		_rmdir(path.c_str());
	}

	void deletefile(string path)
	{
		remove(path.c_str()); // stdio.h
	}

}
