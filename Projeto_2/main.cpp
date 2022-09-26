#include <iostream>
#include "src/Coordinates.h"
#include "src/Menu.h"

using namespace std;

int main() {
    Graph g(true);
    Graph gLine(true);
    Application app(g, gLine);
    Menu menu;
    menu.run();
    return 0;
}
