//
// Created by tomer on 28/06/2020.
//
#include "black_hat.h"
#include <iostream>

BlackHat::BlackHat() : inst() {
    set_border_width(10);
    window = new Gtk::ScrolledWindow(Gtk::Adjustment::create(0, 0, 1), Gtk::Adjustment::create(0, 0, 10));
    int handle = inst.add_terminal("/home/tomer/BlackHat/resources/lua/bash.lua", 8, 8);
    window->add(*inst.get_terminal(handle));
    add(*window);
    show_all_children();

//    add_events(Gdk::KEY_PRESS_MASK);

    inst.get_terminal(handle)->grab_focus();
}

BlackHat::~BlackHat() = default;
