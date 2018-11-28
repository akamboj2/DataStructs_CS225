/* Your code here! */
#pragma once

#include <vector>
#include <cmath>
#include "dsets.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <stack>
#include <unordered_map>
#include <ctime>

using namespace std;
using namespace cs225;

class SquareMaze {
public:
	SquareMaze();
	void makeMaze(int width, int height);
	bool canTravel(int x, int y, int dir) const;
	void setWall(int x, int y, int dir, bool exists);
	vector<int> solveMaze();
	PNG* drawMaze() const;
	PNG* drawMazeWithSolution();
	void solve(int,int,int);
private:
	int width_;
	int height_;
	DisjointSets dset;
	vector<pair<int, int>> walls; //<right wall,btm wall> (1 if there is wall)
	unordered_map<int,pair<int,int>> mazemap;
};
