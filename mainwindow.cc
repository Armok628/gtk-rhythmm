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
	cout<<"!!!!!!!!!!!!!!!!"<<endl<<"Reset button clicked!"<<endl<<"!!!!!!!!!!!!!!!!"<<endl;
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
	float sum=0.0;
	for (int i=0;i<8;i++)
	{
		cout<<"================"<<endl;
		if (sum==4.0)
		{
			cout<<"Not generating notes past sum of 4"<<endl;
			break;
		}
		if (sum<3.5)
		{
			switch (rand()%2)
			{
				case 0:cout<<"Making note of length 1.0"<<endl;sum+=1.0;note_lengths[i]=1.0;break;
				case 1:cout<<"Making note of length 0.5"<<endl;sum+=0.5;note_lengths[i]=0.5;break;
			}
		}
		else if (sum==3.5)
		{
			cout<<"Forced to make a note of length 0.5"<<endl;
			sum+=0.5;
			note_lengths[i]=0.5;
		}
		if ((rand()%8)==0)
		{
			cout<<"Making it a rest!"<<endl;
			if (note_lengths[i]==1.0)
				note_lengths[i]=0.1;
			if (note_lengths[i]==0.5)
				note_lengths[i]=0.05;
		}
		cout<<"Recap:"<<endl<<"Note length = "<<note_lengths[i]<<endl<<"Current sum = "<<sum<<endl;
	}
	cout<<"================"<<endl;
	for (int i=0;i<8;i++)
	{
		if (note_lengths[i]<0.01)
		{
			cout<<"Not drawing notes of length 0"<<endl;
			break;
		}
		if (note_lengths[i]==0.1)
		{
			cout<<"Setting note "<<i<<" to a quarter rest"<<endl;
			notes[i]=Gtk::Image("assets/qr.png");
		}
		else if (note_lengths[i]==0.05)
		{
			if (i==7||note_lengths[i+1]!=0.05)
			{
				cout<<"Setting note "<<i<<" to an eighth rest"<<endl;
			       	notes[i]=Gtk::Image("assets/er.png");
			}
			else if (note_lengths[i+1]==0.05)
			{
				cout<<"Setting eight rests "<<i<<" and "<<i+1<<" to a single quarter rest"<<endl;
				notes[i]=Gtk::Image("assets/qr.png");
				i++;
			}
		}
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
				cout<<"Setting eighth notes "<<i<<" and "<<i+1<<" to beamed eighth notes"<<endl;
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
		box.pack_start(notes[i]);
		notes[i].show();
	}
}
