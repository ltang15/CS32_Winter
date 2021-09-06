#ifndef NEWSEQUENCE_H

#define NEWSEQUENCE_H

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

using ItemType = unsigned long;

const int DEFAULT_MAX_ITEMS = 150;

class Sequence
{
public:
    Sequence(); // no parameter constructor
    Sequence(int cap); // 1 parameter constructor
    Sequence(const Sequence& other); // Copy constructor

    Sequence& operator=(const Sequence& rhs);// Assignment operator
    ~Sequence(); // Destructor

    bool empty() const; 

    // Mutator
      
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool set(int pos, const ItemType& value);
    void swap(Sequence& other);

    // Accessor
    int find(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    int size() const;
    void dump() const;

private:
    ItemType *m_seq; // Array of pointers
    int m_size;     // size
    int m_capacity; // capacity

};

#endif // NEWSEQUENCE_H