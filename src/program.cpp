//
// Created by tomer on 29/06/2020.
//
#include "program.h"

#include <iostream>
#include <utility>

typedef int (Program::*memfunc)(lua_State *L);

Program::Program(const std::string& program_path, std::shared_ptr<BHInstance> parent, int parent_handle, int id) : L(luaL_newstate()), parent(parent), id(id) {
    parent_terminal = parent->get_terminal(parent_handle);
    luaL_openlibs(L);
    set_libs(L);
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
    parent->remove_program(id);
}

void Program::on_keypress(const std::string& func_name, char key) {
    lua_getglobal(L, func_name.c_str());
    if (!lua_isfunction(L, -1)) {
        return;
    }

    lua_pushstring(L, &key);
    if (lua_pcall(L, 1, 0, 0) != 0) {
        std::cerr << "Error on keypress func: " << lua_error(L) << std::endl;
    }
}

bool Program::start() {
//    lua_getglobal(L, "main");
//    if (!lua_isfunction(L, -1)) {
//        return false;
//    }
//
//    if (lua_pcall(L, 0, 0, 0) != 0) {
//        std::cerr << lua_error(L) << std::endl;
//        return false;
//    }
//    return true;
    return call_func("main");
}

int Program::add_rows(lua_State *L) {
    int rows = luaL_checkinteger(L, 1);
    parent_terminal->add_rows(rows);
    return 0;
}

int Program::put_char(lua_State *L) {
    char character = *luaL_checkstring(L, 1);
    int x = luaL_checknumber(L, 2);
    int y = luaL_checknumber(L, 3);

    TerminalChar c;
    c.character = character;
    parent_terminal->put_char(c, x, y);

    return 0;
}

int Program::register_keypress(lua_State *L) {
    std::string func_name(luaL_checkstring(L, 1));

    parent_terminal->register_keypress(id, func_name);

    return 0;
}

void Program::set_libs(lua_State *L) {
    for (const luaL_Reg *lib = loaded_libs; lib->func != nullptr; lib++) {
        luaL_requiref(L, lib->name, lib->func, 1);
        lua_pop(L, 1);
    }
    lua_newtable(L);
    set_field<&Program::put_char>(L, "put_char");
    set_field<&Program::register_keypress>(L, "register_keypress");
    set_field<&Program::get_size>(L, "get_size");
    set_field<&Program::add_rows>(L, "add_rows");
    lua_setglobal(L, "terminal");
}

template <memfunc func>
void Program::set_field(lua_State *L, const std::string& name) {
    lua_pushstring(L, name.c_str());
    lua_pushcfunction(L, &lua_dispatch<func>);
    lua_settable(L, -3);
}

int Program::get_size(lua_State *L) {
    int width, height;
    parent_terminal->get_size(width, height);
    lua_pushnumber(L, width);
    lua_pushnumber(L, height);
    return 2;
}

bool Program::call_func(const std::string& func_name) {
    lua_getglobal(L, func_name.c_str());
    if (!lua_isfunction(L, -1)) {
        return false;
    }
    if (lua_pcall(L, 0, 0, 0) != 0) {
        std::cerr << lua_error(L) << std::endl;
        return false;
    }
    return true;
}
