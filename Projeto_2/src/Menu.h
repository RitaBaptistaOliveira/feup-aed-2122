#ifndef FEUP_AED_PROJ2_MENU_H
#define FEUP_AED_PROJ2_MENU_H


#include "Graph.h"
#include "Application.h"

class Menu {
public:
    Menu();
    void run();

private:
    void drawMenu();
    void stopsMenu(pair <string, string> stops);
    pair<string, string> stopType();
    Application app;
};


#endif