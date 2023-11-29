#include "newSequence.h"
#include <iostream>

using namespace std;

Sequence::Sequence() {
    num_items = 0;
    this->max_items = DEFAULT_MAX_ITEMS;
    sequence = new ItemType[DEFAULT_MAX_ITEMS];
}

Sequence::Sequence(int max_items) {
    if (max_items >= 0) {
        num_items = 0;
        this->max_items = max_items;
        sequence = new ItemType[max_items];
    }
    else {
        cerr << "Cannot create a sequence of maximum size " << max_items << "." << endl;
        exit(EXIT_FAILURE);
    }
}

Sequence::~Sequence() {
    delete[] sequence;
}

Sequence::Sequence(const Sequence& other) {
    num_items = other.num_items;
    max_items = other.max_items;
    sequence = new ItemType[other.max_items];
    for (int i = 0; i < other.max_items; i++) {
        sequence[i] = other.sequence[i];
    }
}

Sequence& Sequence::operator=(const Sequence& rhs) {
    if (this != &rhs) {
        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
}
 

bool Sequence::empty() const {
    return (num_items == 0);
}

int Sequence::size() const {
    return num_items;
}

int Sequence::insert(int pos, const ItemType& value) {
    if (0 <= pos && pos <= num_items && num_items < max_items) {
        for (int i = num_items; i > pos; i--)
            sequence[i] = sequence[i - 1];
        sequence[pos] = value;
        num_items++;
        return pos;
    }
    return -1;
}

int Sequence::insert(const ItemType& value) {
    int pos = num_items;
    for (int i = 0; i < num_items; i++)
        if (value <= sequence[i]) {
            pos = i;
            break;
        }
    if (insert(pos, value) == pos)
        return pos;
    return -1;
}

bool Sequence::erase(int pos) {
    if (0 <= pos && pos < num_items) {
        for (int i = pos; i < num_items - 1; i++)
            sequence[i] = sequence[i + 1];
        sequence[num_items - 1] = ItemType();
        num_items--;
        return true;
    }
    return false;
}

int Sequence::remove(const ItemType& value) {
    int pos = find(value);
    int num_removed = 0;
    while (pos != -1) {
        erase(pos);
        pos = find(value);
        num_removed++;
    }
    return num_removed;
}

bool Sequence::get(int pos, ItemType& value) const {
    if (0 <= pos && pos < num_items) {
        value = sequence[pos];
        return true;
    }
    return false;
}

bool Sequence::set(int pos, const ItemType& value) {
    if (0 <= pos && pos < num_items) {
        sequence[pos] = value;
        return true;
    }
    return false;
}

int Sequence::find(const ItemType& value) const {
    int pos = -1;
    for (int i = num_items - 1; i >= 0; i--)
        if (sequence[i] == value)
            pos = i;
    return pos;
}

void Sequence::swap(Sequence& other) {
    ItemType* temp_sequence = sequence;
    sequence = other.sequence;  
    other.sequence = temp_sequence;
    int temp_num_items = num_items;
    num_items = other.num_items;
    other.num_items = temp_num_items;
}

void Sequence::dump() const {
    cerr << "{size: " << num_items << ", [";
    if (num_items > 1) {
        for (int i = 0; i < num_items - 1; i++)
        {
            cerr << sequence[i] << ", ";
        }
        cerr << sequence[num_items - 1] << "]}" << endl;
    }
    else if (num_items == 1) {
        cerr << sequence[0] << "]}" << endl;
    }
    else {
        cerr << "]}" << endl;
    }
}
