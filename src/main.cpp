#include <gtkmm.h>
#include "black_hat.h"

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "com.blackhat.blackhat");

    BlackHat blackHat;

    return app->run(blackHat);
}
