#include "luafun.h"


int getData(lua_State *L)
{
    return 1;
}

int setData(lua_State *L)
{
    return 0;
}
int switchWindow(lua_State *L)
{
    return 0;
}
int printl(lua_State *L)
{
    return 0;
}
lua_State *openLua()
{
    lua_State *L = luaL_newstate();
    luaopen_base(L);    //调用print使用
    luaL_setfuncs(L, luaLib, 0);    //注册库函数
}

void closeLua(lua_State *L)
{
    lua_close(L);
}
