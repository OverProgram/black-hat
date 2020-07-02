//
// Created by tomer on 28/06/2020.
//
#include "black_hat.h"
#include <gtkmm/messagedialog.h>
#include <iostream>

BlackHat::BlackHat() {
    set_border_width(10);
    terminal = new TerminalWidget("/home/tomer/BlackHat/resources/lua/bash.lua", 50, 22);
    add(*terminal);
    terminal->show();

//    add_events(Gdk::KEY_PRESS_MASK);

    terminal->grab_focus();
}

BlackHat::~BlackHat() = default;
