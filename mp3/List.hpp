/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */


/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
//  cout<<"in end funtion()\n";
  return List<T>::ListIterator(NULL);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  if (!empty()){ //make sure list is not empty
    ListNode* cur = head_;
    while(cur!=NULL){//traverse list
      cur=cur->next;
      if (cur!=NULL) delete cur->prev; //delete all the prvious (except when at null)
    }
    delete tail_; //only the tail should be left
  }
  length_=0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  if (empty()){//if it is empty just add it to list
    head_= new ListNode(ndata);
    tail_=head_;
    head_->prev=NULL;
    head_->next=NULL;
  }else{//otherwise make it's next head, and it's prev null, it becomes new head
    ListNode* at = new ListNode(ndata);
    head_->prev=at;//update previous pointer of head
    at->next=head_;
    at->prev=NULL;
    head_=at;
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if (empty()){//if it is empty just add it to list
    head_= new ListNode(ndata);
    tail_=head_;
    head_->prev=NULL;
    head_->next=NULL;
  }else{//otherwise make it's prev tail, and it's nell null, it becomes new tail
    ListNode* at = new ListNode(ndata);
    tail_->next=at;
    at->prev=tail_;
    at->next=NULL;
    tail_=at;
  }
  length_++;
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
//  cout<<"starting at: "<<head_->next->data;
  //cout<<" ending at: "<<tail_->prev->data;
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  if (startPoint==NULL || endPoint==NULL){
    cerr<<"YOU CAN'T REVERSE A NULL!"<<endl;
    return;
  }
  if (startPoint==endPoint){
    //cerr<<"Reversing Same thing!"<<endl;
    return;
  }
  ListNode* willbeAt;
  //draw it out to understand these first 6 lines--order matters!
  ListNode* at=startPoint->next;
  startPoint->next=endPoint->next;
  if (endPoint->next!=NULL) endPoint->next->prev=startPoint;//can't assume it's at start of list
  endPoint->next=endPoint->prev;
  endPoint->prev=startPoint->prev;
  if (startPoint->prev!=NULL) startPoint->prev->next=endPoint;
  startPoint->prev=at;
//  cout<<"start,end "<<startPoint->data<<","<<endPoint->data<<endl;
  while(at!=endPoint){
    willbeAt=at->next;//store where we're going next

    at->next=at->prev;//use that value as a temp to swap next and prev
    at->prev=willbeAt;
    at=willbeAt;//makes sense that we will be at what we just set as previous bc we're reversing the list
  }
  //once finished with the loop at will be at endpoint but endpoints next pointer
  //won't be flipped because the loop body doesn't execute when at==endPoint
  //nvm-->i took care of it above the loop
//  cout<<"start,end "<<startPoint->data<<","<<endPoint->data<<endl;

  //finally flip the pointers
  ListNode* temp=startPoint;
  startPoint=endPoint;//this should change the pointers of the callee
  endPoint=temp;//bc they are passed by reference into this function
//  cout<<"start,end "<<startPoint->data<<","<<endPoint->data<<endl;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if (n>=length_){//reverse whole list if n>=length
    reverse();
    return;
  }
  ListNode* at,*start,*end;
  at=head_;//start at head
  //print(cout);
  while(at!=NULL){
  //  print(cout);
    start=at; //start at what you're at
  //  cout<<"starting at "<<start->data<<endl;
    for(int i=0;i<n-1;i++){ //keep going to next n-1 times
      if(at->next==NULL) break;
      at=at->next;
    }
    end =at;//after the loop what you end at is where you want to reverse until (inclusive)
//    cout<<"ending at "<<end->data<<endl;
//    cout<<"pre-reversecall: "<<endl;
//    print(cout);cout<<endl;
    reverse(start,end);
//    cout<<"post-reversecall: "<<endl;
//    print(cout);cout<<endl;
    if (start->prev==NULL) head_=start; //make sure you update head
    if (end->next==NULL) tail_=end;
    at=end->next;//if next is null for loop breaks and then this makes at null
    //makeing the while loop break as well
  }
  //print(cout);cout<<endl;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode* at, *save;
  at=head_;
  int iter=0;
//  cout<<head_->next->data<<" "<<tail_->data<<"\n";
//  print(cout);
  while(at!=tail_ && at!=NULL){
//    cout<<"At: "<<at->data<<"\n";
//    print(cout);
    at=at->next;//doing every other so increment past what you at
    //cout<<at->data.h;
//    cout<<"here?" <<"\n";
    save=at->next; //save the next
    if(at==tail_) return; //could happen when doing second to last one
    //bc then at won't be tail but will become tail a when you increment it to next

//   cout<<"removing " <<at->data<<"\n";
    //remove what you at
    at->prev->next=at->next;
    //if (at->next!=NULL) break;
    at->next->prev=at->prev;
//    cout<<"remove successful" <<"\n";
//    cout<<"adding to tail " <<at->data<<"\n";
    //add at to tail
    tail_->next=at;
    at->prev=tail_;
//    cout<<"added to tail\n";
    tail_=at;//update tail
    at->next=NULL;
    //increment at to be it's next while it was in the list (save)
    at=save;
  }//should break because if at is tail or null, in the loop we only go to at's next

}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  ListNode* at =start;
  for(int i =0;i<splitPoint;i++) at=at->next; //at should be at the return head
  at->prev->next=NULL;
  at->prev=NULL;

  return at;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  if (first && second ==NULL){
    return NULL;
  }

  ListNode* hed,*ans;
  if (second->data < first->data){
    hed=ans=second;
    second=second->next;
  }else{
    hed=ans=first;
    first=first->next;
  }
//  cout<<*this<<endl;
  while(first!=NULL && second!=NULL){
    if (first->data < second->data){//if first is less add that to list and increment first
      ans->next=first;
      first->prev=ans;
      first=first->next;
      ans=ans->next;
    }else{//if second is less, add that to list and increment second
      ans->next=second;
      second->prev=ans;
      second=second->next;
      ans=ans->next;
    }
  }
  if (first==NULL && second ==NULL){//i don't htink this would ever be the case
    ans->next=NULL;
    return hed;
  }
  if(first==NULL){//this means the while loop ended with first list
    while(second!=NULL){
      ans->next=second;
      second->prev=ans;
      second=second->next;
      ans=ans->next;
    }
    ans->next=NULL;
    return hed;
  }
  if(second==NULL){//this means the while loop ended with second list
    while(first!=NULL){
      ans->next=first;
      first->prev=ans;
      first=first->next;
      ans=ans->next;
    }
    ans->next=NULL;
    return hed;
  }
  return hed; //i don't think this would ever be called
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength==1) return start; //base case
  //use your helper functions not theirs!
  ListNode* start2= split(start,chainLength/2);
  int start2len=chainLength- chainLength/2;
  ListNode* head1= mergesort(start,chainLength/2);
  ListNode* head2= mergesort(start2,start2len);
  ListNode* newList= merge(head1,head2);
  return newList;
}
