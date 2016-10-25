#include "mainwindow.h"
#include <cstdlib>
#include <ctime>
#include <gtkmm/image.h>
#include <iostream>
using namespace std;
MainWindow::MainWindow() : box(),reset_button("Reset")
{
	reset_button.signal_clicked().connect(sigc::mem_fun(*this,&MainWindow::on_reset_clicked));
	box.pack_start(reset_button);
	srand(time(0));
	generate_notes();
	for (int i=0;i<8;i++)
		box.pack_start(notes[i]);
	add(box);
	box.show();
	reset_button.show();
	draw_notes();
}
MainWindow::~MainWindow()
{
}
void MainWindow::on_reset_clicked()
{
	cout<<"Reset button clicked!"<<endl;
	for (int i=0;i<8;i++)
	{
		notes[i].hide();
		note_lengths[i]=0.0;
		notes[i]=Gtk::Image("assets/n.png");
	}
	generate_notes();
	draw_notes();
}
void MainWindow::generate_notes()
{
	sum=0.0;
	for (int i=0;i<8;i++)
	{
		if (sum<3.5)
		{
			switch (rand()%2)
			{
				case 0:sum+=1.0;note_lengths[i]=1.0;break;
				case 1:sum+=0.5;note_lengths[i]=0.5;break;
			}
		}
		else if (sum==3.5)
		{
			sum+=0.5;
			note_lengths[i]=0.5;
			break;
		}
		else notes[i]=Gtk::Image("assets/n.png");
	}
	for (int i=0;i<8;i++)
	{
		if (note_lengths[i]==1.0)
		{
			cout<<"Setting note "<<i<<" to a quarter note"<<endl;
			notes[i]=Gtk::Image("assets/q.png");
		}
		else if (note_lengths[i]==0.5)
		{
			if (i==7||note_lengths[i+1]!=0.5)
			{
				cout<<"Setting note "<<i<<" to an eighth note"<<endl;
				notes[i]=Gtk::Image("assets/e1.png");
			}
			else if (note_lengths[i+1]==0.5)
			{
				cout<<"Setting notes "<<i<<" and "<<i+1<<" to beamed eighth notes"<<endl;
				notes[i]=Gtk::Image("assets/e2.png");
				i++;
			}
		}
	}
}
void MainWindow::draw_notes()
{
	for (int i=0;i<8;i++)
	{
		cout<<"Now showing note number: "<<i<<endl;
		box.pack_start(notes[i]);
		notes[i].show();
	}
}
