#include "OpenTestItf.hpp"
#include <string>
#pragma comment(lib,"../lib/lua5.3.1.lib")
int main()
{
	::std::string logPath("log.log");
	::std::string luaPath("luaScripts");
	main_Itf(luaPath,logPath);
	return 0;
}