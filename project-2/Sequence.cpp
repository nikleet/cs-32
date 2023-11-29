/**
 * CS 32, Project 2, Sequence.cpp
 * Name: Niklas Leet
 * UID: 405795083
 * Date: 4/24/2023
*/

#include "Sequence.h"
#include <iostream>

using namespace std;

// In the following comments, "item" and "Node" are used interchangeably

// Default constructor - cosntructs an empty Sequence with only a dummy node
Sequence::Sequence() {
	m_head = new Sequence::Node;
	m_head->m_next = m_head;
	m_head->m_prev = m_head;
	m_size = 0;
}

// Copy constructor
Sequence::Sequence(const Sequence& other)
	: Sequence() {
	int idx = 0;
	for (Node* p = other.m_head->m_next; p != other.m_head; p = p->m_next) {
		ItemType data = p->m_data;
		insert(idx, data);
		idx++;
	}
	m_size = other.m_size;
}

// Destructor
Sequence::~Sequence() {
	while(m_size > 0) {
		erase(0);
	}
	delete m_head;
}

// operator= (copy and swap)
Sequence& Sequence::operator=(const Sequence& rhs) {
	if (this != &rhs) {
		Sequence temp(rhs);
		swap(temp);
	}
	return *this;
}

// returns true if Sequence is empty, false otherwise
bool Sequence::empty() const {
	return (m_size == 0);
}

// returns the number of Nodes in the Sequence (excluding the dummy node)
int Sequence::size() const {
	return m_size;
}

// inserts a new Node at index pos with data of ItemType value
// if 0 <= pos <= the size of the Sequence, returns pos; returns -1 otherwise
int Sequence::insert(int pos, const ItemType& value) {
	if (0 <= pos && pos <= m_size) {
		Node* newNode = new Node;
		Node* p = getNode(pos - 1);
		newNode->m_data = value;
		// link newNode with new neighbors
		newNode->m_next = p->m_next;
		newNode->m_prev = p;
		// link neighbors with newNode
		p->m_next->m_prev = newNode;
		p->m_next = newNode;
		m_size++;
		return pos;
	}
	return -1;
}

// isnerts a new Node at the position before first Node which has a value 
// greater than this one, then returns that position
int Sequence::insert(const ItemType& value) {
	int pos = 0;
	for (Node* p = m_head->m_next; p != m_head; p = p->m_next) {
		if (value <= p->m_data)
			break;
		pos++;
	}
	insert(pos, value);
	return pos;
}

// if 0 <= pos < the size of the Sequence, erases the target Node at position pos
// from the Sequence and returns true; returns false otherwise
bool Sequence::erase(int pos) {
	if (0 <= pos && pos < m_size) {
		Node* p = getNode(pos);
		// make the predecessor of the Node following the target Node the
		// Node before the target Node
		p->m_next->m_prev = p->m_prev;
		// make the successor of the Node before the target Node the Node
		// following the target Node
		p->m_prev->m_next = p->m_next;
		delete p;
		m_size--;
		return true;
	}
	return false;
}

// erases all Nodes from the Sequence for which data == value and returns the
// number removed
int Sequence::remove(const ItemType& value) {
	int pos = find(value);
	int removed = 0;
	while (pos != -1) {
		erase(pos);
		removed++;
		pos = find(value);
	}
	return removed;
}

// if 0 <= pos < the size of the Sequence, stores the data of the item at pos in 
// value and returns true; returns false otherwise
bool Sequence::get(int pos, ItemType& value) const {
	if (0 <= pos && pos < m_size) {
		value = getNode(pos)->m_data;
		return true;
	}
	return false;
}

// if 0 <= pos < size of the Sequence, stores the data in the Node at position 
// pos in value and returns true; returns false otherwise
bool Sequence::set(int pos, const ItemType& value) {
	if (0 <= pos && pos < m_size) {
		getNode(pos)->m_data = value;
		return true;
	}
	return false;
}

// returns the position of the first item with data that equals value and
// returns -1 if no such item can be found
int Sequence::find(const ItemType& value) const {
	int idx = 0;
	int pos = -1;
	for (Node* p = m_head->m_next; p != m_head; p = p->m_next) {
		if (value == p->m_data) {
			pos = idx;
			break;
		}
		idx++;
	}
	return pos;
}

// swaps the contents of two Sequences
void Sequence::swap(Sequence& other) {
	Node* temp_head = m_head;
	m_head = other.m_head;
	other.m_head = temp_head;
	int temp_size = m_size;
	m_size = other.m_size;
	other.m_size = temp_size;
}

// returns a pointer to the node at pos if pos is valid; returns m_head otherwise
Sequence::Node* Sequence::getNode(int pos) const {
	// using this function within a loop is discouraged (for efficiency)
	if (0 <= pos && pos < m_size) {
		Node* p = m_head->m_next;
		for (int i = 0; i < pos; i++)
			p = p->m_next;
		return p;
	}
	return m_head;
}

// prints the size and contents of a sequence -- used for testing
void Sequence::dump() {
	cerr << "{size: " << m_size << ", [";
	if (m_size >= 1) {
		for (Node* p = m_head->m_next; p != m_head->m_prev; p = p->m_next) {
			cerr << p->m_data << ", ";
		}
		cerr << m_head->m_prev->m_data << "]}" << endl;
	}
	else {
		cerr << "]}" << endl;
	}
}

// if the items of seq2 appear consecutively in seq1, returns the index in seq1 
// where the subsequence identical seq2 can be found, and returns -1 if no such
// subsequence can be found
int subsequence(const Sequence& seq1, const Sequence& seq2) {
	if (&seq1 == &seq2)
		return 0;
	if (seq1.size() > 0 && seq2.size() > 0) {
		int idx_subseq = -1;
		int idx2 = 0;
		ItemType item1;
		ItemType item2;
		for (int i = 0; i < seq1.size(); i++) {
			seq1.get(i, item1);
			seq2.get(idx2, item2);
			if (item1 == item2) {
				idx2++;
				if (idx_subseq == -1)
					idx_subseq = i;
			}
			else {
				idx_subseq = -1;
				idx2 = 0;
			}
			if (idx2 == seq2.size()) {
				return idx_subseq;
			}
		}
	}
	return -1;
}

// erase all items in result and insert into result the contents of seq1 in 
// reverse order followed by the contents of seq2 in reverse order
void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result) {
	Sequence s1 = seq1;
	Sequence s2 = seq2;
	int size1 = s1.size();
	int size2 = s2.size();
	while (result.size() > 0)
		result.erase(0);
	for (int i = size1 - 1; i >= 0; i--) {
		ItemType item;
		s1.get(i, item);
		result.insert(size1 - i - 1, item);
	}
	for (int i = size2 - 1; i >= 0; i--) {
		ItemType item;
		s2.get(i, item);
		result.insert(size1 + size2 - i - 1, item);
	}
}