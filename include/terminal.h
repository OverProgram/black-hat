//
// Created by tomer on 28/06/2020.
//

#ifndef BLACKHAT_TERMINAL_H
#define BLACKHAT_TERMINAL_H

#include <gtkmm/widget.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#include <cairo.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <lua.hpp>

#include <vector>
#include <functional>
#include <stack>

struct Color {
    float r, g, b;
};

struct TerminalChar {
    char character;
    Color bg, fg;
};

class Program;

class TerminalWidget : public Gtk::Widget {
public:
    TerminalWidget(const std::string& program_path, int width, int height, int font_width = 8, int font_height = 16);
    ~TerminalWidget() override;

    void add_rows(int rows = 1);
//    void execute(Program program);
    void put_char(TerminalChar tchar, int x, int y);
    void register_keypress(int program_id, const std::string& func_name);

protected:
    struct KeypressHandler {
        int program_id;
        std::string func_name;
    };

    void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const override;
    void get_preferred_height_for_width_vfunc(int assigned_width, int& minimum_height, int& natural_height) const  override;
    void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const override;
    void get_preferred_width_for_height_vfunc(int assigned_height, int& minimum_width, int& natural_width) const override;
    void on_size_allocate(Gtk::Allocation& allocation) override;
    void on_realize() override;
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    bool on_key_press_event(GdkEventKey* key_event) override;

    Glib::RefPtr<Gdk::Window> refWindow;

    std::vector<TerminalChar> screen_buffer;

    int width, height, font_width, font_height;

    FT_Library ft_lib;
    FT_Face terminal_face;
    Cairo::RefPtr<Cairo::FtFontFace> terminal_font;

    std::vector<std::shared_ptr<Program>> programs;

    std::stack<KeypressHandler> keypress_handler_stack;
};

#endif //BLACKHAT_TERMINAL_H
