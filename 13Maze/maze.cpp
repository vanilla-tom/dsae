#include<cmath>
#include<vector>
#include<iostream>
#include<time.h>

#define mapWidth 13
#define mapHeight 13

using namespace std;

void create_path(vector<vector<int> > &map, int x, int y){
   map[y][x] = 0;
   int head[4][2] = { {-2,0},{0,2},{2,0},{0,-2} };
   int order[4] = { 0 };
   int n = 0;
   bool flag = true;
   while (flag) {
     flag = false;
     order[n % 4] = rand() % 4;
    for (int i = 0; i < 4; i++) {
      for (int j = i + 1; j < 4; j++) {
        if (order[i] == order[j]) {
          flag = true;
        }
      }
    }
    n++;
  }
  int nx = 0, ny = 0, dx = 0, dy = 0;
  for (int i = 0; i < 4; i++) {
    dx = head[order[i]][1];
    dy = head[order[i]][0];
    if (x + dx < 0 || x + dx >= mapWidth || y + dy < 0 || y + dy >= mapHeight) {
      continue;
    } else {
      if (map[y + dy][x + dx] == 2) {
        nx = x + dx / 2;
        ny = y + dy / 2;
        map[ny][nx] = 0;
        nx = nx + dx / 2;
        ny = ny + dy / 2;
        map[ny][nx] = 0;
        create_path(map, nx, ny);
      }
    }
  }
}

void initMap(vector<vector<int> > &map){
  time_t t;
  srand(time(&t));
  for(int i = 1; i < mapHeight; i += 2){
    for(int j = 1; j < mapWidth; j += 2){
      map[i][j] = 2;
    }
  }
  create_path(map, 1, 1);
}