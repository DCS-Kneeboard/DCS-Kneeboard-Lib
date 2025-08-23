#pragma comment(lib, "lua.lib")

extern "C" {
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}

#include "core.h"

extern "C" int __declspec(dllexport) luaopen_KneeboardLib(lua_State* L) {
    static const luaL_Reg stack[] = {
        { NULL, NULL }
    };
    luaL_register(L, "KneeboardLib", stack);
    return 1;
}