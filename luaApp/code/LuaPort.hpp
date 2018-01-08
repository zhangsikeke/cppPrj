#pragma once
#ifndef _LUAPORT_
#define _LUAPORT_
#include "luaAPI.hpp"
template <typename T>
class LuaPort
{
public:
	static bool clsRegistered(lua_State* L)
	{
		//判断类的元表是否存在，如果不存在lua会释放一个nil到栈顶
		luaL_getmetatable(L,getClsMetaName().c_str());
		bool ret=!lua_isnil(L,-1);
		lua_pop(L,1);
		return ret;
	}
	//注册c++类
	static void regCls(lua_State* L)
	{
		//userDa的metabtale(userData的元表)
		luaL_newmetatable(L,getUdMetaName().c_str());
		//设置userData的垃圾回收table['__gc']=LuaPort::dtor
		lua_pushstring(L,"__gc");
		lua_pushcfunction(L,&LuaPort::dtor);
		lua_settable(L,-3);
		lua_pop(L,1);

		//lua类的metable metable._index=metable
		luaL_newmetatable(L,getClsMetaName().c_str());
		lua_pushstring(L,"__index");
		lua_pushvalue(L,-2);
		lua_settable(L,-3);

		//注册成员函数
		for(int i=0;T::functions_[i].funcName_;i++)
		{
			lua_pushstring(L,T::functions_[i].funcName_);
			lua_pushnumber(L,i);
			lua_pushcclosure(L,&LuaPort<T>::proxy,1);
			lua_settable(L,-3);
		}
		lua_pop(L,1);
	}

	//注册c++实例作为lua中的全局变量由lua负责释放，必需在regCls之后调用
	static void regGlobalInstance(lua_State* L,const std::string &name,T* inst)
	{
		if(inst==NULL)
		{
			return;
		}
		createLuaObj(L,inst);
		lua_setglobal(L,name.c_str());
	}
	static int regReferencedInstance(lua_State* L,T* inst)
	{
		if (inst==NULL)
		{
			return 0;
		}
		return createLuaObj(L,inst,false);
	}
	static int proxy(lua_State* L)
	{
		int n=(int)lua_tonumber(L,lua_upvalueindex(1));
		lua_pushnumber(L,0);
		lua_gettable(L,1);
		if(lua_islightuserdata(L,-1))
		{
			T* p=(T*)lua_touserdata(L,-1);
			if (p==NULL)
			{
				luaL_error(L,"%s","inner c++ obj is NULL");
			}
			lua_remove(L,-1);
			return (p->*(T::functions_[n].func_))(L);
		}
		else
		{
			T** pp=(T**)lua_touserdata(L,-1);
			if (pp!=NULL)
			{
				lua_remove(L,-1);
				return ((*pp)->*(T::functions_[n].func_))(L);
			}
			else
			{
				luaL_error(L,"%s","inner c++ obj is null.");
			}
		}
		return 0;
	}
	static int dtor(lua_State* L)
	{
		T** pp=(T**)luaL_checkudata(L,-1,getUdMetaName().c_str());
		if (pp==NULL)
		{
			return 0;
		}
		delete (*pp);
		return 0;
	}
	static int createLuaObj(lua_State* L,T* inst,bool free_by_lua=true)
	{
		//要返回的lua对象
		lua_newtable(L);
		if(free_by_lua)
		{
			//由lua释放的情况下，设置好full userdata之后绑定好元表
			T** pp=(T**)lua_newuserdata(L,sizeof(T*));
			if(pp==NULL)
			{
				throw "no memory availibe!";
			}
			*pp=inst;
			//设置metable是为了正确的gc c++对象
			luaL_getmetatable(L,getUdMetaName().c_str());
			lua_setmetatable(L,-2);
		}
		else
		{
			//非lua释放，则用light-userdata
			lua_pushlightuserdata(L,inst);
		}

		//保存内部c++对象
		lua_pushnumber(L,0);
		lua_insert(L,-2);
		lua_settable(L,-3);

		//设置类元表
		luaL_getmetatable(L,getClsMetaName().c_str());
		lua_setmetatable(L,-2);
		return 1;
	}
private:
	static const std::string& getUdMetaName()
	{
		static std::string sname=T::luaClsName()+"_Cpp";
		return sname;
	}
	static const std::string& getClsMetaName()
	{
		static std::string sname=T::luaClsName()+"_Lua";
		return sname;
	};
};
#define DECL_FUNC_MAP(cls) \
	public:\
	typedef int (cls::*Func) (lua_State *L);\
struct RegType \
	{\
	const char *funcName_;\
	Func func_;\
};\
	static RegType functions_[];
#define BEGIN_IMPL_FUNC_MAP(cls)\
	cls::RegType cls::functions_[]={
#define FUNC_MAP_ITEM(name,func) \
{name,func},
#define END_IMPL_FUNC_MAP \
{0,0}};

#endif
