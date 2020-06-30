//
// Created by tomer on 28/06/2020.
//
#include "black_hat.h"
#include <gtkmm/messagedialog.h>

BlackHat::BlackHat() {
    set_border_width(10);
    terminal = new TerminalWidget("/home/tomer/BlackHat/resources/lua/bash.lua", 16, 16);
    add(*terminal);
    terminal->show();
}

BlackHat::~BlackHat() = default;

void BlackHat::on_button_click() {
    Gtk::MessageDialog dialog(*this, "Hello, world!");
    dialog.run();
}
