// your code here!
#include "potd.h"
#include <cmath>
#include <iostream>
namespace potd{
  int* raise(int *arr){
    int i=0;
    while (arr[i++]!=-1){} //find how long arr is
    int * out = new int[i]; //create an array to return of that size
    for (int x=0;x<i-2;x++){//go through arr until second to last spot
      out[x]=pow(arr[x],arr[x+1]); //raise first thing in arr to next thing
    }
    out[i-2]=arr[i-2]; //preserve last two values of arr
    out[i-1]=arr[i-1];
    return out; //return answer
  }
}
