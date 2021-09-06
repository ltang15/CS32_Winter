#ifndef SEQUENCE_H

#define SEQUENCE_H

#include <iostream>
#include <string>
using namespace std;

using ItemType = unsigned long;

const int DEFAULT_MAX_ITEMS = 150;

class Sequence
{
public:
    Sequence();    // Constructor

    
    bool empty() const;  // Return true if the sequence is empty, otherwise false.
    
    //Mutator
    int insert(int pos, const ItemType& value); 
    int insert(const ItemType& value);
    bool erase(int pos); 
    int remove(const ItemType& value);    
    bool set(int pos, const ItemType& value); 
    void swap(Sequence& other);

    // Accessor
    bool get(int pos, ItemType& value) const;
    int find(const ItemType& value) const;
    int size() const;    // Return the number of items in the sequence.
    void dump() const;
private:
    ItemType m_seq[DEFAULT_MAX_ITEMS];
    int m_size;

};


#endif // SEQUENCE_H