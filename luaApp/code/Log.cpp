#include "Log.hpp"
//默认logpath
static std::string defLogPath("log.log");
static Log my_log=Log();
Log::Log()
{
	
}
Log::~Log()
{
	out.close();
}
void Log::init(const std::string &logPath)
{
	this->logPath=logPath;
	if (logPath.empty())
	{
		this->logPath=defLogPath;
		out.open(logPath.c_str(),std::ios::out|std::ios::app);
		log("[warning]:not set log path,the default log path is log.log");
	}
	else
	{
		out.open(logPath.c_str(),std::ios::out|std::ios::app);
		COMMON_TRACE("[INFO]:log path is "<<logPath);
	}
	
}
void Log::log(const std::string &str)
{
	time_t nowtime;
	time (&nowtime);//获取当前时间，存rawtime里
	struct tm * target_time;
	target_time = localtime (&nowtime); 

	std::ostringstream os;
	os<<target_time->tm_year+1900<<"/"
		<<std::setw(2)<<std::setfill('0')<<target_time->tm_mon+1<<"/"
		<<std::setw(2)<<std::setfill('0')<<target_time->tm_mday<<" "
		<<std::setw(2)<<std::setfill('0')<<target_time->tm_hour<<":"
		<<std::setw(2)<<std::setfill('0')<<target_time->tm_min<<":"
		<<std::setw(2)<<std::setfill('0')<<target_time->tm_sec<<"|";
	out<<os.str()<<str<<std::endl;
}
void LOG(const std::string &str)
{
	my_log.log(str);
}
void initLog(const std::string &logPaht)
{
	my_log.init(logPaht);
}

