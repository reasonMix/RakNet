#pragma once

#ifndef __LUAX_H__
#define __LUAX_H__

#include <string>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
}


std::string checkString(lua_State* L, int idx);


// get opt string field.
// error if field exists but with other (not string nor nil) type.
std::string optStringField(lua_State* L, int idx, const char* field, const char* def);

// check string field.
// error if field not exists or not a string type.
std::string checkStringField(lua_State* L, int idx, const char* field);

// get string filed, convert to string if possiable.
// error if field not exists or can't convert to string.
std::string getStringField(lua_State* L, int idx, const char* field);


// get opt boolean field.
// error if field exists but with other (not boolean nor nil) type.
bool optBooleanField(lua_State* L, int idx, const char* field, bool def);


bool checkBooleanField(lua_State* L, int idx, const char* field);


bool getBooleanField(lua_State* L, int idx, const char* field);


#endif /* __LUAX_H__ */
