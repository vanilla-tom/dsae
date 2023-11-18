#include "linked_bst_avl.h"

int main(){
  //测试链表结构二叉排序树的代码
  int a[6] = {5,6,3,4,8,9};
  BST bst = BST(a[0]);
  bst.generateBST(a, 6);
  int *b = bst.LNRTree();
  for(int i = 0; i < bst.nodeNums; i++){
    cout << b[i] << " ";
  }
  cout << endl;
  if(bst.deleteNode(4)){
    int *c = bst.LNRTree();
    for(int i = 0; i < bst.nodeNums; i++){
      cout << c[i] << " ";
    }
  }
  cout << endl;
  cout << bst.getASL();
  return 0;
}