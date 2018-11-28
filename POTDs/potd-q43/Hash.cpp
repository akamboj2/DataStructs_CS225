#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Hash.h"
using namespace std;
unsigned long bernstein(std::string str, int M)
{
	unsigned long b_hash = 5381;
	for (int i = 0; i < (int) str.length(); ++i)
	{
		b_hash = b_hash * 33 + str[i];
	}
	return b_hash % M;
}

float hash_goodness(std::string str, int M)
{
    std::vector<int>* array = new std::vector<int>(M,0);	// Hint: This comes in handy
	int permutation_count = 0;
	float goodness = 0;
	//cout<<"array is filled with "<<(*array)[M/2]<<endl;

	do {
		if (permutation_count == M) {cout<<"permuation count being broken"<<endl;break;}
		// Code for computing the hash and updating the array
		long hash=bernstein(str,M);
		((*array)[hash])++;
		permutation_count++;
	} while(std::next_permutation(str.begin(), str.end()));

	//Code for determining goodness
	double collisions =0;

	for (unsigned i=0;i<(*array).size();i++){
		if (M==51) cout<<i<<": "<<(*array)[i]<<endl;
		if ((*array)[i]>1){
			collisions+=(*array)[i]-1;
		}
	}
	cout<<permutation_count<< " "<<collisions<< " "<<M<<endl;
	goodness=collisions/M;
	return goodness;
}
