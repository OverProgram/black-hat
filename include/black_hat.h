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

class BlackHat : public Gtk::Window {
public:
    BlackHat();
    virtual ~BlackHat();

protected:
    TerminalWidget *terminal;
};

#endif //BLACKHAT_BLACK_HAT_H
