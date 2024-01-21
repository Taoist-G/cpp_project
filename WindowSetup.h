#ifndef WINDOWSETUP_H
#define WINDOWSETUP_H
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <string>

void setupHomePage();
void setupGUI();
void startGame(Fl_Widget*, void*);
void loadGame(Fl_Widget*, void*);
void playGame(int difficulty);
void playGame(std::string filename);
void backToStart(Fl_Widget*, void*);
void level_callback(Fl_Widget*, void* userdata);
void exit_callback(Fl_Widget*, void*);

extern Fl_Window* currentWindow;

#endif // WINDOWSETUP_H
