#include "window.h"

void activate(GtkApplication *app, gpointer user_data) {
	const int win_width = 800;
	const int win_height = 600;
	const int paned_pos = 300;

	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *menu_bar;
	GtkWidget *panes;
	GtkWidget *scrolled_window;
	GtkWidget *list_box;
	GtkWidget *text_box;
	GtkWidget *chooser_button;
	GtkWidget *chooser_button_box;

	feed_object *feed;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Forage");
	gtk_window_set_default_size(GTK_WINDOW(window), win_width, win_height);

	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(window), grid);

	menu_bar = gtk_menu_bar_new();
	g_object_set(G_OBJECT(menu_bar), "hexpand", 1, NULL);
	g_object_set(G_OBJECT(menu_bar), "vexpand", 0, NULL);
	gtk_container_add(GTK_CONTAINER(menu_bar), gtk_menu_item_new_with_label("File"));
	gtk_container_add(GTK_CONTAINER(menu_bar), gtk_menu_item_new_with_label("View"));
	gtk_grid_attach(GTK_GRID(grid), menu_bar, 0, 0, 1, 1);

	panes = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_paned_set_position(GTK_PANED(panes), paned_pos);
	g_object_set(G_OBJECT(panes), "expand", 1, NULL);
	gtk_grid_attach(GTK_GRID(grid), panes, 0, 1, 1, 1);

	scrolled_window = gtk_scrolled_window_new(NULL, NULL);
	g_object_set(G_OBJECT(scrolled_window), "expand", 1, NULL);
	gtk_paned_add1(GTK_PANED(panes), scrolled_window);

	list_box = gtk_list_box_new();
	gtk_container_add(GTK_CONTAINER(scrolled_window), list_box);

	text_box = gtk_text_view_new();
	gtk_paned_add2(GTK_PANED(panes), text_box);

	chooser_button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	g_object_set(G_OBJECT(chooser_button_box), "vexpand", 0, NULL);
	gtk_grid_attach(GTK_GRID(grid), chooser_button_box, 0, 3, 1, 1);

	feed = feed_init(list_box, text_box);

	chooser_button = gtk_file_chooser_button_new("Open", GTK_FILE_CHOOSER_ACTION_OPEN);
	g_signal_connect(chooser_button, "file-set", G_CALLBACK(set_path), feed);
	gtk_container_add(GTK_CONTAINER(chooser_button_box), chooser_button);

	gtk_widget_show_all(window);
}

void set_path(GtkWidget *button, feed_object *feed) {
	gchar *path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));
	feed_update(feed, path);

	gtk_widget_show_all(feed->list);
}

