#include "window.h"
#include "events.h"

GtkWidget *scroll_box;

void add_buffer() {
    char label[300];
    snprintf(label, sizeof(label),
             "Кнопка sgsfdgdf dfgs gsf  sdg  sg  sgsg  sg  sg g g  gs nhdf nfg db sdgb fd bds fb df nfgdn fdbgdgnj fd bd fn fgn dhfj ty g svf h ytl iu y h");
    GtkWidget *buffer = gtk_event_box_new();
    gtk_widget_set_size_request(buffer, -1, 100);
    gtk_widget_set_halign(buffer, GTK_ALIGN_START);
    gtk_widget_set_valign(buffer, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(scroll_box), buffer, TRUE, TRUE, 0);

    gtk_style_context_add_class(gtk_widget_get_style_context(buffer), "buffer");
    apply_styles(1, buffer);

    gtk_widget_add_events(buffer, GDK_ENTER_NOTIFY_MASK | GDK_LEAVE_NOTIFY_MASK);
    g_signal_connect(buffer, "enter-notify-event", G_CALLBACK(on_enter_notify), NULL);
    g_signal_connect(buffer, "leave-notify-event", G_CALLBACK(on_leave_notify), NULL);

    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    GtkWidget *button_label = gtk_label_new(label);
    gtk_widget_set_halign(button_label, GTK_ALIGN_START);
    gtk_widget_set_valign(button_label, GTK_ALIGN_START);
    gtk_label_set_line_wrap(GTK_LABEL(button_label), TRUE);

    GtkWidget *tool_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(tool_box, 30, -1);

    GtkWidget *delete_button = gtk_button_new();
    gtk_widget_set_halign(delete_button, GTK_ALIGN_END);
    gtk_widget_set_valign(delete_button, GTK_ALIGN_START);
    gtk_widget_set_vexpand(delete_button, TRUE);

    char *menu_icon_path = g_build_filename(g_get_user_data_dir(), APP_NAME, "resources/delete-icon.svg", NULL);
    GdkPixbuf *menu_pixbuf = gdk_pixbuf_new_from_file_at_scale(menu_icon_path, 18, 18, TRUE, NULL);
    GtkWidget *menu_icon = gtk_image_new_from_pixbuf(menu_pixbuf);
    g_object_unref(menu_pixbuf);
    g_free(menu_icon_path);
    gtk_button_set_image(GTK_BUTTON(delete_button), menu_icon);

    g_object_set_data(G_OBJECT(delete_button), "buffer", buffer);
    g_signal_connect(delete_button, "button-press-event", G_CALLBACK(on_delete_press), scroll_box);

    GtkWidget *pin_button = gtk_button_new();
    gtk_widget_set_halign(pin_button, GTK_ALIGN_END);
    gtk_widget_set_valign(pin_button, GTK_ALIGN_END);
    gtk_widget_set_vexpand(pin_button, TRUE);

    char *pin_icon_path = g_build_filename(g_get_user_data_dir(), APP_NAME, "resources/pin-icon.svg", NULL);
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(pin_icon_path, 18, 18, TRUE, NULL);
    GtkWidget *pin_icon = gtk_image_new_from_pixbuf(pixbuf);
    g_object_unref(pixbuf);
    g_free(pin_icon_path);
    gtk_button_set_image(GTK_BUTTON(pin_button), pin_icon);

    gtk_box_pack_start(GTK_BOX(main_box), button_label, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(main_box), tool_box, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(tool_box), delete_button, FALSE, FALSE, 2);
    gtk_box_pack_start(GTK_BOX(tool_box), pin_button, FALSE, FALSE, 2);

    gtk_container_add(GTK_CONTAINER(buffer), main_box);
    gtk_widget_show_all(buffer);
}

GtkWindow *create_main_window() {
    GtkWindow *window = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
    gtk_window_set_default_size(window, 350, 450);
    gtk_window_set_decorated(window, FALSE);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

    GtkWidget *top_panel_overlay = gtk_overlay_new();
    gtk_widget_set_size_request(top_panel_overlay, 350, 38);

    GtkWidget *event_box = gtk_event_box_new();
    gtk_event_box_set_above_child(GTK_EVENT_BOX(event_box), FALSE);

    GtkWidget *close_button = gtk_button_new();

    GtkWidget *icon = gtk_image_new_from_icon_name("window-close-symbolic", GTK_ICON_SIZE_BUTTON);
    gtk_image_set_pixel_size(GTK_IMAGE(icon), 24);
    gtk_button_set_image(GTK_BUTTON(close_button), icon);

    gtk_widget_set_halign(close_button, GTK_ALIGN_END);
    gtk_widget_set_valign(close_button, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_end(close_button, 6);

    GtkWidget *grip = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(grip, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grip, GTK_ALIGN_CENTER);

    GtkWidget *middle_panel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(middle_panel, -1, 38);

    GtkWidget *title_label = gtk_label_new(NULL);
    gtk_widget_set_halign(title_label, GTK_ALIGN_START);
    gtk_widget_set_valign(title_label, GTK_ALIGN_END);
    gtk_widget_set_margin_start(title_label, 12);
    gtk_widget_set_margin_bottom(title_label, 2);
    gtk_label_set_markup(GTK_LABEL(title_label), "<span font_desc='12' weight='bold'>Буфер обмена</span>");

    GtkWidget *clear_button = gtk_button_new_with_label("Очистить");
    gtk_widget_set_hexpand(clear_button, TRUE);
    gtk_widget_set_halign(clear_button, GTK_ALIGN_END);
    gtk_widget_set_valign(clear_button, GTK_ALIGN_END);
    gtk_widget_set_margin_end(clear_button, 12);

    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_widget_set_margin_top(scrolled_window, 3);
    gtk_widget_set_margin_bottom(scrolled_window, 5);

    scroll_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    gtk_widget_set_margin_start(scroll_box, 12);
    gtk_widget_set_margin_end(scroll_box, 12);

    gtk_style_context_add_class(gtk_widget_get_style_context(close_button), "close-button");
    gtk_style_context_add_class(gtk_widget_get_style_context(event_box), "event-box");
    gtk_style_context_add_class(gtk_widget_get_style_context(grip), "grip");

    apply_styles(3, close_button, event_box, grip);

    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_container_add(GTK_CONTAINER(event_box), top_panel_overlay);
    gtk_container_add(GTK_CONTAINER(middle_panel), title_label);
    gtk_container_add(GTK_CONTAINER(middle_panel), clear_button);
    gtk_container_add(GTK_CONTAINER(scrolled_window), scroll_box);
    gtk_overlay_add_overlay(GTK_OVERLAY(top_panel_overlay), grip);
    gtk_overlay_add_overlay(GTK_OVERLAY(top_panel_overlay), close_button);
    gtk_box_pack_start(GTK_BOX(box), event_box, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), middle_panel, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), scrolled_window, TRUE, TRUE, 0);

    g_signal_connect(close_button, "clicked", G_CALLBACK(gtk_main_quit), window);
    g_signal_connect(event_box, "button-press-event", G_CALLBACK(on_button_press), window);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);

    return window;
}
