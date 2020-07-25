#include "update.h"

void display_feed(GList *items) {
	rss_item *data = NULL;
	for (GList *l = items; l != NULL; l = l->next) {
		data = l->data;
		g_print("title: %s\n", data->title);
		g_print("link: %s\n", data->link);
		g_print("description: %s\n", data->description);
		g_print("\n");
	}
}

void update_feed(char *path) {
	GList *items = parse_document(path);
	display_feed(items);
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

