#include "funSortProblem.h"
#include <algorithm>

FunSortProblem::FunSortProblem() {}


//-----------------------------------------------------------------

// TODO
void FunSortProblem::expressLane(vector<Product> &products, unsigned k) {
    if (k < products.size()){
        sort(products.begin(), products.end());
        products.erase(products.begin() + k, products.end());
    }
}

// TODO
int FunSortProblem::minDifference(const vector<unsigned> &values, unsigned nc) {
    if(nc > values.size())
        return -1;
    else if(nc == values.size()){
        vector<unsigned > v = values;
        sort(v.begin(), v.end());
        return (v.at(nc-1) - v.at(0));
    }
    vector<unsigned > v = values;
    sort(v.begin(), v.end());
    int min = v.at(nc) - v.at(0);
    for (int i = 0; i <= v.size() - nc; i++) {
        int a = v.at(i+nc-1) - v.at(i);
        if(a < min){
            min = a;
        }
    }
    return min;
}


// TODO
unsigned FunSortProblem::minPlatforms (const vector<float> &arrival, const vector<float> &departure) {
    vector<float> arrive = arrival;
    vector<float> depart = departure;
    sort(arrive.begin(), arrive.end());
    sort(depart.begin(), depart.end());
    int numplatform = 0, max = numplatform , m = 0, n = 0;

    for (int i = 0; i < arrive.size() + depart.size(); i++)
    {
        if(arrive[m] < depart[n]) {
            numplatform++;
            m++;
            if(numplatform > max)
                max = numplatform;
        }
        else if(arrive[m] > depart[n]) {
            numplatform--;
            n++;
            if(numplatform > max)
                max = numplatform;
        }
        else{
            n++;
            m++;
            i++;
            numplatform++;
            if(numplatform > max)
                max = numplatform;
        }
    }
    return max+1;
}


// TODO

void FunSortProblem::nutsBolts(vector<Piece> &nuts, vector<Piece> &bolts) {

}
