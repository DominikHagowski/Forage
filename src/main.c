#include "window.h"
#include "update.h"

int main(int argc, char **argv) {

	if (argc != 2) {
		g_print("Please provide an XML file to parse\n");
	}
	else {
		update_feed(argv[1]);
	}

	GtkApplication *application;
	int status;

	application = gtk_application_new("org.mzyzc.forage", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(application, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(application), argc, argv);
	g_object_unref(application);
	
	return status;
}

