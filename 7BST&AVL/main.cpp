#include "link_bst_avl.h"

int main(){
  //测试链表结构二叉排序树的代码
  int a[5] = {5,6,3,4,8};
  BST bst = BST(5);
  bst.generateBST(a, 5);
  int *b = bst.LNRTree(5);
  for(int i = 0; i < bst.nodeNums; i++){
    cout << b[i] << " ";
  }
  cout << endl;
  if(bst.deleteNodeByPos(bst.getNodeByData(bst.root, 3))){
    int *c = bst.LNRTree(4);
    for(int i = 0; i < bst.nodeNums; i++){
      cout << c[i] << " ";
    }
  }
  cout << endl;
  cout << bst.getASL();
  return 0;
}