#include "LuaAdapter.hpp"
#include "CommonUtil.hpp"
#include "Log.hpp"
namespace LuaAdapter
{
void loadAllLuaScript(lua_State *L,const std::string filePath)
{
	std::vector<std::string> fileList;
	util::findAllExtFile(filePath,"*.lua",fileList);
	std::vector<std::string>::iterator it=fileList.begin();
	for (it;it!=fileList.end();it++)
	{
		int result=luaL_dofile(L,(*it).c_str());//执行脚本;
		if(result!=0)
		{
			const char* c=lua_tostring(L,-1);//若没执行成功，获取异常信息
			COMMON_TRACE("[ERROR]:excute "<<*it<< " faild: "<<c);
		}
		else
		{
			COMMON_TRACE("[INFO]:load file "<<*it);
		}
		
	}

	int bgc=lua_gc(L,LUA_GCCOUNT,0);
	lua_gc(L,LUA_GCCOLLECT,0);
	int agc=lua_gc(L,LUA_GCCOUNT,0);;
	COMMON_TRACE("[INFO]:before gc:"<<bgc<<"KB")
	COMMON_TRACE("[INFO]:after gc:"<<agc<<"KB")
}
void callALuaFunction(lua_State *L,char *moduleName,char *funcName)
{
	/*int result=luaL_dofile(L,filePath);//执行脚本;
	if(result!=0)
	{
		const char* c=lua_tostring(L,-1);//若没执行成功，获取异常信息
		TRACE("error! excute "<<filePath<< " faild: "<<c);
	}*/

	lua_getglobal(L,moduleName);//拿到全局变量压入栈
	if(lua_istable(L,-1))
	{
		lua_getfield(L,-1,funcName);
		lua_pcall(L,0,0,0);
	}
	else
	{
		lua_getglobal(L,funcName);
		lua_pcall(L,0,0,0);
	}
}
}
