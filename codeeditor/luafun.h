#ifndef LUAFUN_H
#define LUAFUN_H

#include "lua/lua.hpp"
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
#include <windows.h>
#include <QString>
/*自定义函数区*/
int getData(lua_State *L);
int setData(lua_State *L);
int switchWindow(lua_State *L);
int printl(lua_State *L);
static const struct luaL_Reg luaLib[] =
{
    {"getData", getData},
    {"setData", setData},
    {"switchWindow", switchWindow},
    {"printl", printl},
    {NULL, NULL},
};

/*LUA函数区*/
lua_State *openLua();
void closeLua(lua_State *L);

#endif // LUAFUN_H
