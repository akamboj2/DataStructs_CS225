
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <iostream>
using std::endl;
using std::cout;
template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    return 2*currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    return 2*currentIdx+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if(currentIdx*2<_elems.size()) return true;
    return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t i) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    if (i*2+1==_elems.size())//this means no right element exists!
      return leftChild(i);

//    if (_elems[i]==99) cout<<"comparing maxPriority of "<<_elems[i]<<endl;
//    cout<<"\t"<<_elems[leftChild(i)]<<" "<<_elems[rightChild(i)]<<endl;

    return (higherPriority(_elems[leftChild(i)],_elems[rightChild(i)]) ? leftChild(i):rightChild(i));
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t i)
{
    // @TODO Implement the heapifyDown algorithm.
//    if (_elems[i]==99)
//      cout<<"heaping down on 99"<<endl;
    if(!hasAChild(i)) return;
    size_t child = maxPriorityChild(i);
    if (higherPriority(_elems[child],_elems[i])){
      T temp=_elems[child];
      _elems[child]=_elems[i];
      _elems[i]=temp;
      heapifyDown(child);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T()); //IGNORE THIS ELEMENT!
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems.push_back(T()); //IGNORE THIS ELEMENT!
    // for(auto i:elems) push(i);
    // std::sort(_elems.begin(),_elems.end());
    for(auto e:elems) _elems.push_back(e);
    for(unsigned i=parent(_elems.size()-1);i>0;i--){
      heapifyDown(i);
    }
    // _elems=elems;
    // for(unsigned i=0;i<_elems.size()/2;i++){
    //   heapifyDown(_elems[i]);
    // }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    T ret=_elems[1];
//    cout<<"Popping "<<ret<<endl;
    std::swap(_elems[1],_elems.back());
//    cout<<"now back is "<<_elems.back()<<endl;

    _elems.pop_back();
    // cout<<"Before heapDown ";
    // for (unsigned i=1;i<_elems.size();i++){
    //   cout<<_elems[i]<<" ";
    // }
    // cout<<endl;
    heapifyDown(1);
    // cout<<"Post heapDown ";
    // for (unsigned i=1;i<_elems.size();i++){
    //   cout<<_elems[i]<<" ";
    // }
    // cout<<endl;
    return ret;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
//     cout<<"Pushed element "<<elem<<endl;
    //cout<<*this<<endl;
    // for (unsigned i=1;i<_elems.size();i++){
    //   cout<<_elems[i]<<" ";
    // }
    // cout<<endl;
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    size_t i=idx+1;//bc we start indexing at 1;

//    cout<<"Updating element at idx: "<<i<<" with "<<elem;
    _elems[i]=elem;
    if (i==root()) heapifyDown(i);
    else
      if(!hasAChild(i)) heapifyUp(i);
      else
        if(higherPriority(_elems[i], _elems[parent(i)])) heapifyUp(i);
        else heapifyDown(i);
  //  cout<<*this;
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return !(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
