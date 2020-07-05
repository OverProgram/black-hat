//
// Created by tomer on 29/06/2020.
//

#ifndef BLACKHAT_PROGRAM_H
#define BLACKHAT_PROGRAM_H

#include <lua.hpp>

#include <string>

#include "terminal.h"
#include "bh_inst.h"

class BHInstance;
class TerminalWidget;

class Program {
public:
    Program(const std::string& program_path, std::shared_ptr<BHInstance> parent, int parent_handle, int id);
    ~Program();

    void on_keypress(const std::string& func_name, char key);

    bool start();
    bool call_func(const std::string& func_name);

protected:
    lua_State *L;
    std::shared_ptr<TerminalWidget> parent_terminal;
    std::shared_ptr<BHInstance> parent;


    int id;

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
