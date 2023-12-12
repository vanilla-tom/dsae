#include "maze_head.h"

node* create_node(int x, int y, int g, int h, node* parent) {
    node* n = new node;
    n->x = x;
    n->y = y;
    n->g = g;
    n->h = h;
    n->f = g + h;
    n->parent = parent;
    return n;
}

int calc_h(int x, int y, int dest_x, int dext_y) {
    return abs(x - dest_x) + abs(y - dext_y);
}

node* move(node* n, std::vector<std::vector<int> >& map, int dir, int dest_x, int dest_y) {
    int moveArr[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    int nx = n->x + moveArr[dir][0];
    int ny = n->y + moveArr[dir][1];
    if (nx < 0 || nx >= map[0].size() || ny < 0 || ny >= map.size() || map[ny][nx] != 0) {
        return nullptr;
    }
    return create_node(nx, ny, n->g + 1, calc_h(nx, ny, dest_x, dest_y), n);
}

int getmin(std::vector<node*>& list) {  //返回表中最小元素索引
    int min = list[0]->f;
    int pos = 0;
    for (int i = 0; i < list.size(); i++) {
        if (list[i]->f < min) {
            min = list[i]->f;
            pos = i;
        }
    }
    return pos;
}

int findPos(std::vector<node*>& list, node* n) {
    std::vector<node*>::iterator it;
    for (it = list.begin(); it != list.end(); it++) {
        if ((*it)->x == n->x && (*it)->y == n->y) {
            return it - list.begin();
        }
    }
    return -1;
}

node* astar(std::vector<std::vector<int> >& map, int start_x, int start_y, int dest_x, int dest_y) {
    std::vector<node*> openlist(0);
    std::vector<node*> closelist(0);
    openlist.reserve(100);
    closelist.reserve(100);

    node* start = create_node(start_x, start_y, 0, 0, nullptr);
    openlist.push_back(start);  //将初始位置加入开表

    while (!openlist.empty()) {
        int min_pos = getmin(openlist);     //获取f值最小的节点
        node* current = openlist[min_pos];
        if (current->x == dest_x && current->y == dest_y) {
            return current;   //到达目标直接返回当前节点
        }
        openlist.erase(openlist.begin() + min_pos);
        closelist.push_back(current);
        for (int dir = 0; dir < 4; dir++) {
            node* next = move(current, map, dir, dest_x, dest_y);
            if (next != nullptr && !(next->x == current->x && next->y == current->y)) {
                if (findPos(closelist, next) != -1) continue;
                int open_pos = findPos(openlist, next);
                if (open_pos == -1) {
                    openlist.push_back(next);
                }
                else if (open_pos != -1 && next->f < openlist[open_pos]->f) {
                    openlist[open_pos] = next;
                }
            }
        }
    }
    return nullptr;
}