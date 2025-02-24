#include "events.h"

GtkCssProvider *css_provider = NULL;

void init_css() {
    css_provider = gtk_css_provider_new();

    char *css_path = g_build_filename(g_get_user_data_dir(), APP_NAME, "resources/style.css", NULL);
    gtk_css_provider_load_from_path(css_provider, css_path, NULL);
    g_free(css_path);
}

gboolean on_button_press(GtkWidget *widget, const GdkEventButton *event, GtkWindow *window) {
    if (event->type == GDK_BUTTON_PRESS && event->button == 1) {
        gtk_window_begin_move_drag(window, event->button, (gint) event->x_root, (gint) event->y_root, event->time);
        return TRUE;
    }
    return FALSE;
}

gboolean on_key_press(GtkWidget *widget, const GdkEventKey *event, gpointer data) {
    if (event->keyval == GDK_KEY_Escape) {
        gtk_main_quit();
        return TRUE;
    }
    return FALSE;
}

void apply_styles(const int count, ...) {
    va_list args;
    va_start(args, count);

    for (int i = 0; i < count; i++) {
        GtkWidget *widget = va_arg(args, GtkWidget*);
        gtk_style_context_add_provider(
            gtk_widget_get_style_context(widget),
            GTK_STYLE_PROVIDER(css_provider),
            GTK_STYLE_PROVIDER_PRIORITY_USER
        );
    }

    va_end(args);
}

gboolean on_enter_notify(GtkWidget *widget, GdkEventCrossing *event, gpointer data) {
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_add_class(context, "hover");
    return FALSE;
}

gboolean on_leave_notify(GtkWidget *widget, GdkEventCrossing *event, gpointer data) {
    GtkStyleContext *context = gtk_widget_get_style_context(widget);
    gtk_style_context_remove_class(context, "hover");
    return FALSE;
}

gboolean on_delete_press(GtkWidget *widget, const GdkEventButton *event, GtkWindow *scroll_box) {
    if (event->type == GDK_2BUTTON_PRESS && event->button == 1) {
        gtk_container_remove(GTK_CONTAINER(scroll_box), GTK_WIDGET(g_object_get_data(G_OBJECT(widget), "buffer")));
        //todo удаление из файла
        return TRUE;
    }
    return FALSE;
}
