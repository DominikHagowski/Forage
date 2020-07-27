#include <gtk/gtk.h>
#include "parser.h"

feed_object *feed_init(GtkWidget *list, GtkWidget *text_box);
void feed_update(feed_object *feed, gchar *path);
void feed_clear(feed_object *feed);
void create_row(feed_object *feed, feed_item *item);
void update_preview(GtkListBox *list_box, GtkListBoxRow *row, feed_object *feed);

