#include "parser.h"

GList *parse_document(GList *item_list, char *doc_path) {
	feed_item *current_item;

	xmlDoc *document;
	xmlNode *cursor;

	document = xmlReadFile(doc_path, NULL, 0);

	if (document == NULL) {
		fprintf(stderr, "Document could not be parsed.\n");
		exit(1);
	}

	cursor = xmlDocGetRootElement(document);

	if (cursor == NULL) {
		fprintf(stderr, "Document is empty\n");
		xmlFreeDoc(document);
		exit(2);
	}

	if (xmlStrcmp(cursor->name, (const xmlChar *)"rss")) {
		fprintf(stderr, "Document is not an valid RSS feed (missing rss node)\n");
		xmlFreeDoc(document);
		exit(3);
	}

	cursor = cursor->xmlChildrenNode;
	if (xmlIsBlankNode(cursor)) { cursor = cursor->next; }  // skip blank nodes
	if (xmlStrcmp(cursor->name, (const xmlChar *)"channel")) {
		fprintf(stderr, "Document is not an valid RSS feed (missing channel node)\n");
		xmlFreeDoc(document);
		exit(4);
	}

	cursor = cursor->xmlChildrenNode;
	while (cursor != NULL) {
		if (!(xmlStrcmp(cursor->name, (const xmlChar *)"item"))) {
			current_item = malloc(sizeof(feed_item));
			current_item->data = parse_item(document, cursor);
			item_list = g_list_prepend(item_list, current_item);
		}
		cursor = cursor->next;
	}

	xmlFreeNode(cursor);
	xmlFreeDoc(document);

	return item_list;
}

feed_item_data *parse_item(xmlDoc *document, xmlNode *cursor) {
	feed_item_data *item_data = malloc(sizeof(feed_item_data));

	cursor = cursor->xmlChildrenNode;
	while (cursor != NULL) {
		if (!(xmlStrcmp(cursor->name, (const xmlChar *)"title"))) {
			item_data->title = (char *)xmlNodeListGetString(document, cursor->xmlChildrenNode, 1);
		}
		else if (!(xmlStrcmp(cursor->name, (const xmlChar *)"link"))) {
			item_data->link = (char *)xmlNodeListGetString(document, cursor->xmlChildrenNode, 1);
		}
		else if (!(xmlStrcmp(cursor->name, (const xmlChar *)"description"))) {
			item_data->description = (char *)xmlNodeListGetString(document, cursor->xmlChildrenNode, 1);
		}

		cursor = cursor->next;
	}

	return item_data;
}

