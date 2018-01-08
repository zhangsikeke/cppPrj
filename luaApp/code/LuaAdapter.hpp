#ifndef _LUAADAPTER_
#define _LUAADAPTER_
#include <string>
#include "luaAPI.hpp"
namespace LuaAdapter
{
	void loadAllLuaScript(lua_State *L,const std::string filePath);
	void callALuaFunction(lua_State *L,char *moduleName,char *funcName);
}
#endif