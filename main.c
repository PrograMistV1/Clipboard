#include <gtk/gtk.h>

#include "events.h"
#include "window.h"

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    init_css();

    GtkWindow *window = create_main_window();

    gtk_widget_show_all(GTK_WIDGET(window));
    add_buffer();
    gtk_main();
    return 0;
}
