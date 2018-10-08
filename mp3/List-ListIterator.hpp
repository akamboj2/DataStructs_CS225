
class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    ListNode* position_;

  public:
    ListIterator() : position_(nullptr) { }
    ListIterator(ListNode* x) : position_(x) { }

    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in MP3.1
        position_=position_->next;
        return *this;
    }

    // Post-Increment, iter++
    ListIterator operator++(int) {
        ListNode* temp = position_;
        position_ = position_->next;
      //  if(position_==NULL) cout<<"iter is now a null list iterator!"<<endl;
        return ListIterator(temp);
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        position_ = position_->prev;
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in MP3.1
  //      cout<<"Called post decrement\n";
        ListNode* tem=position_;
    //    cout<<" is at "<<position_->data<<" next is "<<position_->next->data<<" prev is "<<position_->prev->data<<endl;
        if (position_!=NULL) position_=position_->prev;
    //    cout<<" now is at "<<(position_==NULL)<<" "<<position_->data<<endl;

        return ListIterator(tem);
    }

    bool operator==(const ListIterator& rhs) {
    //    cout<<"comparing==: "<<position_<<" and "<<rhs.position_<<endl;
        return !(*this != rhs);
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in MP3.1
        //if (*position_!=*(rhs.position_)) return true; //might instead need to compare position_->data
        //but is iterator equal when just data there is equal? or before and after is equal as well?
        //or the whole list is equal??<-- probs not that
      //  cout<<"comparing!=: "<<position_<<" and "<<rhs.position_<<endl;

        //need to consider case when position_==null;
        if (position_==NULL && rhs.position_==NULL) return false;

        //what about if position_ is NULL but rhs.pos_ is not?--then they're defs not equal
        if (position_==NULL || rhs.position_==NULL) return true;
        if (position_->data!=rhs.position_->data) return true;
        return false;
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};
