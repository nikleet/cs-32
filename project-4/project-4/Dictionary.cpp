/**
 * CS 32, Project 4, Dictionary.cpp
 * Name: Niklas Leet
 * UID: 405795083
 * Date: 6/5/2023
*/

// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include <functional>
#include <algorithm>

using namespace std;

void removeNonLetters(string& s);

  // This class does the real work of the implementation.


class DictionaryImpl
{
    public:
        DictionaryImpl(int maxBuckets = 50000);
        ~DictionaryImpl() { delete[] m_words; }
        void insert(string word);
        void lookup(string letters, void callback(string)) const;
    private:
        struct Entry {
            string word;
            string sorted;
        };
        int m_buckets;
        list<Entry>* m_words;
        // this function hash() modifies s, sorting the characters string s alphabetically
        unsigned int hash(string& s) const;
};


DictionaryImpl::DictionaryImpl(int maxBuckets) 
{
    m_buckets = maxBuckets;
    m_words = new list<Entry>[maxBuckets]; 
}

/*
    This function simply sorts the string parameter s alphabetically using std::sort, and returns the result
    of the std::hash function applied to the sorted string % the number of buckets. Note that std::sort sorts
    s in place, and s is allowed to be modified by the function, so s will be sorted after hash is called.
    By using std::hash % number of buckets we generate a fairly uniform distribution of keys across our hash
    table which are sufficiently unique to minimize accidental collisions. Sorting the string before calling
    std::hash ensures that anagrams of the same set of characters will always generate the same key, and hence
    will be stored in the same bucket.
*/
unsigned int DictionaryImpl::hash(string& s) const
{
    std::sort(s.begin(), s.end());
    return std::hash<string>().operator()(s) % m_buckets;
}

/*
    When the user inserts a new dictionary entry, the default (from the spec) implementation of removeNonLetters
    is called first. Then, the hash function is called on a copy of the parameter word, and this copy is 
    alphabetically sorted by the hash function. Then, the word and its sorted copy are sotred in an Entry object
    and that Entry is pushed back onto the list at the position in m_words keyed by the hash function.
*/
void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    string sorted_word(word);
    int key = hash(sorted_word);
    Entry entry;
    entry.word = word;
    entry.sorted = sorted_word;
    m_words[key].push_back(entry);
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

    string sorted_letters(letters);
    int key = hash(sorted_letters);

    list<Entry>* bucket = &m_words[key];
    
    for (list<Entry>::iterator entryp = bucket->begin(); entryp != bucket->end(); entryp++)
    {
        // these if statements check for accidental collisions
        // comparing the sizes is O(1) and is a good first line of defence
        if ((*entryp).sorted.size() == sorted_letters.size())
            // this comparison ensures the entry and letters are actually anagrams
            if ((*entryp).sorted == sorted_letters)
                callback((*entryp).word);
    }
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
} 


//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
