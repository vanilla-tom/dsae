#include "Astar.cpp"

void output(node *n){
  if(n->parent != nullptr){
    output(n->parent);
  }
  cout << "->(" << n->x << "," << n->y << ")" << endl;
}

int main(){
  vector<vector<int> > map(mapHeight, vector<int>(mapWidth, 1));
  initMap(map);  //随机生成
  //打印
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
  return 0;
}