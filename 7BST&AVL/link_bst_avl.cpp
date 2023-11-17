#include "link_bst_avl.h"

node *addChild(int data, node *parent, bool addleft){
  if(parent == NULL){
    node *root = new node;
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
    return root;
  }else{
    node *child = new node;
    child->data = data;
    child->left = NULL;
    child->right = NULL;
    child->parent = parent;
    if(addleft){
      parent->left = child;
    }else{
      parent->right = child;
    }
    return child;
  }
}

node *generateBST(int list[], int n){
  node *root = addChild(list[0]);
  node *p = root;
  for(int i = 1; i < n; i++){
    p = root;
    while (true){
      if(list[i] < p->data){
        if(p->left != NULL) p = p->left;
        else {
          p->left = addChild(list[i], p, true);
          break;
        }
      }else if(list[i] > p->data){
        if(p->right != NULL) p = p->right;
        else {
          p->right = addChild(list[i], p, false);
          break;
        }
      }
    }
  }
  return root;
}

void lnrdfs(node *root, nodeArr *arr){
  if(root == NULL) return;
  lnrdfs(root->left, arr);
  arr->arr[arr->pos++] = root;
  lnrdfs(root->right, arr);
}

int *LNRTree(node *root, int n){
  nodeArr *orderArr= new nodeArr;
  orderArr->maxsize = n;
  orderArr->arr = new node*[n];
  lnrdfs(root, orderArr);
  int *outarr = new int[n];
  for(int i = 0; i < n; i++){
    outarr[i] = orderArr->arr[i]->data;
  }
  return outarr;
}

int getNodeNums(node *root){
  if(root == NULL) return 0;
  return getNodeNums(root->left) + getNodeNums(root->right) + 1;
}

int getSL(node *root, int k){
  int d = k;  //记录当前查找长度
  if(root->left != NULL){
    d += getSL(root->left, k + 1);  //把所有左子树的查找长度加进d
  }
  if(root->right != NULL){
    d += getSL(root->right, k + 1);
  }
  return d;
}

float getASL(node *root){
  return getSL(root) * 1.0 / getNodeNums(root);
}

node *getNodeByData(node *root,  int x){
  if(root == NULL) return 0;
  if(root->data > x) return getNodeByData(root->left, x);
  else{
    if(root->data == x) return root;
    else return getNodeByData(root->right, x);
  }
}

bool deleteNodeByPos(node *pos){
  if(pos == NULL) return false;
  node *p = pos->left;
  node *q = pos->right;
  if(p == NULL && q == NULL){
    delete pos;
    pos = NULL;
  }
  else if(p == NULL){
    pos->data = q->data;
    pos->right = q->right;
    pos->left = q->left;
    delete q;
    q = NULL;
  }
  else if(q == NULL){
    pos->data = p->data;
    pos->right = p->right;
    pos->left = p->left;
    delete p;
    p = NULL;
  }else{
    node *r = q;
    while(r->left != NULL){
      r = r->left;
    }
    pos->data = r->data;
    pos->right = r->right;
    pos->left = r->left;
    delete r;
    r = NULL;
  }
  return true;
}