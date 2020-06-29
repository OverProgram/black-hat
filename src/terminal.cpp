//
// Created by tomer on 28/06/2020.
//
#include "terminal.h"

#include <string>

//template <memfunc F>
//int lua_dispatch(lua_State* l) {
//    TerminalWidget *ptr = *static_cast<TerminalWidget**>(lua_getextraspace(l));
//    return ((*ptr).*F)(l);
//}

TerminalWidget::TerminalWidget(int width, int height, int font_width, int font_height) : Glib::ObjectBase("terminal"), Gtk::Widget(),
screen_buffer(width * height), width(width), height(height), font_width(font_width), font_height(font_height), refWindow(nullptr),
ft_lib(), terminal_face(), terminal_font(), l(luaL_newstate()) {
    set_has_window(true);
    set_name("terminal");
    FT_Init_FreeType(&ft_lib);
    FT_New_Face(ft_lib, "/home/tomer/BlackHat/resources/Perfect DOS VGA 437.ttf", 0, &terminal_face);
    FT_Set_Pixel_Sizes(terminal_face, font_width, font_height);
    terminal_font = Cairo::FtFontFace::create(terminal_face, 0);
    luaL_openlibs(l);
    *static_cast<TerminalWidget**>(lua_getextraspace(l)) = this;
}

void TerminalWidget::get_preferred_width_vfunc(int &minimum_width, int &natural_width) const {
    minimum_width = width * font_width;
    natural_width = (width + 2) * font_width;
}

void TerminalWidget::get_preferred_height_vfunc(int &minimum_height, int &natural_height) const {
    minimum_height = height * font_height;
    natural_height = (height + 1) * font_height;
}

void TerminalWidget::get_preferred_height_for_width_vfunc(int assigned_width, int &minimum_height, int &natural_height) const {
    float aspect_ratio = (float)(width) / (float)(height);
    minimum_height = (int)((float)(assigned_width) / aspect_ratio);
    natural_height = (int)((float)(assigned_width) / aspect_ratio);
}

void TerminalWidget::get_preferred_width_for_height_vfunc(int assigned_height, int &minimum_width, int &natural_width) const {
    float aspect_ratio = (float)(width) / (float)(assigned_height);
    minimum_width = (int)(aspect_ratio * (float)(assigned_height));
    natural_width = (int)(aspect_ratio * (float)(assigned_height));
}

void TerminalWidget::on_size_allocate(Gtk::Allocation &allocation) {
    set_allocation(allocation);

    if (refWindow) {
        refWindow->move_resize(allocation.get_x(), allocation.get_y(), allocation.get_width(), allocation.get_height());
    }
}

void TerminalWidget::on_realize() {
    Widget::on_realize();

    if (!refWindow) {
        GdkWindowAttr attributes = {};
        auto allocation = get_allocation();

        attributes.x = allocation.get_x();
        attributes.y = allocation.get_y();
        attributes.height = allocation.get_height();
        attributes.width = allocation.get_width();

        attributes.event_mask = get_events() | Gdk::EXPOSURE_MASK;
        attributes.window_type = GDK_WINDOW_CHILD;
        attributes.wclass = GDK_INPUT_OUTPUT;

        refWindow = Gdk::Window::create(get_parent_window(), &attributes, GDK_WA_X | GDK_WA_Y);
        set_window(refWindow);

        refWindow->set_user_data(gobj());
    }
}

bool TerminalWidget::on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
    const Gtk::Allocation allocation = get_allocation();
    cr->set_font_face(terminal_font);

    for (int y = 0; y < this->height; y++) {
        int loc_y = y * font_height;
        for (int x = 0; x < this->width; x++) {
            int index = y * this->width + x;
            int loc_x = x * font_width;
            TerminalChar tchar = screen_buffer[index];
            cr->move_to(loc_x, loc_y);
            cr->set_source_rgb(tchar.bg.r, tchar.bg.g, tchar.bg.b);
            cr->rectangle(loc_x, loc_y, font_width, font_height);
            cr->set_source_rgb(tchar.fg.r, tchar.fg.g, tchar.fg.b);
            cr->show_text(std::string(tchar.character, 1));
        }
    }

    cr->stroke();
    return true;
}

void TerminalWidget::add_rows(int rows) {
    screen_buffer.resize(screen_buffer.size() + rows);
}

TerminalWidget::~TerminalWidget() = default;
