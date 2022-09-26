#include <iostream>
#include <vector>

using namespace std;

template <class T>
class MyVector {
    vector<T> values;
public:
    MyVector();
    ~MyVector();
    void push_back(T v1);
    void fillVector(int size);
    vector<T> getValues() const;
    T max() const;
    bool hasDuplicates() const;
    void removeDuplicates() ;
};


// exception EmptyVector
class EmptyVector
{ };

// methods
template <class T>
MyVector<T>::MyVector() {}

template <class T>
MyVector<T>::~MyVector() {}

template <class T>
void MyVector<T>::push_back(T v1) {
    values.push_back(v1);
}

template <class T>
vector<T> MyVector<T>::getValues() const {
    return values;
}

//---------------------------------

// TODO
template <class T>
T MyVector<T>::max() const {
    T vmax;
    if (values.size() == 0)
        throw EmptyVector();
    vmax = values[0];
    for(int i = 0; i < values.size(); i++)
    {
        if (vmax <= values[i])
            vmax = values[i];
    }
	return vmax;
}

// TODO
template<class T>
bool MyVector<T>::hasDuplicates() const {
    for (int i = 0; i < values.size(); i++)
    {
        T v1 = values[i];
        for (int j = i+1; j < values.size(); j++)
        {
            if (v1 == values[j])
                return true;
        }
    }
	return false;
}

// TODO
template<class T>
void MyVector<T>::removeDuplicates() {
    for (int i = 0; i < values.size(); i++)
    {
        T v1 = values[i];
        for (int j = i+1; j < values.size(); j++)
        {
            if (v1 == values[j]) {
                values.erase(values.begin()+j);
                j--;
            }
        }
    }
}

template<class T>
void MyVector<T>::fillVector(int size) {
    for (int i = 0; i < size; i++){
        T v1;
        v1 = rand();
        push_back(v1);
    }

}

