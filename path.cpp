#include "path.h"
#include <queue>
#include <stack>
#include <iostream>
#include <string>
using namespace std;

path::path(const PNG & im, pair<int,int> s, pair<int,int> e)
   :start(s),end(e),image(im){
    BFS();
}

void path::BFS(){
	// initialize working vectors
	vector<vector<bool>> V(image.height(), vector<bool> (image.width(),false));
	vector<vector<pair<int,int>>> P(image.height(), vector<pair<int,int>> (image.width(),end));

    /* your code here */
    vector<pair<int,int>> v = neighbors( pair<int,int>(3,4) );

	pathPts = assemble(P,start,end);
}

PNG path::render(){

    /* your code here */
    PNG imgWithPath(image);
    for (int i = 0; i < length(); i++) {
        *imgWithPath.getPixel(pathPts[i].first, pathPts[i].second) = RGBAPixel(255, 0, 0);
    }
    return imgWithPath;
}

vector<pair<int,int>> path::getPath() { return pathPts;}

int path::length() { return pathPts.size();}

bool path::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

    /* your code here */
    if ( withinImg(next) ) {
        return ( unvisited(v, next) && closeEnough(curr, next) );
    } else {
        return false;
    }
}

bool path::withinImg(pair<int,int> & next) {
    return 0 <= next.first  && next.first  < (int)image.width() 
        && 0 <= next.second && next.second < (int)image.height(); 
}

bool path::unvisited(vector< vector<bool> > & v, pair<int,int> & next) {
    return !v[next.second][next.first];
}

bool path::closeEnough(pair<int,int> & curr, pair<int,int> & next) {
    RGBAPixel* pixelCurr = image.getPixel(curr.first, curr.second);
    RGBAPixel* pixelNext = image.getPixel(next.first, next.second);
    return closeEnough(*pixelCurr, *pixelNext);
}

vector<pair<int,int>> path::neighbors(pair<int,int> curr) {
	vector<pair<int,int>> n;

    /* your code here */
    vector< pair<int, int> > neighbors(4);
    
    pair<int,int> left(curr.first - 1, curr.second);
    pair<int,int> down(curr.first, curr.second + 1);
    pair<int,int> right(curr.first + 1, curr.second);
    pair<int,int> up(curr.first, curr.second - 1);

    neighbors.push_back(left);
    neighbors.push_back(down);
    neighbors.push_back(right);
    neighbors.push_back(up);

    // cout << "current Point: " << curr.first << ", " << curr.second << "\n\n";
    // cout << "Neighbors:\n"; 
    // for (unsigned i = 0; i < neighbors.size(); i++) {
    //     cout << neighbors[i].first << ", " << neighbors[i].second << "\n";
    // }

    return neighbors;
}

vector<pair<int,int>> path::assemble(vector<vector<pair<int,int>>> & p, pair<int,int> s, pair<int,int> e) {

    /* hint, gold code contains the following line:
	stack<pair<int,int>> S; */

    /* your code here */
    vector< pair<int,int> > vec;
    vec.push_back(s);
    return vec;
}

bool path::closeEnough(RGBAPixel p1, RGBAPixel p2){
   int dist =   (p1.r-p2.r)*(p1.r-p2.r) 
              + (p1.g-p2.g)*(p1.g-p2.g) 
              + (p1.b-p2.b)*(p1.b-p2.b);

   return (dist <= 80);
}
