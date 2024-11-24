#include "heap.hpp"

template <typename Key, typename Value, class Comparator, class Hash>
Heap<Key, Value, Comparator, Hash>::Heap(ll maxsize, Comparator comp, Hash hash) : size(0), maxSize(maxsize), data(new pair<Key, Value>[maxsize]), indexes(new ll[maxsize]), comp(comp), hash(hash) {
    // Input: (int) maxsize, (Comparator) comp, a custom class used to define de priorities,
    // (Hash) has, a custom class to hash the key into the indexes array
    // Complexity: O(maxsize)

    for (ll i = 0; i < maxsize; i++) indexes[i] = -1;
}

template <typename Key, typename Value, class Comparator, class Hash>
Heap<Key, Value, Comparator, Hash>::~Heap() {
    delete[] data; delete[] indexes;
    // Complexity: O(1)
}

template <typename Key, typename Value, class Comparator, class Hash>
ll Heap<Key, Value, Comparator, Hash>::getFather(ll i){
    // Input: (int) i, the index in the heap of the current item
    // Output: (int) returns the index of the father of the current item
    // Complexity: O(1)
    return (i-1)/2;
}

template <typename Key, typename Value, class Comparator, class Hash>
ll Heap<Key, Value, Comparator, Hash>::getLeftChild(ll i){
    // Input: (int) i, the index in the heap of the current item
    // Output: (int) returns the index of the left child of the current item
    // Complexity: O(1)
    return 2 * i + 1;
}

template <typename Key, typename Value, class Comparator, class Hash>
ll Heap<Key, Value, Comparator, Hash>::getRightChild(ll i){
    // Input: (int) i, the index in the heap of the current item
    // Output: (int) returns the index of the right child of the current item
    // Complexity: O(1)
    return 2 * i + 2;
}

template <typename Key, typename Value, class Comparator, class Hash>
bool Heap<Key, Value, Comparator, Hash>::empty()
{
    // Output: (bool) returns if the heap is empty or not
    // Complexity: O(1)
    return size == 0;
}

template <typename Key, typename Value, class Comparator, class Hash>
pair<Key, Value>* Heap<Key, Value, Comparator, Hash>::contains(Key key)
{
    // Input: (Key) key, the key of the element being searched
    // Output: (pair<Key, Value> *) returns a pointer to an element, if it exists
    // Complexity: O(1)

    ll index = indexes[hash(key)];

    if (index == -1) return nullptr;

    return &data[index];
}


template <typename Key, typename Value, class Comparator, class Hash>
void Heap<Key, Value, Comparator, Hash>::insert(Key key, Value value) {

    // Input: (Key) the key of the element being created, (Value) value, the value of the element
    // Complexity: O(log(maxsize))

    if (size == maxSize)
        throw "Heap is full";

    data[size].first = key;
    data[size].second = value;

    indexes[hash(key)] = size;

    heapifyDown(size);

    size++;
}

template <typename Key, typename Value, class Comparator, class Hash>
void Heap<Key, Value, Comparator, Hash>::update(Key key, Value value) {

    // Input: (Key) the key of the element being updated, (Value) value, the new value of the element
    // Complexity: O(log(maxsize))

    pair<Key, Value>* item = contains(key);
    if (item == nullptr)
        throw "Index doesn't exist";

    
    Value temp = item->second;
    item->second = value;

    if (comp(value, temp))    
        heapifyDown(indexes[hash(key)]);
    
    else
        heapifyUp(indexes[hash(key)]);
    
    
    
}

template <typename Key, typename Value, class Comparator, class Hash>
pair<Key, Value> Heap<Key, Value, Comparator, Hash>::remove()
{
    // Complexity: O(log(maxsize))

    if (empty())
        throw "Heap is empty";

    pair<Key, Value> temp = data[0];
    indexes[hash(data[0].first)] = -1; size--;

    if(!empty())
    {
        data[0] = data[size];
        indexes[hash(data[0].first)] = 0;

        heapifyUp(0);
    }

    return temp;
}


template <typename Key, typename Value, class Comparator, class Hash>
void Heap<Key, Value, Comparator, Hash>::heapifyDown(ll pos)
{
    // Input: (int) the index of the element with the position being fixed
    // Complexity: O(log(maxsize))
    ll current = pos, 
    father = getFather(current);

    while (current > 0 && comp(data[current].second, data[father].second))
    {
        pair<Key, Value> temp = data[current];
        data[current] = data[father];
        data[father] = temp;

        ll temp_index = indexes[hash(data[current].first)];
        indexes[hash(data[current].first)] = indexes[hash(data[father].first)];
        indexes[hash(data[father].first)] = temp_index;

        current = father;
        father = getFather(current);
    }   
}

template <typename Key, typename Value, class Comparator, class Hash>
void Heap<Key, Value, Comparator, Hash>::heapifyUp(ll pos)
{
    // Input: (int) the index of the element with the position being fixed
    // Complexity: O(log(maxsize))

    ll current = pos, smallest_child,
    left = getLeftChild(current),
    right = getRightChild(current);

    if (left >= size)
        return;

    else if (right >= size)
        smallest_child = left;

    else smallest_child = comp(data[left].second, data[right].second) ? left : right;

    while (comp(data[smallest_child].second, data[current].second))
    {
        pair<Key, Value> temp = data[current];
        data[current] = data[smallest_child];
        data[smallest_child] = temp;

        ll temp_index = indexes[hash(data[current].first)];
        indexes[hash(data[current].first)] = indexes[hash(data[smallest_child].first)];
        indexes[hash(data[smallest_child].first)] = temp_index;

        current = smallest_child;
        left = getLeftChild(current);
        right = getRightChild(current);

        if (left >= size)
            return;

        else if (right >= size)
            smallest_child = left;

        else smallest_child = comp(data[left].second, data[right].second) ? left : right;
    }

}

Map_Hash_Custom::Map_Hash_Custom(ull rows, ull cols) : rows(rows), cols(cols) {}
    // Complexity: O(log(1))

ull Map_Hash_Custom::operator() (const pair<ull, ull>& key) const {
    return (rows * (key.first) + (key.second));
    // Input: (Key) the key of the element being hashed
    // Complexity: O(1)
}

bool Comp_Dijkstra::operator() (const double& v1, const double& v2) const {
    // Input: (double) v1, (double) v2, the two elements being compared
    // Complexity: O(1)
    return v1 < v2;
}

bool Comp_A_Star::operator() (const pair<double, double>& v1, const pair<double, double>& v2) const {
    // Input: (Tuple<double, double>) v1, (Tuple<double, double>) v2, the two elements being compared
    // Complexity: O(1)
    return v1.second + v1.first < v2.second + v2.first;
}

template class Heap<pair<ull, ull>, double, Comp_Dijkstra, Map_Hash_Custom>;
template class Heap<pair<ull, ull>, pair<double, double>, Comp_A_Star, Map_Hash_Custom>;