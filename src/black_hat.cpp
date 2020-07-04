//
// Created by tomer on 28/06/2020.
//
#include "black_hat.h"
#include <iostream>

BlackHat::BlackHat() {
    set_border_width(10);
    window = new Gtk::ScrolledWindow(Gtk::Adjustment::create(0, 0, 1), Gtk::Adjustment::create(0, 0, 10));
    terminal = new TerminalWidget("/home/tomer/BlackHat/resources/lua/bash.lua", 8, 8, 16, 32);
    window->add(*terminal);
    add(*window);
    show_all_children();

//    add_events(Gdk::KEY_PRESS_MASK);

    terminal->grab_focus();
}

BlackHat::~BlackHat() = default;
