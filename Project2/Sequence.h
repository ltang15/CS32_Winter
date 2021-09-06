#ifndef SEQUENCE_H

#define SEQUENCE_H

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

using ItemType = string;


class Sequence
{
public:
    Sequence(); // constructor
    
    Sequence(const Sequence& other); // Copy constructor
    Sequence& operator=(const Sequence& rhs);// Assignment operator
    ~Sequence(); // Destructor

    bool empty() const;
    int size() const;
  
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);

    bool set(int pos, const ItemType& value);
    bool get(int pos, ItemType& value) const;
    int find(const ItemType& value) const;
    void swap(Sequence& other);
   
   
  
    void dump() const;

private:
    struct Node
    {
        ItemType m_data;
        Node* m_next;
        Node* m_prev;
    };

    Node *head;
    Node dummy;
    int m_size;     // size
};


int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif // SEQUENCE_H 