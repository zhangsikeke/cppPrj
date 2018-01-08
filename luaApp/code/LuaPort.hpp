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
		//�ж����Ԫ���Ƿ���ڣ����������lua���ͷ�һ��nil��ջ��
		luaL_getmetatable(L,getClsMetaName().c_str());
		bool ret=!lua_isnil(L,-1);
		lua_pop(L,1);
		return ret;
	}
	//ע��c++��
	static void regCls(lua_State* L)
	{
		//userDa��metabtale(userData��Ԫ��)
		luaL_newmetatable(L,getUdMetaName().c_str());
		//����userData����������table['__gc']=LuaPort::dtor
		lua_pushstring(L,"__gc");
		lua_pushcfunction(L,&LuaPort::dtor);
		lua_settable(L,-3);
		lua_pop(L,1);

		//lua���metable metable._index=metable
		luaL_newmetatable(L,getClsMetaName().c_str());
		lua_pushstring(L,"__index");
		lua_pushvalue(L,-2);
		lua_settable(L,-3);

		//ע���Ա����
		for(int i=0;T::functions_[i].funcName_;i++)
		{
			lua_pushstring(L,T::functions_[i].funcName_);
			lua_pushnumber(L,i);
			lua_pushcclosure(L,&LuaPort<T>::proxy,1);
			lua_settable(L,-3);
		}
		lua_pop(L,1);
	}

	//ע��c++ʵ����Ϊlua�е�ȫ�ֱ�����lua�����ͷţ�������regCls֮�����
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
		//Ҫ���ص�lua����
		lua_newtable(L);
		if(free_by_lua)
		{
			//��lua�ͷŵ�����£����ú�full userdata֮��󶨺�Ԫ��
			T** pp=(T**)lua_newuserdata(L,sizeof(T*));
			if(pp==NULL)
			{
				throw "no memory availibe!";
			}
			*pp=inst;
			//����metable��Ϊ����ȷ��gc c++����
			luaL_getmetatable(L,getUdMetaName().c_str());
			lua_setmetatable(L,-2);
		}
		else
		{
			//��lua�ͷţ�����light-userdata
			lua_pushlightuserdata(L,inst);
		}

		//�����ڲ�c++����
		lua_pushnumber(L,0);
		lua_insert(L,-2);
		lua_settable(L,-3);

		//������Ԫ��
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
