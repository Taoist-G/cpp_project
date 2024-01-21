#include "WindowSetup.h"
#include <FL/Fl.H>

Fl_Window* currentWindow = nullptr; // Definition of the global variable.

int main() {
    Fl::visual(FL_DOUBLE|FL_INDEX);
    setupHomePage();
    return Fl::run();
}
