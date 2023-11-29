/**
 * CS 32, Project 2, Sequence.h
 * Name: Niklas Leet
 * UID: 405795083
 * Date: 4/24/2023
*/

#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <string>
// #include "IntWrapper.h"

// using ItemType = unsigned long;
// using ItemType = IntWrapper;
using ItemType = std::string;

class Sequence
{
    public:
        Sequence();
        Sequence(const Sequence& other);
        ~Sequence();
        Sequence& operator=(const Sequence& rhs);
        bool empty() const;
        int size() const;
        int insert(int pos, const ItemType& value);
        int insert(const ItemType& value);
        bool erase(int pos);
        int remove(const ItemType& value);
        bool get(int pos, ItemType& value) const;
        bool set(int pos, const ItemType& value);
        int find(const ItemType& value) const;
        void swap(Sequence& other);
        void dump();
    private:
        struct Node {
            struct Node* m_prev;
            struct Node* m_next;
            ItemType m_data;
        };
        Node* m_head;
        Node* getNode(int pos) const;
        int m_size;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif // SEQUENCE_H INCLUDED