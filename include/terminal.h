//
// Created by tomer on 28/06/2020.
//

#ifndef BLACKHAT_TERMINAL_H
#define BLACKHAT_TERMINAL_H

#include <gtkmm/widget.h>
#include <gtkmm/window.h>
#include <vector>

struct Color {
    float r, g, b;
};

struct TerminalChar {
    char character;
    Color bg, fg;
};

class TerminalWidget : public Gtk::Widget {
public:
    TerminalWidget(int width, int height, int font_width = 16, int font_height = 8);
    ~TerminalWidget() override;

protected:
    void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const override;
    void get_preferred_height_for_width_vfunc(int assigned_width, int& minimum_height, int& natural_height) const  override;
    void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const override;
    void get_preferred_width_for_height_vfunc(int assigned_height, int& minimum_width, int& natural_width) const override;
    void on_size_allocate(Gtk::Allocation& allocation) override;
    void on_realize() override;
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    Glib::RefPtr<Gdk::Window> refWindow;

    std::vector<TerminalChar> screen_buffer;

    int width, height, font_width, font_height;
};

#endif //BLACKHAT_TERMINAL_H
