#include "rssitem.h"

rss_item *parse_item(xmlDoc *document, xmlNode *cursor);
GList *parse_document(char *doc_path);

