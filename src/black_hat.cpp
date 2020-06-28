//
// Created by tomer on 28/06/2020.
//
#include "black_hat.h"
#include <gtkmm/messagedialog.h>

BlackHat::BlackHat() : button("Hello world"){
    set_border_width(10);

    button.signal_clicked().connect(sigc::mem_fun(*this, &BlackHat::on_button_click));
    add(button);

    button.show();
}

BlackHat::~BlackHat() = default;

void BlackHat::on_button_click() {
    Gtk::MessageDialog dialog(*this, "Hello, world!");
    dialog.run();
}
