#pragma once

#include <stdio.h>
#include <vector>
#include <string>

#include <windows.h> 

class Logger
{
public:
	static Logger* Get();
private:
	Logger() {}
	Logger(const Logger& other) {}
	~Logger() {}
public:
	void Add(const char* msg);
	void FlushToFile();

private:
	std::vector<std::string> m_log;
};

#define OUT_DEBUG_STR(str) OutputDebugStringA(str);

static void OUT_IMPL(const char* msg, const char* type, const char* file, int line, ...)
{
	char buff[1024];
	va_list argptr;
	va_start(argptr, line);
	vsnprintf_s(buff, 1024, msg, argptr);

	// Make short version of file:
	char fileName[128];
	char fileExt[8];
	_splitpath_s(file, NULL, 0, NULL, 0, fileName, 128, fileExt, 8);

	char fullMsg[2048];
	sprintf_s(fullMsg, 2048, "%s(%s%s)(%d): %s \n", type, fileName, fileExt, line, buff);
	OUT_DEBUG_STR(fullMsg);
	va_end(argptr);

	Logger::Get()->Add(fullMsg);
}

#define INFO(msg, ...) OUT_IMPL(msg, "[INFORMATION]", __FILE__, __LINE__,  __VA_ARGS__)
#define WARN(msg, ...) OUT_IMPL(msg, "[WARNING]", __FILE__, __LINE__,  __VA_ARGS__)
#define ERR(msg, ...)  OUT_IMPL(msg, "[ERROR]", __FILE__, __LINE__,  __VA_ARGS__)