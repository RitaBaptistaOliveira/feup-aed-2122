// AED 2021/2022 - Aula Pratica 07
// Ultima edicao: Pedro Ribeiro (DCC/FCUP) [06/12/2012]

#ifndef _FUNBST_H_
#define _FUNBST_H_

#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <set>
#include <map>

using namespace std;

class FunWithBSTs {
public:
    static int newBag(const vector<int>& collection, const vector<int>& bag);
    static int battle(const vector<int>& alice, const vector<int>& bruno);
    static int numberMovies(const vector<pair<string, int>>& reviews);
    static void moreReviews(const vector<pair<string, int>>& reviews, int& m, int& n);
    static vector<string> topMovies(const vector<pair<string, int>>& reviews, double k);
};

#endif
