#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H
#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
class MainWindow : public Gtk::Window
{
	public:
		MainWindow();
		virtual ~MainWindow();
	protected:
		void on_reset_clicked();
		void generate_notes();
		void draw_notes();
		float sum;
		float note_lengths[8];
		Gtk::Image notes[8];
		Gtk::Button reset_button;
		Gtk::Box box;
};
#endif
