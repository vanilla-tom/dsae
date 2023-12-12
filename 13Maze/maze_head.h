#pragma once

#include<cmath>
#include<vector>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<time.h>


typedef struct node {
	int x, y;
	int f, g, h;
	node* parent;
}node;

node* astar(std::vector<std::vector<int> >&, int, int, int, int);
void randomMap(std::vector<std::vector<int> >&, int, int);
void readMap(std::vector<std::vector<int> >&, std::string);