#include <gtk/gtk.h>
#include "parser.h"

void update_feed(GtkWidget *list_box, gchar *path);
void clear_feed(GList *items);
GtkWidget *create_row(gchar *text);

