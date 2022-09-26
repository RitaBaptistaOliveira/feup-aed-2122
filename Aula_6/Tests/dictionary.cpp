#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"

using namespace std;

WordMean::WordMean(string w, string m): word(w), meaning(m) {}

string WordMean::getWord() const {
    return word;
}

string WordMean::getMeaning() const {
    return meaning;
}

void WordMean::setMeaning(string m) {
    meaning = m;
}

void WordMean::setWord(string w) {
    word = w;
}

bool WordMean::operator<(const WordMean &s) const{
    return this->word < s.word;
}

bool WordMean::operator==(const WordMean &s) const {
    return this->word == s.word;
}

BST<WordMean> Dictionary::getWords() const {
	return words;
}

// ---------------------------------------------

//TODO
void Dictionary::readFile(ifstream &f) {
    while(!f.eof()){
        string word, meaning;
        getline(f, word);
        getline(f, meaning);
        WordMean w(word, meaning);
        words.insert(w);
    }
}

//TODO
string Dictionary::consult(string word1, WordMean& previous, WordMean& next) const {
    WordMean w(word1, "");
    iteratorBST<WordMean> it = words.begin();
    while(it != words.end()){
        if(*it == w)
            return (*it).getMeaning();
        else
            previous = next;
        it++;
        next = *it;
        if(w < next)
            break;
    }
    return "word not found";
}

//TODO
bool Dictionary::update(string word1, string mean1) {
    WordMean w(word1, mean1);
    iteratorBST<WordMean> it = words.begin();
    while(it != words.end()){
        if(*it == w){
            words.remove(*it);
            words.insert(w);
            return true;
        }
        else
            it++;
    }
    words.insert(w);
    return false;
}

//TODO
void Dictionary::print() const {
    BSTItrIn<WordMean> it(words);
    while(!it.isAtEnd()) {
        cout << it.retrieve().getWord() << endl << it.retrieve().getMeaning() << endl;
        it.advance();
    }
}
