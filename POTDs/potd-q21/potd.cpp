#include "potd.h"

// Your code here!
/** Returns the sum of elements between start to end.
	The value at start is included, while the value at end is not.
	*/
double sum(vector<double>::iterator start, vector<double>::iterator end){
  double sum=0;
  for(vector<double>::iterator it=start;it!=end;it++){
    sum+=*it;
  }
  return sum;
}

/** Returns an iterator that points to the element with the largest value between start and end. */
vector<double>::iterator max_iter(vector<double>::iterator start, vector<double>::iterator end){
  vector<double>::iterator max_it = start;
  for(vector<double>::iterator it=start;it!=end;it++){
    max_it=(*it>*max_it ? it:max_it);
  }
  return max_it;
}

/** Sort, in descending order, part of an array between start to end.
	Hint: use max_iter.
*/
void sort_vector(vector<double>::iterator start, vector<double>::iterator end){
  for(vector<double>::iterator it=start;it!=end;it++){
    double temp=*it;
    vector<double>::iterator max=max_iter(it,end);
    *it=*max;
    *max=temp;
  }
}
