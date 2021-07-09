#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include <math.h>
#include <stdio.h>

static int my_math_sin(lua_State *L){
    double d = lua_tonumber(L,1);
    lua_pushnumber(L, sin(d));
    return 1;
}

static int my_math_cos(lua_State *L){
    double d = lua_tonumber(L,1);
    lua_pushnumber(L, cos(d));
    return 1;
}

static const luaL_Reg mylib[] = {
{"my_cos",   my_math_cos},
{"my_sin",   my_math_sin},
{NULL, NULL}
};

extern int luaopen_math_lib(lua_State* L)
{
    /* void luaL_newlib (lua_State *L, const luaL_Reg l[]);
     * 创建一个新的"table"，并将"l"中所列出的函数注册为"table"的域。
     */ 
    luaL_newlib(L, mylib);

    return 1;
}