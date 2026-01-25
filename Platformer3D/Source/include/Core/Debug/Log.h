#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>
#include <stdarg.h>

#include <Windows.h>
#include <fstream>

//#define __FILENAME__ (strrchr(__FILE__, '\') ? strrchr(FILE, '\') + 1 : __FILE__)
#define DEBUG_LOG(txt,...)(Debug_Log(txt,__FILE__, __LINE__,__VA_ARGS__))

class Log
{
public:

	static Log& Get();
	static void Destroy();
	~Log();

	void OpenFile(const char*& filename);
	std::string Print(const std::string format, ...);
	std::string Print(const std::string format, va_list params);

private:

	Log(const char* fileName);
	static Log* instance;

	std::string StrReorganization(const std::string format, va_list params);
	std::fstream fileOpen;
	void CloseFile();
};

void Debug_Log(std::string text, std::string FileName, int line, ...);