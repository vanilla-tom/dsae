#include<iostream>

using namespace std;

int map[8][8] = {0};
int cnt = 0;

void output(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      cout << map[i][j] << " ";
    }
    cout << endl;
  }
}

bool check(int x, int y){
  for(int i = 0; i < 8; i++){
    if(map[x][i] == 1 || map[i][y] == 1){
      return false;
    }
  }
  int t = 1;
  while(x+t < 8 || x-t >= 0 || y+t < 8 || y-t >= 0){
    if(x+t < 8 && y+t < 8){
      if(map[x+t][y+t] == 1) return false;
    }
    if(x-t >= 0 && y-t >= 0){
      if(map[x-t][y-t] == 1) return false;
    }
    if(x-t >= 0 && y+t < 8){
      if(map[x-t][y+t] == 1) return false;
    }
    if(x+t < 8 && y-t >= 0){
      if(map[x+t][y-t] == 1) return false;
    }
    t++;
  }
  return true;
}

void dfs(int x, int y){
  for(int i = 0; i < 8; i++){
    if(check(i, y)){
      map[i][y] = 1;
      if(y == 7){
        output();
        cnt++;
        // return true;
        cout << endl;
      }
      // if(dfs(i, y+1)) return true;
      dfs(i, y+1);
      map[i][y] = 0;
    }
  }
  // return false;
}

int main(){
  dfs(0, 0);
  cout << cnt << endl;
  return 0;
}