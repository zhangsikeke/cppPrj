#include "RegisterC.hpp"
#include "Log.hpp"
#include <vector>
#include "CommonUtil.hpp"
#include "Log.hpp"

int luaLog(lua_State* L)
{
	const char* c=lua_tostring(L,-1);
	LOG(c);
	return 0;
}

int findAllFileList(lua_State *L)
{
	std::string fileExt(lua_tostring(L,-1));
	std::string filePath(lua_tostring(L,-2));
	lua_pop(L,lua_gettop(L));
	std::vector<std::string> fileList;
	util::findAllExtFile(filePath,fileExt,fileList);
	std::vector<std::string>::iterator it=fileList.begin();
	lua_newtable(L);
	size_t i=1;
	for (it;it!=fileList.end();it++)
	{
		lua_pushnumber(L,i);
		lua_pushfstring(L,(*it).c_str());
		lua_settable(L,-3);
		i++;		
	}
	return 1;
}
 void reisterCFunction(lua_State *L)
{
	lua_getglobal(L,"util");//拿到全局变量压入栈
	if(lua_istable(L,-1))
	{
		lua_pushcfunction(L,luaLog);
		lua_setfield(L,-2,"luaLog");
		lua_pushcfunction(L,findAllFileList);
		lua_setfield(L,-2,"findAllFileList");
		lua_pop(L,lua_gettop(L));
	}
	else
	{
		lua_newtable(L);
		lua_setglobal(L,"util");
		lua_getglobal(L,"util");
		lua_pushcfunction(L,luaLog);
		lua_setfield(L,-2,"luaLog");
		lua_pushcfunction(L,findAllFileList);
		lua_setfield(L,-2,"findAllFileList");
		lua_pop(L,lua_gettop(L));

	}
	
	//注册c函数
	//lua_pushcfunction(L,luaLog);
	//lua_setglobal(L,"lua_log");
	//lua_pop(L,-1);
}