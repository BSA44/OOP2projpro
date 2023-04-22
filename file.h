#pragma once

#include<fstream>
#include<string>
#include<vector>

#ifdef _WIN32
#include <direct.h>
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
#include <sys/stat.h>
#include <unistd.h>
#endif

using namespace std;

namespace files
{

	enum class WriteStatus
	{
		SUCCESS = 0,
		ERROR
	};

	void writeFile(string path, string data, WriteStatus& status)
	{
		ofstream file;
		file.open(path.c_str(), ios::app);
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
#if defined _WIN32
		_mkdir(path.c_str());
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		mkdir(path.c_str(), S_IFDIR)
#endif
	}

	void deletedir(string path)
	{
#ifdef _WIN32
		_rmdir(path.c_str());
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		rmdir(path.c_str());
#endif
	}

	void deletefile(string path)
	{
		remove(path.c_str()); // stdio.h
	}

}