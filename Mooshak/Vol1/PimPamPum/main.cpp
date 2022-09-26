#include <iostream>
#include <string>
#include <list>


using namespace std;

void findKids(const string &phrase, string kidsPlaying, list<string> &kids) {
    string kid;
    size_t pos = kidsPlaying.find(' ');
    while (pos != string::npos) {
        kid = kidsPlaying.substr(0, pos);
        kids.push_back(kid);
        kidsPlaying = kidsPlaying.substr(pos + 1);
        pos = kidsPlaying.find(' ');
    }
    kids.push_back(kidsPlaying);
}

bool safe(int numWords, int numKids, const string &kidToCheck, list<string> &kids) {
    int repeat;
    list<string>::iterator it = kids.begin();
    while(kids.size()>1){
        repeat = (numWords-1)%numKids;
        if(it == kids.end())
            it = kids.begin();
        for(int i = 0; i < repeat; i++){
            it++;
            if(it == kids.end())
                it = kids.begin();
        }
        it = kids.erase(it);
        if(it == kids.end())
            it = kids.begin();
        numKids--;
    }
    if(*kids.begin() == kidToCheck)
        return false;
    else
        return true;
}

int numOfWords(string phrase){
    int n;
    for (char c : phrase){
        if(c == ' ')
            n++;
    }
    return n+1;
}

int main() {
    int n;
    string kidToCheck = "Carlos";
    string number;
    getline(cin, number);
    n = stoi(number);
    //cin.ignore(1000, '\n');
    for (int i = 0; i < n; i++) {
        int numWords, numKids;
        string phrase, kidsPlaying;
        list<string> kids;

        getline(cin, phrase);
        numWords = numOfWords(phrase);

        getline(cin, kidsPlaying);
        numKids = stoi(kidsPlaying.substr(0, kidsPlaying.find(" ")));
        kidsPlaying = kidsPlaying.substr(kidsPlaying.find(" ") + 1);

        //Separar as crianças
        findKids(phrase, kidsPlaying, kids);

        //Ver se a criança se livrou
        if (!safe(numWords, numKids, kidToCheck, kids))
            cout << "O " << kidToCheck << " nao se livrou" << endl;
        else
            cout << "O " << kidToCheck << " livrou-se (coitado do " << *kids.begin() << "!)" << endl;
    }
}




