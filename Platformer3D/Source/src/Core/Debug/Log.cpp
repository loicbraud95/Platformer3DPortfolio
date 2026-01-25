#include "Log.h"

Log* Log::instance = nullptr;

Log::Log(const char* fileName)
{
	OpenFile(fileName);
}

Log& Log::Get()
{
	if (instance == nullptr)
		instance = new Log("debug.txt");
	return *instance;
}

void Log::Destroy()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

Log::~Log()
{
	CloseFile();
}

void Log::OpenFile(const char*& fileName)
{
	fileOpen.open(fileName, std::ofstream::out | std::ofstream::trunc);

	if (!fileOpen.is_open())
	{
		Print("unknow file");
	}
}

bool CheckPrintArg(const char c)
{
	if (c == 'd' || c == 'f')
	{
		return true;
	}
	else
		return false;
}

std::string Log::Print(const std::string format, ...)
{
	va_list params;
	va_start(params, format);
	std::string txt = Print(format, params);
	va_end(params);

	return txt;
}

std::string Log::Print(const std::string format, va_list params)
{
	std::string txt = StrReorganization(format, params);

	std::cout << txt << std::endl;
	if (fileOpen.is_open())
		fileOpen << txt + "\n";

	return txt;
}

std::string Log::StrReorganization(const std::string format, va_list params)
{
	int nbValue = 0;
	std::string result = "";
	for (int i = 0; i < format.length(); ++i)
	{
		if (format[i] == '%' && i != format.length() - 1)
		{
			char c = format[i + 1];
			if (CheckPrintArg(c))
			{
				++nbValue;

				if (c == 'd')
				{
					result += std::to_string(va_arg(params, int));
				}
				else if (c == 'f')
				{
					result += std::to_string(va_arg(params, double));
				}

				++i;
			}
			else
			{
				std::cout << "error type arg : %" << c << std::endl;
				break;
			}
		}
		else
		{
			result += format[i];
		}
	}

	return result;
}

void Log::CloseFile()
{
	if (fileOpen.is_open())
	{
		fileOpen.close();
	}
}

void Debug_Log(std::string text, std::string FileName, int line, ...)
{
	va_list args;
	va_start(args, line);

	text = FileName + "(" + std::to_string(line) + "): " + text + "\n";
	text = Log::Get().Print(text, args);
	va_end(args);
	OutputDebugStringA(text.c_str());
}
