#include "funSearchProblem.h"

FunSearchProblem::FunSearchProblem() {}

//-----------------------------------------------------------------

// TODO
int FunSearchProblem::facingSun(const vector<int> & values) {
    int maxHeight = 0;
    int count = 0;
    if (values.size() == 0)
        return count;
    for (int i = 0; i < values.size(); i++){
        if (values[i] > maxHeight) {
            count++;
            maxHeight = values[i];
        }
    }
    return count;
}

// TODO
int FunSearchProblem::squareR(int num) {
    int mid = num/2; int left = 1; int right = num;
    int square;
    while(left <= right){
        square = mid*mid;
        if (num == square){
            return mid;
        }
        else if (num < square){
            right = mid - 1;
        }
        else if (num > square){
            left = mid + 1;
        }
        mid = (left + right)/2;
    }
    return left-1;
}

// TODO
int FunSearchProblem::smallestMissingValue(const vector<int> & values) {
    return 0;
}

// TODO
int FunSearchProblem::minPages(const vector<int> & values, int numSt) {
    return 0;
}

