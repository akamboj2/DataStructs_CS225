/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 */
#include "lphashtable.h"
#include <iostream>
using hashes::hash;
using std::pair;
using std::cout;
using std::endl;

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >= 0.7).
     * **Do this check *after* increasing elems (but before inserting)!!**
     * Also, don't forget to mark the cell for probing with should_probe!
     */

    //(void) key;   // prevent warnings... When you implement this function, remove this line.
    //(void) value; // prevent warnings... When you implement this function, remove this line.
    //pair<K,V> p(key,value);
    elems++;
    if (shouldResize()) resizeTable();

    size_t idx=hash(key,size);
    while(table[idx]!=NULL) {
      idx++;
      if(idx>=size) idx%=size;
    }
    table[idx]= new pair<K,V>(key,value);

}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo: implement this function
     */
     int idx=findIndex(key);
     if (idx!=-1){
       elems--;
       delete table[idx];
       table[idx]=NULL;
     }
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{

    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */
     unsigned idx=hash(key,size);
     unsigned i=idx;
     if (table[i]!=NULL && table[i]->first==key) return i; //if your at element that's great!
     i++;
     if (i>=size) i%=size;
     while(i!=idx){
       //otherwise just keep going around until you find it! or reach where you started
       //cout<<"About to segfault: "<<table[i]<<endl;
//       cout<<"i is "<<i<<" size is "<<size<<" idx is "<<idx<<endl;
//       if (table[i]!=NULL) cout<<"Table's first "<<table[i]->first<<endl;
       if (table[i]!=NULL && table[i]->first==key) return i;
       i+=1;
//       cout<<"btm of loop: i is "<<i<<" size is "<<size<<endl;
       if (i>=size) i%=size;
//       cout<<"After change: i is "<<i<<" size is "<<size<<endl;
     }
    return -1;//if you reached where you started then it's not in here!
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
//    cout<<"NEW CALL TO findIndex:"<<endl;
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{

    /**
     * @todo Implement this function
     *
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
     size_t newsize=findPrime(size*2);
     pair<K, V>** newtable = new pair<K,V>*[newsize];
     bool* spnew= new bool[newsize];
     for(unsigned i =0;i<newsize;i++) {
       newtable[i]=NULL;//make sure it's ok to not be doing
       spnew[i]=false;
     }
     //go through entire old table and rehash every element
     for(unsigned i = 0;i<size;i++){
       if (table[i]==NULL) continue;
       K key=table[i]->first;
       V value=table[i]->second;
       size_t idx=hash(key,newsize);

       while(newtable[idx]!=NULL) {//inserting algorithm--there must be some nulls bc size is not full
         idx++;
         if(idx>=newsize) idx%=newsize;
       }
       newtable[idx]= new pair<K,V>(key,value);
       spnew[idx]=true;
     }




         for (size_t i = 0; i < size; i++)
             delete table[i];
         delete[] table;
         delete[] should_probe;

         table=newtable;
         size=newsize;
         should_probe=spnew;
}
