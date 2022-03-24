extern "C" {
#include <Lua.5.2.0/src/lua.h>
#include <Lua.5.2.0/src/lualib.h>
#include <Lua.5.2.0/src/lauxlib.h>
}


#include <memory>
#include <iostream>

#include <LuaBridge/LuaBridge.h>



void report_errors(lua_State* luastate, int status) {
	if (status == 0) {
		return;
	}

	std::cerr << "[lua error] " << lua_tostring(luastate, -1) << std::endl;

	// remove error message from lua state
	lua_pop(luastate, 1);
}

int main() {
	// create a lua state
	lua_State* luastate = luaL_newstate();

	// load standard libs
	luaL_openlibs(luastate);

	// load some code from lua file
	int scriptloadstatus = luaL_dofile(luastate, "LUABRIDGE/Example.lua");

	// define error reporter for any lua error
	report_errors(luastate, scriptloadstatus);

	// call function defined in lua script
	luabridge::LuaRef addanddouble = luabridge::getGlobal(luastate, "addAndDouble");

	int x = addanddouble(15, 12);

	std::cout << "[evaluate lua] (15 + 12) * 2 = " << x << std::endl;

	return 0;
}