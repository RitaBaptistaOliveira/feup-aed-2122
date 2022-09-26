#include "LuggageCart.h"

/**
 * Class LuggageCart constructor.
 * Initializes a new instance of the LuggageCart class using the specified maxPiles and maxLuggage
 * @param maxPiles Maximum number of piles per luggage cart
 * @param maxLuggage Maximum number of luggage per pile
 */
LuggageCart::LuggageCart(int maxPiles, int maxLuggage) {
    this->maxPiles = maxPiles;
    this->maxLuggage = maxLuggage;
    stack<luggage> s;
    for (int i = 0; i < maxPiles; i++) {
        cart.push_back(s);
    }
}

/**
 * @return The maximum number of piles of the luggage cart
 */
int LuggageCart::getMaxPiles() const {
    return maxPiles;
}

/**
 * Sets the maximum number of piles of the luggage cart to the given number
 * @param maxPiles New maximum of piles
 */
void LuggageCart::setMaxPiles(int maxPiles) {
    this->maxPiles = maxPiles;
}

/**
 * @return the maximum number of luggage per pile
 */
int LuggageCart::getMaxLuggage() const {
    return maxLuggage;
}

/**
 * Sets the maximum number of luggage per pile to the given number
 * @param maxLuggage New maximum number of luggage
 */
void LuggageCart::setMaxLuggage(int maxLuggage) {
    this->maxLuggage = maxLuggage;
}

/**
 * @return The cart, a list of stacks
 */
list<stack<luggage>> LuggageCart::getCart() const {
    return cart;
}

/**
 * Adds a luggage to the last unfilled pile in the luggage cart
 * @param l Luggage to add
 */
void LuggageCart::addLuggage(const luggage l) {
    list<stack<luggage>>::iterator pile;
    for (pile = cart.begin(); pile != cart.end(); pile++) {
        if (pile->size() < maxLuggage) {
            pile->push(l);
            break;
        }
    }
}

/**
 * Checks if the cart is full
 * @return true if the luggage cart is full or false otherwise
 */
bool LuggageCart::isFull() {
    return cart.back().size() == maxLuggage;
}
