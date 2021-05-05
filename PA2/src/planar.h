
#ifndef _PLANAR_H
#define _PLANAR_H

#include <vector>
#include <map>

using namespace std;

class Planar
{
public:
    Planar(int, map<int, int>); // constructor
    map<int, int> MPS(int, int); // finds the maximum planar subset

private:
    map<int, int> chords;                 // chords[end] -> start
    int vertices;                         // number of vertices on the circle
    vector<vector<map<int, int> > > memo; // memo, stores the chords data for each vertice
};

#endif
