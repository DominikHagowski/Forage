#include "rssitem.h"

GList *parse_document(char *doc_path);
rss_item *parse_item(xmlDoc *document, xmlNode *cursor);
void display_feed(GList *items);
void update_feed(char *path);

