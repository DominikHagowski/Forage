#include "window.h"
#include "update.h"

int main(int argc, char **argv) {
	//GtkApplication *application;
	//int status;

	//application = gtk_application_new("org.mzyzc.forage", G_APPLICATION_FLAGS_NONE);
	//g_signal_connect(application, "activate", G_CALLBACK(activate), NULL);
	//status = g_application_run(G_APPLICATION(application), argc, argv);
	//g_object_unref(application);
	
	//return status;
	
	if (argc != 2) {
		printf("Please provide an XML file to parse\n");
		return 1;
	}

	update_feed(argv[1]);
}

