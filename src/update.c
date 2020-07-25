#include "update.h"

void update_feed(GtkWidget *list_box, gchar *path) {
	GList *items = parse_document(path);
	rss_item *data = NULL;

	for (GList *l = items; l != NULL; l = l->next) {
		data = l->data;
		GtkWidget *row = create_row(data->title);
		gtk_list_box_insert(GTK_LIST_BOX(list_box), row, -1);
	}

	clear_feed(items);
}

void clear_feed(GList *items) {
	rss_item *data = NULL;
	for (GList *l = items; l != NULL; l = l->next) {
		data = l->data;
		free(data->title);
		free(data->link);
		free(data->description);
		free(data);
	}
	g_list_free(items);
}

GtkWidget *create_row(gchar *text) {
	GtkWidget *row;
	GtkWidget *box;
	GtkWidget *label;

 	row = gtk_list_box_row_new();

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_container_add(GTK_CONTAINER(row), box);

	label = gtk_label_new(text);
	gtk_container_add(GTK_CONTAINER(box), label);

	return row;
}

