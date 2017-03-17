#pragma once
#ifndef __LUA_RAKNET_HPP__
#define __LUA_RAKNET_HPP__

#if __cplusplus
extern "C" {
#endif

#include "lua.h"
#include "lauxlib.h"

int luaopen_raknet(lua_State *L);

#if __cplusplus
}
#endif




#endif
