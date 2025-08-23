#include "lua/lua.h"
#include "lua/lauxlib.h"

static int foo(lua_State* L) {
    lua_pushinteger(L, 67);
    return 1;
}

extern "C" __declspec(dllexport)
int lua_open_kneeboard(lua_State* L) {
    static const luaL_Reg funcs[] = {
        { "foo", foo },
        { NULL, NULL }
    };
    return 1;
}