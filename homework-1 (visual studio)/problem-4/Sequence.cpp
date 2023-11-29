#include "Sequence.h"
#include <iostream>

using namespace std;

Sequence::Sequence() {
    len = 0;
}

bool Sequence::empty() const {
    return (len == 0);
}

int Sequence::size() const {
    return len;
}

int Sequence::insert(int pos, const ItemType& value) {
    if (0 <= pos && pos <= len && len < DEFAULT_MAX_ITEMS) {
        for (int i = len; i > pos; i--)
            sequence[i] = sequence[i - 1];
        sequence[pos] = value;
        len++;
        return pos;
    }
    return -1;
}

int Sequence::insert(const ItemType& value) {
    int pos = len;
    for (int i = 0; i < len; i++)
        if (value <= sequence[i]) {
            pos = i;
            break;
        }
    if (insert(pos, value) == pos)
        return pos;
    return -1;
}

bool Sequence::erase(int pos) {
    if (0 <= pos && pos < len) {
        for (int i = pos; i < len - 1; i++)
            sequence[i] = sequence[i + 1];
        sequence[len - 1] = ItemType();
        len--;
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
    if (0 <= pos && pos < len) {
        value = sequence[pos];
        return true;
    }
    return false;
}

bool Sequence::set(int pos, const ItemType& value) {
    if (0 <= pos && pos < len) {
        sequence[pos] = value;
        return true;
    }
    return false;
}

int Sequence::find(const ItemType& value) const {
    int pos = -1;
    for (int i = len - 1; i >= 0; i--)
        if (sequence[i] == value)
            pos = i;
    return pos;
}

void Sequence::swap(Sequence& other) {
    ItemType temp;
    int max_len = max(len, other.len);
    for (int i = 0; i < max_len; i++) {
        temp = sequence[i];
        sequence[i] = other.sequence[i];
        other.sequence[i] = temp;
    }
    int len_temp = len;
    len = other.len;
    other.len = len_temp;
}

void Sequence::dump() const {
    cerr << "{size: ";
    cerr << len;
    cerr << ", [";
    for (int i = 0; i < len - 1; i++)
    {
        cerr << sequence[i];
        cerr << ", ";
    }
    cerr << sequence[len - 1];
    cerr << "]}" << endl;
}
