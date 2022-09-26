// AED 2021/2022 - Aula Pratica 07
// Pedro Ribeiro (DCC/FCUP) [06/12/2012]

#include "funWithBSTs.h"
#include "bst.h"

// ----------------------------------------------------------
// Exercicio 1: Colecao de Cromos
// ----------------------------------------------------------
// TODO
int FunWithBSTs::newBag(const vector<int>& collection, const vector<int>& bag) {
    int oldNum, newNum;
    unordered_set<int> s;
    for(int n : collection){
        s.insert(n);
    }
    oldNum = s.size();
    for(int n : bag){
        s.insert(n);
    }
    newNum = s.size();
    return newNum - oldNum;
}

// ----------------------------------------------------------
// Exercicio 2: Batalha de Pokemons
// ----------------------------------------------------------
// TODO
int FunWithBSTs::battle(const vector<int>& alice, const vector<int>& bruno) {
  multiset<int, greater<int>> baralhoA, baralhoB;
  for(int card : alice){
      baralhoA.insert(card);
  }
  for(int card : bruno){
       baralhoB.insert(card);
  }
  while(baralhoA.size() != 0 && baralhoB.size() != 0){
      int cardA = *baralhoA.begin();
      baralhoA.erase(baralhoA.begin());
      int cardB = *baralhoB.begin();
      baralhoB.erase(baralhoB.begin());
      if(cardA > cardB){
          baralhoA.insert(cardA-cardB);
      }
      else if(cardB > cardA){
          baralhoB.insert(cardB-cardA);
      }
  }
  if(baralhoA.size() != 0){
      return baralhoA.size();
  }
  else return -baralhoB.size();
}

// ----------------------------------------------------------
// Exercicio 3: Reviews Cinematograficas
// ----------------------------------------------------------

// ..............................
// a) Contando Filmes
// TODO
int FunWithBSTs::numberMovies(const vector<pair<string, int>>& reviews) {
    unordered_set<string> s;
  for(auto & review :reviews){
      s.insert(review.first);
  }
  return s.size();
}

// ..............................
// b) O filme com mais reviews
// TODO
void FunWithBSTs::moreReviews(const vector<pair<string, int>>& reviews, int& m, int& n) {
    map <string, int> numReviews;
    m = 2; n=2;
    for(auto & review :reviews){
        if(numReviews.find(review.first) == numReviews.end()){
            numReviews.emplace(review.first,1);
        }
        else{
            numReviews[review.first] += 1;
        }
    }
    for (auto & [key, value] : numReviews) {
        std::cout << key << " " << value << endl;
    }

}

// ..............................
// c) Os melhores filmes
// TODO
vector<string> FunWithBSTs::topMovies(const vector<pair<string, int>>& reviews, double k) {
    vector<string> answer;
    return answer;
}
