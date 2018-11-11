/* Your code here! */
#include "dsets.h"
#include <cstdlib>
void DisjointSets::addelements(int a){
	for(int i = 0; i < a; i++){
		arr.push_back(-1);
	}
}

int DisjointSets::find(int a){
  //will break if a> arr.size()
	if ( arr[a] < 0 ) { return a; } else { return find(arr[a]); }

}

void DisjointSets::setunion(int c, int d){

	int a = find(c);
	int b = find(d);

	int newSize = arr[a] + arr[b];
	// If arr_[root1] is less than (more negative), it is the larger set; // we union the smaller set, root2, with root1.
	if ( arr[a] < arr[b] ) {
	    arr[b] = a;
	    arr[a] = newSize;
	}
	// Otherwise, do the opposite:
	else {
		arr[a] = b;
	    arr[b] = newSize;
	}

}

int DisjointSets::size(int a){
	int idx = find(a);
	return std::abs(arr[idx]);
}
