#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

struct Letter{
    int position;
    char letter;
    int frequency;
};

void removeDuplicates(vector<char> &v)
{
    vector<char>::iterator itr = v.begin();
    unordered_set<char> s;
    for (char & curr : v) {
        if (s.insert(curr).second) {
            *itr++ = curr;
        }
    }

    v.erase(itr, v.end());
}

bool sortFreq(const Letter &a, const Letter &b){
    bool t;
    if(a.frequency != b.frequency)
        t = a.frequency > b.frequency;
    else
        t = a.position < b.position;
    return (t);
}

int getPos(const char ch, const vector<char> &order) {
    int pos;
    for (int i = 0; i < order.size(); i++){
        if (order[i] == ch){
            pos = i;
            break;
        }
    }
    return pos;
}

int main() {
    string dna;
    vector <char> vDna;
    getline(cin, dna);
    for (char & i : dna){
        vDna.push_back(i);
    }
    vector<char> order = vDna;
    removeDuplicates(order);
    sort(vDna.begin(), vDna.end());
    char ch = vDna[0];
    int pos = getPos(ch, order);
    int count = 0;
    vector <Letter> counting;
    for (int i = 0; i < vDna.size(); i++){
        if (ch == vDna[i])
            count++;
        if (ch != vDna[i+1]){
            Letter letter;
            letter.letter = vDna[i];
            letter.frequency = count;
            letter.position = pos;
            counting.push_back(letter);
            ch = vDna[i+1];
            count = 0;
            pos = getPos(vDna[i + 1], order);
        }
    }
    sort(counting.begin(), counting.end(), sortFreq);
    for (auto & i : counting){
        cout << i.letter << " " << i.frequency << endl;
    }
    return 0;
}