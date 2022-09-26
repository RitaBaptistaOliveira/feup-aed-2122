#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Game::numberOfWords(string phrase) {
  if ( phrase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = phrase.find(' ');
  while (pos != string::npos) {
    phrase = phrase.substr(pos+1);
    pos = phrase.find(' ');
    n++;
  }
  return n;
}

Game::Game() {
	this->kids.clear();
}

Game::Game(list<Kid>& l2) {
	this->kids = l2;
}

//-----------------------------------------------------------------

// TODO
void Game::addKid(const Kid k1) {
    kids.push_back(k1);
}

// TODO
list<Kid> Game::getKids() const {
    return kids;
}

// TODO
void Game::setKids(const list<Kid>& l1) {
    kids = l1;
}

// TODO
Kid Game::loseGame(string phrase) {
    list<Kid>::iterator itr = kids.begin();
    int repeat = numberOfWords(phrase);
    while(kids.size() > 1){
        int r = (repeat-1)%kids.size();
        if(itr == kids.end())
            itr = kids.begin();
        for(int i = 1; i <= r; i++){
            itr++;
            if(itr == kids.end())
                itr = kids.begin();
        }
        itr = kids.erase(itr);
        if(itr == kids.end())
            itr = kids.begin();
    }
    return kids.front();
}

// TODO
list<Kid> Game::removeOlder(unsigned id) {
    return (list<Kid>());
}

// TODO
queue<Kid> Game::rearrange() {
    queue<Kid> girls;
    queue<Kid> boys;
    list<Kid>::iterator itr = kids.begin();
    for(int i = 0; i < kids.size();i++){
        if(itr->getSex() == 'f')
            girls.push(*itr);
        else if (itr->getSex() == 'm')
            boys.push(*itr);
        itr++;
    }
    kids.clear();
    int numGirls = girls.size(), numBoys = boys.size();
    int g, b;
    if(numGirls < numBoys) {
        g = 1;
        b = numBoys/numGirls;
    }
    else{
        b = 1;
        g = numGirls/numBoys;
    }
    while(!girls.empty() && !boys.empty()){
        for(int i = 0; i < g; i++){
            kids.push_back(girls.front());
            girls.pop();
        }
        for(int i = 0; i < b; i++){
            kids.push_back(boys.front());
            boys.pop();
        }
    }
    if(girls.empty())
        return boys;
    else
        return girls;
}

// TODO
bool Game::operator==(Game& g2) {
	return true;
}

// TODO
list<Kid> Game::shuffle() const {
	return (list<Kid>());
}
