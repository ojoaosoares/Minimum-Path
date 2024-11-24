#ifndef HEAP_HPP
#define HEAP_HPP

#include <utility>

typedef long long ll;

typedef unsigned long long ull;

using namespace std;

template <typename Key, typename Value, class Comparator, class Hash>
class Heap{

    public:
        Heap(ll maxsize, Comparator comp, Hash hash);
        ~Heap();

        void insert(Key key, Value value);
        pair<Key, Value>* contains(Key key);
        void update(Key key, Value value);
        pair<Key, Value> remove();

        bool empty();

    private:
        ll getFather(ll pos);
        ll getLeftChild(ll pos);
        ll getRightChild(ll pos);

        ll size;
        ll maxSize;

        pair<Key, Value> *data;
        ll *indexes;

        Comparator comp;
        Hash hash;

        void heapifyDown(ll pos);
        void heapifyUp(ll pos);
};

class Map_Hash_Custom {

    private:
        ull rows, cols;

    public:
        Map_Hash_Custom(ull rows, ull cols);
        ull operator() (const pair<ull, ull> &key) const;

};

class Comp_Dijkstra {
    public:
        bool operator() (const double& v1, const double& v2) const;

};

class Comp_A_Star {
    public:
        bool operator() (const pair<double, double>& v1, const pair<double, double>& v2) const;
};

class Comp_Greedy {
    public:
        bool operator() (const pair<double, double>& v1, const pair<double, double>& v2) const;
};

#endif