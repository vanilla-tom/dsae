#include "link_bst_avl.h"

int main(){
  //测试链表结构二叉排序树的代码
  int a[5] = {5,6,3,4,8};
  node *root = generateBST(a, 5);
  int *b = LNRTree(root, 5);
  for(int i = 0; i < getNodeNums(root); i++){
    cout << b[i] << " ";
  }
  cout << endl;
  node *p =  getNodeByData(root, 3);
  if(deleteNodeByPos(p)){
    int *c = LNRTree(root, 4);
    for(int i = 0; i < getNodeNums(root); i++){
      cout << c[i] << " ";
    }
  }
  cout << endl;
  cout << getASL(root);
  return 0;
}