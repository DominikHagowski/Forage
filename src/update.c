#include "update.h"

feed_object *feed_init(GtkWidget *list, GtkWidget *text_box) {
	feed_object *feed = malloc(sizeof(feed_object));
	GList *feed_items = NULL;

	feed->items = feed_items;
	feed->list = list;
	feed->preview = text_box;

	return feed;
}

void feed_update(feed_object *feed, char *path) {
	GList *items = feed->items;
	items = parse_document(items, path);
	feed_item *current_item;

	for (GList *l = items; l != NULL; l = l->next) {
		current_item = l->data;
		create_row(feed, current_item);
	}
	feed_clear(feed);
}

void feed_clear(feed_object *feed) {
	GList *items = feed->items;
	feed_item *current_item;
	feed_item_data *current_data;

	for (GList *l = items; l != NULL; l = l->next) {
		current_item = items->data;
		current_data = current_item->data;

		free(current_data->title);
		free(current_data->link);
		free(current_data->description);
		free(current_data);

		g_object_unref(current_item->row);
		free(current_item);
	}
	g_list_free(items);
}

void create_row(feed_object *feed, feed_item *item) {
	feed_item_data *item_data = item->data;

	GtkWidget *row = item->row;
	GtkWidget *box;
	GtkWidget *label;

 	row = gtk_list_box_row_new();

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
	gtk_container_add(GTK_CONTAINER(row), box);

	label = gtk_label_new(item_data->title);
	gtk_container_add(GTK_CONTAINER(box), label);

	g_signal_connect(feed->list, "row-selected", G_CALLBACK(update_preview), feed);

	gtk_list_box_prepend(GTK_LIST_BOX(feed->list), row);
}

void update_preview(GtkListBox *list_box, GtkListBoxRow *row, feed_object *feed) {
	//printf("success\n");
}

