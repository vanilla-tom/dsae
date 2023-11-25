#include<iostream>
#include<vector>
#include<string>

#define FARMER 1
#define WOLF 2
#define SHEEP 4
#define CABBAGE 8

using namespace std;

int solution_cnt = 0;

bool is_crossed(int status, int who){
  if((status & who) == who) return true;
  else return false;
}

void get_status(int status, bool &farmer, bool &wolf, bool &sheep, bool &cabbage){
  farmer = is_crossed(status, FARMER);
  wolf = is_crossed(status, WOLF);
  sheep = is_crossed(status, SHEEP);
  cabbage = is_crossed(status, CABBAGE);
}

bool is_safe(int status){
  bool farmer, wolf, sheep, cabbage;
  get_status(status, farmer, wolf, sheep, cabbage);
  if((farmer^wolf) && (farmer^sheep) || (farmer^cabbage) && (farmer^sheep)){
    return false;
  }else{
    return true;
  }
}

void get_move_list(int status, vector<int> &move_list){
  move_list.clear();
  for(int i = 1; i <= 8; i = i<<1){
    if((status&i)/i == (status&FARMER)){
      int new_status = status ^ (i | FARMER);
      if(is_safe(new_status)){
        move_list.push_back(new_status);
      }
    }
  }
}

void print(int status){
  string m[4] = {"farmer", "wolf", "sheep", "cabbage"};
  for(int i = 0; i < 4; i++){
    if((status/(1<<i))%2 == 1){
      cout << m[i] << " ";
    }
  }
  cout << endl << "---------------------------" << endl << "river";
  cout << endl << "---------------------------" << endl;
  for(int i = 0; i < 4; i++){
    if((status/(1<<i))%2 == 0){
      cout << m[i] << " ";
    }
  }
  cout << endl;
}

void output(vector<int> &path){
  cout << "solution " << solution_cnt << " :" << endl;
  for(int i = 0; i < path.size(); i++){
    print(path[i]);
    if(i != path.size()-1)
      cout << endl << "V" << endl << endl;
  }
  cout << endl;
}

void dfs(int status, vector<int> &path){
  if(status == 15){
    solution_cnt++;
    output(path);
    return;
  }
  vector<int> move_list;
  get_move_list(status, move_list);
  for(int i = 0; i < move_list.size(); i++){
    bool isin = false;
    for(auto j : path){
      if(move_list[i] == j){
        isin = true;
        break;
      }
    }
    if(isin) continue;
    path.push_back(move_list[i]);
    dfs(move_list[i], path);
    path.pop_back();
  }
}

int main(){
  int status = 0;  //全部在南岸
  vector<int> path(1, 0);
  path.reserve(16);
  dfs(status, path);
  return 0;
}