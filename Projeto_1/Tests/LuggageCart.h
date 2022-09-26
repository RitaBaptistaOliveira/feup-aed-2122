#ifndef UNTITLED2_LUGGAGECART_H
#define UNTITLED2_LUGGAGECART_H

#include <iostream>
#include <stack>
#include <list>

using namespace std;

typedef int luggage;

class LuggageCart {
    int maxPiles;
    int maxLuggage;
    list<stack<luggage>> cart;
public:
    LuggageCart(int maxPiles, int maxLuggage);
    int getMaxPiles() const;
    void setMaxPiles(int MaxPiles);
    int getMaxLuggage() const;
    void setMaxLuggage(int MaxLuggage);
    list<stack<luggage>> getCart() const;
    void addLuggage(luggage luggage);
    bool isFull();
};

#endif //UNTITLED2_LUGGAGECART_H