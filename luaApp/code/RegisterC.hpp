#ifndef _REGISTERC_
#define _REGISTERC_
#include "luaAPI.hpp"
#include <string>
int luaLog(lua_State *L);
int findAllFileList(lua_State *L);
void reisterCFunction(lua_State *L);
#endif