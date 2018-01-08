#ifndef _OPENLUAITF_
#define _OPENLUAITF_
#include <string>
#include "luaAPI.hpp"
#include "LuaPort.hpp"
#include "CommonUtil.hpp"
class OpenLuaItf
{
	DECL_FUNC_MAP(OpenLuaItf)
public:
	OpenLuaItf(){}
	~OpenLuaItf(){}
	int getFileList(lua_State *L)
	{
		::std::string ext(luaL_checkstring(L,-1));
		::std::string path(luaL_checkstring(L,-2));
		lua_pop(L,2);
		::std::vector<::std::string>  fileList;
		util::findAllExtFile(path,ext,fileList);
		lua_newtable(L);
		::std::vector<::std::string>::const_iterator it=fileList.begin();
		long i=1;
		for (it;it!=fileList.end();++it)
		{
			lua_pushnumber(L,i);
			lua_pushstring(L,(*it).c_str());
			lua_settable(L,-3);
			++i;
		}
		return 1;
	}
	static std::string& luaClsName()
	{
		static std::string sname("OpenLuaItf");
		return sname;
	}
	static void regClass(lua_State *L)
	{
		if(LuaPort<OpenLuaItf>::clsRegistered(L))
			return;
		LuaPort<OpenLuaItf>::regCls(L);
		std::auto_ptr<OpenLuaItf> ap(new OpenLuaItf());
		LuaPort<OpenLuaItf>::regGlobalInstance(L,OpenLuaItf::luaClsName(),ap.release());
	}
};
BEGIN_IMPL_FUNC_MAP(OpenLuaItf)
	FUNC_MAP_ITEM("getFileList",&OpenLuaItf::getFileList)
END_IMPL_FUNC_MAP
#endif