#ifndef EVENTS_H
#define EVENTS_H

#include <gtk/gtk.h>

extern GtkCssProvider *css_provider;

void init_css();

gboolean on_button_press(GtkWidget *widget, const GdkEventButton *event, GtkWindow *window);

gboolean on_key_press(GtkWidget *widget, const GdkEventKey *event, gpointer data);

void apply_styles(int count, ...);

gboolean on_enter_notify(GtkWidget *widget, GdkEventCrossing *event, gpointer data);

gboolean on_leave_notify(GtkWidget *widget, GdkEventCrossing *event, gpointer data);

gboolean on_delete_press(GtkWidget *widget, const GdkEventButton *event, GtkWindow *scroll_box);

#endif
