#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "parser.h"

void parse_document(char *doc_name) {
	xmlDoc *document;
	xmlNode *cursor;

	document = xmlParseFile(doc_name);

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

	if (xmlStrcmp(cursor->name, (const xmlChar *) "rss")) {
		fprintf(stderr, "Document is not an valid RSS feed\n");
		xmlFreeDoc(document);
		return;
	}
}

