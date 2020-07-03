//
// Created by tomer on 29/06/2020.
//

#ifndef BLACKHAT_PROGRAM_H
#define BLACKHAT_PROGRAM_H

#include <lua.hpp>

#include <string>

#include "terminal.h"


class Program {
public:
    Program(const std::string& program_path, TerminalWidget* parent, int id);
    ~Program();

    void on_keypress(const std::string& func_name, char key);
    bool start();

protected:
    lua_State *L;
    TerminalWidget *parent;

    int id;

//    std::string keypress_func;

    typedef int (Program::*memfunc)(lua_State *L);
    template <memfunc func>
    static int lua_dispatch(lua_State *L);

    static void set_libs(lua_State *L);
    template <memfunc func>
    static void set_field(lua_State *L, const std::string& key);

    constexpr static const luaL_Reg loaded_libs[] = {
            {LUA_TABLIBNAME, luaopen_table},
            {LUA_STRLIBNAME, luaopen_string},
            {LUA_MATHLIBNAME, luaopen_math},
            {LUA_UTF8LIBNAME, luaopen_utf8},
            {nullptr, nullptr}
    };

    int put_char(lua_State* L);
    int add_rows(lua_State* L);
    int register_keypress(lua_State *L);
    int get_size(lua_State* L);
};


#endif //BLACKHAT_PROGRAM_H
