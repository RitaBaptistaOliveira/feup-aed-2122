#ifndef SRC_FUNSP_H_
#define SRC_FUNSP_H_

#include <iostream>
#include <vector>

using namespace std;

class FunSearchProblem{
public:
    FunSearchProblem();
    static int smallestMissingValue(const vector<int> & values);
    static int facingSun(const vector<int> & values);
    static int squareR(int num);
    static int minPages(const vector<int> & values, int numSt);
};

#endif