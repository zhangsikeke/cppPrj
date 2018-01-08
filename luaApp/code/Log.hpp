#pragma once
#ifndef _LOG_
#define _LOG_
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#define COMMON_TRACE(msg) \
	do\
	{\
	std::ostringstream os;\
	os<<msg;\
	LOG(os.str());\
	}while(0);

class Log
{
private:
	std::ofstream out;
	std::string logPath;
public:
	Log();
	~Log();
	void init(const std::string &logPath);
	void log(const std::string &str);
};
extern void initLog(const std::string &logPaht);
extern void LOG(const std::string &str);
#endif