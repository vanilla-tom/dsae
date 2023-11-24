#include "maze.cpp"

using namespace std;

typedef struct node{
  int x, y;
  int f, g, h;
  node *parent;
}node;


node *create_node(int x, int y, int g, int h, node *parent){
  node *n = new node;
  n->x = x;
  n->y = y;
  n->g = g;
  n->h = h;
  n->f = g + h;
  n->parent = parent;
  return n;
}

int calc_h(int x, int y, int dest_x, int dext_y){
  return abs(x - dest_x) + abs(y - dext_y);
}

node *move(node *n, vector<vector<int> > &map, int dir, int dest_x, int dest_y){
	int moveArr[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  int nx = n->x + moveArr[dir][0];
  int ny = n->y + moveArr[dir][1];
  if(nx < 0 || nx >= mapWidth || ny < 0 || ny >= mapHeight || map[ny][nx] != 0){
    return nullptr;
  }
  return create_node(nx, ny, n->g + 1, calc_h(nx, ny, dest_x, dest_y), n);
}

int getmin(vector<node*> &list){  //返回表中最小元素索引
  int min = list[0]->f;
  int pos = 0;
  for(int i = 0; i < list.size(); i++){
    if(list[i]->f < min){
      min = list[i]->f;
      pos = i;
    }
  }
  return pos;
}

node *astar(vector<vector<int> > &map, int start_x, int start_y, int dest_x, int dest_y){
  vector<node*> openlist(0);
  vector<node*> closelist(0);


	node *start = create_node(start_x, start_y, 0, 0, nullptr);
  openlist.push_back(start);  //将初始位置加入开表

  while(!openlist.empty()){
    int min_pos = getmin(openlist);     //获取f值最小的节点
    node *current = openlist[min_pos]; //并把他作为current
    if(current->x == dest_x && current->y == dest_y){
      return current;   //到达目标直接返回当前节点
    }
    openlist.erase(openlist.begin() + min_pos);
    closelist.push_back(current);
    for(int dir = 0; dir < 4; dir++){
      node *next = move(current, map, dir, dest_x, dest_y);
      if(next != nullptr && !(next->x == current->x && next->y == current->y)){
        int next_g = current->g + 1;
        int next_h = next->h;
        int next_f = next_g + next_h;

        bool inOpen = false;
        bool inClose = false;
        vector<node*>::iterator it;
        for(it = openlist.begin(); it != openlist.end(); it++){
          if((*it)->x == next->x && (*it)->y == next->y){
            inOpen = true;
            break;
          }
        }
        for(it = closelist.begin(); it != closelist.end(); it++){
          if((*it)->x == next->x && (*it)->y == next->y){
            inClose = true;
            break;
          }
        }
        if(inClose) continue;
        if(!inOpen){
          openlist.push_back(next);
        }
      }
    }
  }
  return nullptr;
}