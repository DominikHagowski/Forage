#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <glib.h>
#include "feed.h"

GList *parse_document(GList *item_list, char *doc_path);
feed_item_data *parse_item(xmlDoc *document, xmlNode *cursor);

