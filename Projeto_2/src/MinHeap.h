#ifndef FEUP_AED_PROJ2_MINHEAP_H
#define FEUP_AED_PROJ2_MINHEAP_H

#include <vector>
#include <unordered_map>

#define LEFT(i) (2*(i))
#define RIGHT(i) (2*(i)+1)
#define PARENT(i) ((i)/2)

using namespace std;

template <class K, class V>
class MinHeap {
    struct Node {
        K key;
        V value;
    };

    int size;
    int maxSize;
    vector<Node> a;
    unordered_map<K, int> pos;
    const K KEY_NOT_FOUND;

    void upHeap(int i);
    void downHeap(int i);
    void swap(int i1, int i2);

public:
    MinHeap(int n, const K& notFound);
    int getSize();
    bool hasKey(const K& key);
    void insert(const K& key, const V& value);
    void decreaseKey(const K& key, const V& value);
    K removeMin();
};

// ----------------------------------------------

/**
 * Makes a value go "up the tree" until it reaches its position
 */
template <class K, class V>
void MinHeap<K,V>::upHeap(int i) {
    while (i>1 && a[i].value < a[PARENT(i)].value) { // while pos smaller than parent, keep swapping to upper position
        swap(i, PARENT(i));
        i = PARENT(i);
    }
}

/**
 * Make a value go "down the tree" until it reaches its position
 */
template <class K, class V>
void MinHeap<K,V>::downHeap(int i) {
    while (LEFT(i) <= size) { // while within heap limits
        int j = LEFT(i);
        if (RIGHT(i)<=size && a[RIGHT(i)].value < a[j].value) j = RIGHT(i); // choose smaller child
        if (a[i].value < a[j].value) break;   // node already smaller than children, stop
        swap(i, j);                    // otherwise, swap with smaller child
        i = j;
    }
}

/**
 * Swap two positions of the heap (update their positions)
 */
template <class K, class V>
void MinHeap<K,V>::swap(int i1, int i2) {
    Node tmp = a[i1]; a[i1] = a[i2]; a[i2] = tmp;
    pos[a[i1].key] = i1;
    pos[a[i2].key] = i2;
}

// ----------------------------------------------

/**
 * Create a min-heap for a max of n pairs (K,V) with notFound returned when empty
 */
template <class K, class V>
MinHeap<K,V>::MinHeap(int n, const K& notFound) : KEY_NOT_FOUND(notFound), size(0), maxSize(n), a(n+1) {
}

 /**
  * @return the size of the min heap
  */
template <class K, class V>
int MinHeap<K,V>::getSize() {
    return size;
}

/**
 * Checks if the key exists in the heap
 * @param key Value of the key
 * @return True if the key exists and false otherwise
 */
template <class K, class V>
bool MinHeap<K, V>::hasKey(const K& key) {
    return pos.find(key) != pos.end();
}

/**
 * Inserts the key and the value on the heap and adjusts their placement
 * @param key Value of the key
 * @param value Value associated with the key
 */
template <class K, class V>
void MinHeap<K,V>::insert(const K& key, const V& value) {
    if (size == maxSize) return; // heap is full, do nothing
    if (hasKey(key)) return;     // key already exists, do nothing
    a[++size] = {key, value};
    pos[key] = size;
    upHeap(size);
}

/**
 * Decreases the value of key to the indicated value
 * @param key Value of the key
 * @param value Value associated with the key
 */
template <class K, class V>
void MinHeap<K,V>::decreaseKey(const K& key, const V& value) {
    if (!hasKey(key)) return; // key does not exist, do nothing
    int i = pos[key];
    if (value > a[i].value) return; // value would increase, do nothing
    a[i].value = value;
    upHeap(i);
}

/**
 * Removes and returns the key with the smallest value
 * @return KEY_NOT_FOUND if the heap is empty or the key with the smallest value otherwise
 */
template <class K, class V>
K MinHeap<K,V>::removeMin() {
    if (size == 0) return KEY_NOT_FOUND;
    K min = a[1].key;
    pos.erase(min);
    a[1] = a[size--];
    downHeap(1);
    return min;
}

#endif

