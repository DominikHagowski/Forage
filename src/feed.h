#include <gtk/gtk.h>

typedef struct feed_item_data {
	char *title;
	char *link;
	char *description;
} feed_item_data;

typedef struct feed_item {
	GtkWidget *row;
	feed_item_data *data;
} feed_item;

typedef struct feed_object {
	GList *items;
	GtkWidget *list;
	GtkWidget *preview;
} feed_object;

