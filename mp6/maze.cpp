/* Your code here! */
#include "maze.h"
#include <vector>
#include <iostream>

SquareMaze::SquareMaze(){
	width_ = 0;
	height_ = 0;
	srand(time(0));
	// dset.arr = new vector...
	// walls = new vector...
}

void SquareMaze::makeMaze(int width, int height){

	width_ = width;
	height_ = height;
	(dset.arr).clear();
	dset.addelements(width_ * height_);

	for(int i = 0; i < width_ * height_; i++){
		walls.push_back(make_pair(1, 1));
	}

	while(dset.size(0) != width_ * height_){

		if(width_ == 1 && height_ == 1){
			return;
		}

		// 1. randomly select a point --> inclusive?
		int point_1 = rand() % (width_ * height_);

		// 2. randomly select a neighboring point
		int point_2;
		pair<int, int> n_dir;

		if(point_1 == width_ * height_ - 1){
			continue;
		} else if( (point_1 + 1) % width_ == 0){
			// only bottom is valid
			point_2 = point_1 + width_;
			n_dir = make_pair(0, 1);
		} else if(point_1 >= (width_ * height_) - width_){
			// only right is valid
			point_2 = point_1 + 1;
			n_dir = make_pair(1, 0);
		} else {
			// random: either 0 or 1
			int rand_num = rand() % 2;
			if(rand_num == 0){
				point_2 = point_1 + width_;//point below
				n_dir = make_pair(0, 1);
			} else {
				point_2 = point_1 + 1;//point to the right
				n_dir = make_pair(1, 0);
			}
		}

		// 3. if the two are in the same set, continue
		//    else, union them
		if(dset.find(point_1) != dset.find(point_2)){
			// cout << "Joining cells: " << point_1 << " and " << point_2 << endl;

			// update walls vector
			if(n_dir == make_pair(0, 1)){

				// break bottom wall
				walls[point_1].second = 0;

			} else {

				// break right wall
				walls[point_1].first = 0;

			}

			dset.setunion(point_1, point_2);

		}

	}

}

bool SquareMaze::canTravel(int x, int y, int dir) const {

	// assuming 0 indexing for x and y

	// if(y == 0 && dir == 3){
	// 	return false;
	// } else if(x == 0 && dir == 2){
	// 	return false;
	// } else if(x == width_ - 1 && dir == 0){
	// 	return false;
	// } else if(y == height_ - 1 && dir == 1){
	// 	return false;
	// }

	int point_1 = y*width_ + x;

	if(dir == 0){
		if(walls[point_1].first == 0){
			return true;
		}
	} else if(dir == 1){
		if(walls[point_1].second == 0){
			return true;
		}
	} else if(dir == 2){
		// leftward step

		if(x == 0){
			return false;
		}

		if(walls[point_1 - 1].first == 0){
			return true;
		}

	} else if(dir == 3){
		// upward step

		if(y == 0){
			return false;
		}

		if(walls[point_1 - width_].second == 0){
			return true;
		}

	}

	return false;

}

void SquareMaze::setWall(int x, int y, int dir, bool exists){

	// assuming 0 indexing for x and y
	// assuming no bad parameter values
	// assuming children of node being pulled off also get pulled off of original set

	// if(exists == false){

	// 	// union
	// 	if(dir == 0){
	// 		dset.setunion(y*width_ + x, y*width_ + x + 1);
	// 	} else {
	// 		dset.setunion(y*width_ + x, y*width_ + x + width_);
	// 	}

	// } else {

	// 	// break the set
	// 	if(dir == 0){
	// 		// cannot traverse through entire arr to set children nodes to point to original set
	// 		// cannot traverse through entire arr to count number of children nodes either
	// 		dset.arr[y*width_ + x + 1] = -1;
	// 	} else {
	// 		dset.arr[y*width_ + x + width_] = -1;
	// 	}

	// }

	// JUST WALLS VECTOR

	int point_1 = y*width_ + x;

	if(dir == 0){
		if(exists){
			walls[point_1].first = 1;
		} else {
			walls[point_1].first = 0;
		}
	} else {
		if(exists){
			walls[point_1].second = 1;
		} else {
			walls[point_1].second = 0;
		}
	}

}
/*
vector< int > squaremaze::solvemaze ( )
solves this squaremaze. for each square on the bottom row (maximum y coordinate),
there is a distance from the origin (i.e. the top-left cell), which is defined as
the length (measured as a number of steps) of the only path through the maze from
the origin to that square. select the square in the bottom row with the largest
distance from the origin as the destination of the maze. solvemaze() returns the
winning path from the origin to the destination as a vector of integers,
where each integer represents the direction of a step, using the same encoding
 as in cantravel(). if multiple paths of maximum length exist, use the one with
 the destination cell that has the smallest x value. hint: this function should
 run in time linear in the number of cells in the maze. returns a vector of
  directions taken to solve the maze
*/

/*this function is helper for solve maze. It recursively builds a an uptree
as a hash mazemap with point 0 being the root and the value of every node storing the
next point in the uptree and the length until the root.
*/
void SquareMaze::solve(int point, int prev_point, int len){//pass point and length
	//if p already exists in mazemap we visitied it already
	if(mazemap.find(point)!=mazemap.end()) return;

	//otherwise we haven't visited it so add it to mazemap and visit it's neighbors
	mazemap[point]=make_pair(prev_point,len);

	unsigned x=point%width_, y=point/width_;
	if (canTravel(x,y,0)){//check wall on right
		solve(point+1,point,len+1);//if no wall then visit that point
	}
	if (canTravel(x,y,1)){//check bottom
		solve(point+width_,point,len+1);
	}
	if (canTravel(x,y,2)){//check left
		solve(point-1,point,len+1);
	}
	if (canTravel(x,y,3)){//check up
		solve(point-width_,point,len+1);
	}
}

vector<int> SquareMaze::solveMaze(){
	vector<int> ans;
	if (!mazemap.empty()) mazemap.clear();

	//build mazemap of maze (have the root hold -size for previous_point)
	solve(0,-width_*height_,0);

	// //debug to check maze map:
	// for(int i=0;i<4;i++){
	// 	cout<<"MAZEMAP "<<i<<" "<<mazemap[i].first<<endl;
	// }

	//find which box in the bottom row has the longest path
	int end=width_*(height_-1);
	for (int i =width_*(height_-1);i<width_*height_;i++){
		if (mazemap[i].second>mazemap[end].second){
			//not >= bc need to default to smallest x in case of a tie
			end=i;
		}
	}

	//now know which point is end... solve the maze
	stack<int> s;
	for(int at =end; at!=-width_*height_; at=mazemap[at].first){
		//start at end and go backwards up the uptree until you get too root
		s.push(at);//add points to a stack
//		cout<<"pusing "<<at<<endl;
	}
	//now go through stack and encode the path as directions
	int first=s.top(),next;
	s.pop();//store first and pop. i think we can assume solution path is not just one point
	while(!s.empty()){
		next=s.top();//sore and pop next
		s.pop();
		int diff = next-first;//find the difference between the points to determine dir of movement
		if (diff==1) ans.push_back(0);
		if (diff==width_) ans.push_back(1);
		if (diff==-1) ans.push_back(2);
		if (diff==-width_)ans.push_back(3);
		//default: cout<<"THIS SHOULD NEVER BE THE CASE!!!\n";

		first = next;//reset the new first
	}
	return ans;
}

/*
PNG * SquareMaze::drawMaze	(		)	const
Draws the maze without the solution.

First, create a new PNG. Set the dimensions of the PNG to (width*10+1,height*10+1). where height and width were the arguments to makeMaze.
Blacken the entire topmost row and leftmost column of pixels,
except the entrance (1,0) through (9,0).
 For each square in the maze, call its maze coordinates (x,y).
 If the right wall exists, then blacken the pixels with coordinates
  ((x+1)*10,y*10+k) for k from 0 to 10.
	If the bottom wall exists, then blacken the pixels with coordinates
	(x*10+k, (y+1)*10) for k from 0 to 10.

The resulting PNG will look like the sample image, except there will be no exit from the maze and the red line will be missing.

Returns
a PNG of the unsolved SquareMaze
*/
PNG* SquareMaze::drawMaze() const{
	PNG* a = new PNG(width_*10+1,height_*10+1);
	HSLAPixel black(0,0,0);//h=0,s=1,l=0

	a->getPixel(0,0)=black;//blacken first pixel
	for(unsigned i =10;i<a->width();i++)//blacken top row except for entrance
		a->getPixel(i,0)=black;
	for(unsigned i=0;i<a->height();i++)
		a->getPixel(0,i)=black;

	for(unsigned p=0;p<walls.size();p++){ //go through all walls
		unsigned x=p%width_, y=p/width_;
		if(walls[p].first==1){//right wall exists so draw it
			for (unsigned k=0;k<=10;k++){
				a->getPixel((x+1)*10,y*10+k)=black;
			}
		}
		if(walls[p].second==1){//btm wall exists so draw it
			for (unsigned k=0;k<=10;k++){
				a->getPixel(x*10+k,(y+1)*10)=black;
			}
		}

	}
	return a;
}

/*
This function calls drawMaze, then solveMaze; it modifies the PNG from
drawMaze to show the solution vector and the exit.
Start at pixel (5,5). Each direction in the solution vector corresponds
to a trail of 11 red pixels in the given direction. If the first step is
downward, color pixels (5,5) through (5,15) red. (Red is 0,1,0.5,1 in HSLA).
Then if the second step is right, color pixels (5,15) through (15,15) red.
Then if the third step is up, color pixels (15,15) through (15,5) red.
Continue in this manner until you get to the end of the solution vector,
so that your output looks analogous the above picture.
Make the exit by undoing the bottom wall of the destination square:
call the destination maze coordinates (x,y), and whiten the pixels with
coordinates (x*10+k, (y+1)*10) for k from 1 to 9.
Returns
a PNG of the solved SquareMaze
*/
PNG* SquareMaze::drawMazeWithSolution(){
	PNG* a =drawMaze();
	HSLAPixel red(0,1,.5,1);//h=0,s=1,l=.5,a=1
	HSLAPixel white(0,0,1);
	vector<int> path=solveMaze();
	unsigned x=5,y=5;
	for(auto i : path){
		switch(i){
			case 0:
				for(unsigned k=x;k<x+11;k++) a->getPixel(k,y)=red;
				x+=10;
				break;
			case 1:
				for(unsigned k=y;k<y+11;k++) a->getPixel(x,k)=red;
				y+=10;
				break;
			case 2:
				for(unsigned k=x;k>x-11;k--) a->getPixel(k,y)=red;
				x-=10;
				break;
			case 3:
				for(unsigned k=y;k>y-11;k--) a->getPixel(x,k)=red;
				y-=10;
				break;
			default:
				cout<<"SHOULD NEVER GET TO THIS CASE in drawMazeWithSolution\n";
		}
	}

	//whiten the bottom exit
	x=x-5;
	for(int k=1;k<10;k++) a->getPixel(x+k,height_*10)=white;
	return a;
}
