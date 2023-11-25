#include "maze_head.h"

void output(node *n){
  if(n->parent != nullptr){
    output(n->parent);
  }
  cout << "->(" << n->x << "," << n->y << ")" << endl;
}

int main(){
  vector<vector<int> > map(0, vector<int>(0));
  // randomMap(map, 13, 13);
  readMap(map, "testmap.txt");
  //打印
  int mapHeight = map.size();
  int mapWidth = map[0].size();
  for(int i = 0; i < mapHeight; i++){
    for(int j = 0; j < mapWidth; j++){
      cout << map[i][j] << " ";
    }
    cout << endl;
  }
  node *path = astar(map, 1, 1, mapWidth-2, mapHeight-2);
  if(path == nullptr){
    cout << "No path found!" << endl;
  }else{
    output(path);
  }
}