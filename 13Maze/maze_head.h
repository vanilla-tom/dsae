#include<cmath>
#include<vector>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<time.h>

using namespace std;

typedef struct node{
  int x, y;
  int f, g, h;
  node *parent;
}node;

node *astar(vector<vector<int> > &, int, int, int, int);
void randomMap(vector<vector<int> > &, int, int);
void readMap(vector<vector<int> > &, string);