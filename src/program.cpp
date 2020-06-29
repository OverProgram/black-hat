//
// Created by tomer on 29/06/2020.
//
#include "program.h"

#include <iostream>

typedef int (Program::*memfunc)(lua_State *L);

Program::Program(const std::string& program_path, TerminalWidget* parent) : parent(parent), L(luaL_newstate()) {
    luaL_openlibs(L);
    *static_cast<Program**>(lua_getextraspace(L)) = this;
    luaL_dofile(L, program_path.c_str());
}

template<memfunc func>
int Program::lua_dispatch(lua_State *L) {
    Program *ptr = *static_cast<Program**>(lua_getextraspace(L));
    return ((*ptr).*func)(L);
}

Program::~Program() {
    lua_close(L);
}

void Program::on_keypress(char key) {
    lua_getglobal(L, "on_keypress");
    if (!lua_isfunction(L, -1)) {
        return;
    }

    lua_pushstring(L, &key);
    if (lua_pcall(L, 1, 0, 0) != 0) {
        std::cerr << "Invalid on_keypress function!" << std::endl;
    }
}
