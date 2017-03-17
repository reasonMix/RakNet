#include "luax.hpp"


std::string optStringField(lua_State* L, int idx, const char* field, const char* def)
{
    lua_getfield(L, idx, field);
    size_t len;
    const char* s = luaL_optlstring(L, -1, def, &len);
    if (s == nullptr)
        luaL_error(L, "requires field '%s' to be a valid string", field);
    std::string r(s, len);
    lua_pop(L, 1);
    return r;
}

std::string checkStringField(lua_State* L, int idx, const char* field)
{
    return optStringField(L, idx, field, nullptr);
}


std::string getStringField(lua_State* L, int idx, const char* field)
{
    lua_getfield(L, idx, field);
    size_t len;
    const char* s = lua_tolstring(L, -1, &len);
    if (s == nullptr)
        luaL_error(L, "requires field '%s' to be a valid string", field);
    std::string r(s, len);
    lua_pop(L, 1);
    return r;
}


bool optBooleanField(lua_State* L, int idx, const char* field, bool def)
{
    lua_getfield(L, idx, field);
    bool v;
    switch(lua_type(L, -1))
    {
        case LUA_TBOOLEAN:
            v = lua_toboolean(L, -1);
            lua_pop(L, 1);
            return v;
        case LUA_TNIL:
            lua_pop(L, 1);
            return def;
        default:
            lua_pop(L, 1);
            luaL_error(L, "expected field '%s' to be a boolean or nil value");
            return false; // luaL_error never returns, so we can go to this line.
    }
}


bool checkBooleanField(lua_State* L, int idx, const char* field)
{
    lua_getfield(L, idx, field);
    luaL_checktype(L, -1, LUA_TBOOLEAN);
    bool v = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return v;
}


bool getBooleanField(lua_State* L, int idx, const char* field)
{
    lua_getfield(L, idx, field);
    bool v = lua_toboolean(L, -1);
    lua_pop(L, 1);
    return v;
}

std::string checkString(lua_State* L, int idx)
{
    size_t len;
    const char* s = luaL_checklstring(L, idx, &len);
    return std::string(s, len);
}
