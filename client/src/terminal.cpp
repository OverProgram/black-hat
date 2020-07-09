//
// Created by tomer on 28/06/2020.
//
#include "terminal.h"
#include "program.h"

#include <string>

TerminalWidget::TerminalWidget(BHInstance* parent_inst, int handle, int width, int height, int font_width, int font_height)
    : Glib::ObjectBase("terminal")
    , Gtk::Widget()
    , screen_buffer(width * height)
    , width(width)
    , height(height)
    , parent_inst(parent_inst)
    , handle(handle)
    , font_width(font_width)
    , font_height(font_height)
    , refWindow(nullptr)
    , ft_lib()
    , terminal_face()
    , terminal_font() {
    set_has_window(true);
    set_name("terminal");
    FT_Init_FreeType(&ft_lib);
    FT_New_Face(ft_lib, "/home/tomer/BlackHat/resources/iv8x16u.bdf", 0, &terminal_face);
    terminal_font = Cairo::FtFontFace::create(terminal_face, 0);

    for (auto & i : screen_buffer) {
        i = std::make_unique<TerminalChar>();
    }

//    programs.push_back(std::make_shared<Program>(program_path, this, 0));
//    programs.back()->start();
//    parent_inst->add_program(program_path, handle);

//    screen_buffer.reserve(100);

    set_can_focus(true);
    grab_focus();
}

void TerminalWidget::run(const std::string& program_path) {
    int new_program_handle = parent_inst->add_program(program_path, handle);
    parent_inst->get_program(new_program_handle)->start();
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
    set_realized();

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
    cr->set_font_face(terminal_font);
    float scale_x = (float)(font_width)/8.0f;
    float scale_y = (float)(font_height)/16.0f;
    auto scale_matrix = Cairo::scaling_matrix(scale_x * 10, scale_y * 10);
    cr->set_font_matrix(scale_matrix);
    double px, py;
    for (int y = 0; y < this->height; y++) {
        int loc_y = y * font_height;
        for (int x = 0; x < this->width; x++) {
            int index = y * this->width + x;
            int loc_x = x * font_width;
            TerminalChar tchar = *screen_buffer[index];
            cr->move_to(loc_x, loc_y);
            cr->set_source_rgb((double)(tchar.bg.r)/255., (double)(tchar.bg.g)/255., (double)(tchar.bg.b)/255.);
            cr->rectangle(loc_x, loc_y, font_width, font_height);
            cr->fill();
            cr->set_source_rgb((double)(tchar.fg.r)/255., (double)(tchar.fg.g)/255., (double)(tchar.fg.b)/255.);
            cr->set_source_rgb(1, 1, 255);
            cr->get_current_point(px, py);
            std::string str(1, tchar.character);
            cr->move_to(loc_x, loc_y + (font_height/2));
            cr->text_path(str);
            cr->fill();
        }
    }

    return true;
}

void TerminalWidget::add_rows(int rows) {
    screen_buffer.reserve(screen_buffer.size() + rows * width);
    for (int i = 0; i < rows * width; i++) {
        screen_buffer.push_back(std::make_unique<TerminalChar>());
    }
    height += rows;
    queue_resize();
}

//void TerminalWidget::execute(Program program) {
//    program_stack.push(program);
//    program.start();
//}

void TerminalWidget::put_char(TerminalChar tchar, int x, int y) {
    int index = y * width + x;
//    auto new_tchar = new TerminalChar(tchar);
    screen_buffer[index] = std::make_unique<TerminalChar>(tchar);
    queue_draw();
}

char TerminalWidget::keyval_to_char(unsigned int keyval) {
    switch(keyval) {
        case GDK_KEY_Return:
            return '\n';
        case GDK_KEY_space:
            return ' ';
        case GDK_KEY_BackSpace:
            return '\b';
        case GDK_KEY_Tab:
            return '\t';
        default:
            return std::string(gdk_keyval_name(keyval))[0];
    }
}

bool TerminalWidget::on_key_press_event(GdkEventKey* key_event) {
    char key = keyval_to_char(key_event->keyval);
    auto handler = keypress_handler_stack.top();
    parent_inst->get_program(handler.program_id)->on_keypress(handler.func_name, key);
    return true;
}

void TerminalWidget::register_keypress(int program_id, const std::string& func_name) {
    KeypressHandler handler{program_id, func_name};
    keypress_handler_stack.push(handler);
}

void TerminalWidget::get_size(int &width_ptr, int &height_ptr) const {
    width_ptr = this->width;
    height_ptr = this->height;
}

TerminalWidget::~TerminalWidget() = default;

TerminalChar::TerminalChar() : character('\0'), fg({255, 2555, 255}), bg({0, 0, 0}) {}
