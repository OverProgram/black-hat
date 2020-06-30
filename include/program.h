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
    Program(const std::string& program_path, TerminalWidget* parent);
    ~Program();

    void on_keypress(char key);
    bool start();

protected:
    lua_State *L;
    TerminalWidget *parent;

    typedef int (Program::*memfunc)(lua_State *L);
    template <memfunc func>
    static int lua_dispatch(lua_State *L);

    int put_char(lua_State* L);
    int add_rows(lua_State* L);
};


#endif //BLACKHAT_PROGRAM_H
