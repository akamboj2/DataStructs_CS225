/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */

#include "schashtable.h"

using hashes::hash;
using std::list;
using std::pair;

template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new list<pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new list<pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new list<pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     */
     ++elems;
     if (shouldResize())
         resizeTable();
     size_t idx = hash(key, size);
     pair<K, V> p(key, value);
     table[idx].push_front(p);
}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    typename list<pair<K, V>>::iterator it;
    /**
     * @todo Implement this function.
     *
     * Please read the note in the lab spec about list iterators and the
     * erase() function on std::list!
     */
    //(void) key; // prevent warnings... When you implement this function, remove this line.
    if (!keyExists(key)) return;
    size_t idx=hash(key,size);
    for (it=table[idx].begin();it!=table[idx].end();it++){
      if (it->first==key){
        table[idx].erase(it);
        break;
      }
    }
    elems--;
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    /**
     * @todo: Implement this function.
     */
     //return (*this)[key];//defined below, it should return the value of the associated key
     size_t idx = hash(key, size);
     typename list<pair<K, V>>::iterator it;
     for (it = table[idx].begin(); it != table[idx].end(); it++) {
         if (it->first == key)
             return it->second;
     }
     return V();//if key doesn't exist return default
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hash(key, size);
    pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hash(key, size);
    typename list<pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new list<pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    typename list<pair<K, V>>::iterator it;
    /**
     * @todo Implement this function.
     *
     * Please read the note in the spec about list iterators!
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
     size_t newsize= findPrime(2*size);
     list<pair<K,V>>* newtab;
     newtab=new list<pair<K,V>>[newsize];

     for(unsigned i=0;i<size;i++){ //go through entire old array of lists
       typename list<pair<K, V>>::iterator it;
       for (it = table[i].begin(); it != table[i].end(); it++) {//go through each element in that list
         K key=it->first;
         V value=it->second;
         size_t idx = hash(key, newsize); //hash that key and value to the new array
         pair<K, V> p(key, value);
         newtab[idx].push_front(p);//push it onto the new list
       }
     }
     delete [] table;
     table=newtab;
     size=newsize;
}