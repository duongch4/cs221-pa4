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
    queue< pair<int,int> > q;
    q.push(start);

    while ( !q.empty() ) {
        pair<int,int> curr = q.front();
        q.pop();
        vector< pair<int,int> > adjList = neighbors(curr);

        for (unsigned i = 0; i < adjList.size(); i++) {
            if ( good(V, curr, adjList[i]) ) {
                
                V[ adjList[i].second ][ adjList[i].first ] = true; // set visited to vertex
                P[ adjList[i].second ][ adjList[i].first ] = curr; // remember the parent/predecessor

                q.push(adjList[i]); // add neighbour to queue
            }
        }
    }

	pathPts = assemble(P,start,end); //provided, do not erase!
}

vector<pair<int,int>> path::assemble(vector<vector<pair<int,int>>> & p, pair<int,int> s, pair<int,int> e) {

    /* hint, gold code contains the following line:
	stack<pair<int,int>> S; */

    /* your code here */
    vector< pair<int,int> > result;
    stack< pair<int,int> > S;

    // add start point to result
    result.push_back(s);

    // do something to S
    while (e != s) {
        // add e to S
        S.push(e);
        // update e:
        // if e == predecessor of e <=> no path back to s => set e = s to exit loop
        // else: backtrack to s => update e to be its predecessor 
        e = (e == p[e.second][e.first])?
            s : p[e.second][e.first];
    }

    // No path => return only the start
    if (S.size() < 2) {
        return result;
    }

    // Reverse the order of S if path exists
    while ( !S.empty() ) {
        result.push_back(S.top());
        S.pop();
    }
    return result; 
}

/*===============================================================================*/

PNG path::render(){

    /* your code here */
    PNG imgWithPath(image);
    for (int i = 0; i < length(); i++) {
        *imgWithPath.getPixel(pathPts[i].first, pathPts[i].second) = RGBAPixel(255, 0, 0);
    }
    return imgWithPath;
}

/*===============================================================================*/

bool path::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){

    /* your code here */
    return withinImg(next) 
           && unvisited(v, next)
           && closeEnough(curr, next);
}

bool path::withinImg(pair<int,int> & point) {
    return 0 <= point.first  && point.first  < (int)image.width() 
        && 0 <= point.second && point.second < (int)image.height(); 
}

bool path::unvisited(vector< vector<bool> > & v, pair<int,int> & point) {
    return !v[point.second][point.first];
}

bool path::closeEnough(pair<int,int> & curr, pair<int,int> & next) {
    RGBAPixel* pixelCurr = image.getPixel(curr.first, curr.second);
    RGBAPixel* pixelNext = image.getPixel(next.first, next.second);
    return closeEnough(*pixelCurr, *pixelNext);
}

/**
 * This is given */
bool path::closeEnough(RGBAPixel p1, RGBAPixel p2){
   int dist =   (p1.r-p2.r)*(p1.r-p2.r) 
              + (p1.g-p2.g)*(p1.g-p2.g) 
              + (p1.b-p2.b)*(p1.b-p2.b);

   return (dist <= 80);
}

/*===============================================================================*/

vector<pair<int,int>> path::neighbors(pair<int,int> curr) {
	vector<pair<int,int>> n;

    /* your code here */
    vector< pair<int, int> > neighbors(4);
    
    pair<int,int> left(curr.first - 1, curr.second);
    pair<int,int> down(curr.first, curr.second + 1);
    pair<int,int> right(curr.first + 1, curr.second);
    pair<int,int> up(curr.first, curr.second - 1);

    neighbors[0] = left;
    neighbors[1] = down;
    neighbors[2] = right;
    neighbors[3] = up;

    return neighbors;
}

/*============== These are given ================================================*/

vector<pair<int,int>> path::getPath() { return pathPts; }

int path::length() { return pathPts.size(); }
