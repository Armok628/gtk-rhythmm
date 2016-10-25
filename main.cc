#include "mainwindow.h"
int main(int argc,char *argv[])
{
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc,argv,"org.gtkmm.mrhythm");
	MainWindow main;
	main.set_title("Rhythm Generator");
	return app->run(main);
}
