#pragma comment(lib, "lua.lib")

extern "C" {
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}

#include "kneeboard.h"

static int kb_init(lua_State* L) {
    lib_init();
    return 0;
}

static int kb_handshake(lua_State* L) {
    lua_pushboolean(L, lib_handshake());
    return 1;
}

static int kb_send_packet(lua_State* L) {
    const char* message = luaL_checkstring(L, 1);
    lib_send_packet(message);
    return 0;
}

extern "C" int __declspec(dllexport) luaopen_KneeboardLib(lua_State* L) {
    static const luaL_Reg stack[] = {
        { "kb_init", kb_init },
        { "kb_handshake", kb_handshake },
        { "kb_send_packet", kb_send_packet },
        { NULL, NULL }
    };
    luaL_register(L, "KneeboardLib", stack);
    return 1;
}