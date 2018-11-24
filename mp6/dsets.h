/* Your code here! */
#pragma once

#include <vector>
#include <cmath>

class DisjointSets {
public:
	void addelements(int a);
	int find(int a);
	void setunion(int c, int d);
	int size(int a);
	std::vector<int> arr;

};
