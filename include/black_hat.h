//
// Created by tomer on 27/06/2020.
//

#ifndef BLACKHAT_BLACK_HAT_H
#define BLACKHAT_BLACK_HAT_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm.h>
#include "program.h"
#include "terminal.h"
#include "bh_inst.h"

class BlackHat : public Gtk::Window {
public:
    BlackHat();
    ~BlackHat() override;

protected:
//    std::shared_ptr<TerminalWidget> terminal;
    Gtk::ScrolledWindow *window;
    BHInstance inst;
};

#endif //BLACKHAT_BLACK_HAT_H
