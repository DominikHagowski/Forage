#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "parser.h"

void parse_document(char *doc_path) {
	xmlDoc *document;
	xmlNode *cursor;

	document = xmlReadFile(doc_path, NULL, 0);

	if (document == NULL) {
		fprintf(stderr, "Document could not be parsed.\n");
		return;
	}

	cursor = xmlDocGetRootElement(document);

	if (cursor == NULL) {
		fprintf(stderr, "Document is empty\n");
		xmlFreeDoc(document);
		return;
	}

	if (xmlStrcmp(cursor->name, (const xmlChar *)"rss")) {
		fprintf(stderr, "Document is not an valid RSS feed (missing rss node)\n");
		xmlFreeDoc(document);
		return;
	}

	cursor = cursor->xmlChildrenNode;
	if (xmlIsBlankNode(cursor)) { cursor = cursor->next; }  // skip blank nodes
	if (xmlStrcmp(cursor->name, (const xmlChar *)"channel")) {
		fprintf(stderr, "Document is not an valid RSS feed (missing channel node)\n");
		xmlFreeDoc(document);
		return;
	}

	cursor = cursor->xmlChildrenNode;
	while (cursor != NULL) {
		if (!(xmlStrcmp(cursor->name, (const xmlChar *)"item"))) {
			parse_item(document, cursor);
		}
		cursor = cursor->next;
	}
}

void parse_item(xmlDoc *document, xmlNode *cursor) {
	xmlChar *title;
	xmlChar *link;
	xmlChar *description;

	cursor = cursor->xmlChildrenNode;

	while (cursor != NULL) {
		if (!(xmlStrcmp(cursor->name, (const xmlChar *)"title"))) {
			title = xmlNodeListGetString(document, cursor->xmlChildrenNode, 1);
		}

		if (!(xmlStrcmp(cursor->name, (const xmlChar *)"link"))) {
			link = xmlNodeListGetString(document, cursor->xmlChildrenNode, 1);
		}

		if (!(xmlStrcmp(cursor->name, (const xmlChar *)"description"))) {
			description = xmlNodeListGetString(document, cursor->xmlChildrenNode, 1);
		}

		cursor = cursor->next;
	}

	printf("title: %s\n", title);
	printf("link: %s\n", link);
	printf("description: %s\n", description);
	printf("\n");

	xmlFree(title);
	xmlFree(link);
	xmlFree(description);
}

