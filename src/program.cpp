//
// Created by tomer on 29/06/2020.
//
#include "program.h"

#include <iostream>

typedef int (Program::*memfunc)(lua_State *L);

Program::Program(const std::string& program_path, TerminalWidget* parent) : parent(parent), L(luaL_newstate()) {
    luaL_openlibs(L);
    lua_pushcfunction(L, &lua_dispatch<&Program::put_char>);
    lua_setglobal(L, "put_char");
    *static_cast<Program**>(lua_getextraspace(L)) = this;
    if (luaL_dofile(L, program_path.c_str()) != 0) {
        std::cerr << lua_error(L) << std::endl;
    }
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

bool Program::start() {
    lua_getglobal(L, "main");
    if (!lua_isfunction(L, -1)) {
        return false;
    }

    if (lua_pcall(L, 0, 0, 0) != 0) {
        std::cerr << lua_error(L) << std::endl;
        return false;
    }
    return true;
}

int Program::add_rows(lua_State *L) {
    int rows = luaL_checkinteger(L, 1);
    parent->add_rows(rows);
    return 0;
}

int Program::put_char(lua_State *L) {
    char character = *luaL_checkstring(L, 1);
    int x = luaL_checknumber(L, 2);
    int y = luaL_checknumber(L, 3);

    TerminalChar c{character, {0, 0, 0}, {255, 255, 255}};
    parent->put_char(c, x, y);

    return 0;
}
