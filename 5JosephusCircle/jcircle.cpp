#include "jcircle.h"

node *createNode(int code){
  node *head = new node;
  head->next = head;
  head->num = 1;
  head->code = code;
  return head;
}

node *addNode(node *head, int num, int code){
  node *p = new node;
  p->num = num;
  p->code = code;
  p->next = head->next;
  head->next = p;
  return p;
}

int deleteNextNode(node *head){
  if(head->next == head){
    return 0;
  }else{
    node *tmp = head->next;
    head->next = tmp->next;
    delete tmp;
    tmp = NULL;
    return 1;
  }
}

node *generateCircle(int n, int code[]){
  node *head = createNode(code[0]);
  for(int i = 1; i < n; i++){
    head = addNode(head, i+1, code[i]);
  }
  return head;
}

int *outOrder(int n, int m, int code[]){
  node *head = generateCircle(n, code);
  int *order = new int[m]();  //初始化顺序数组
  int count = 0;
  do
  {
    for(int i = 1; i < m; i++){
      head = head->next;
    }
    m = head->next->code;
    order[count++] = head->next->num;
  } while (deleteNextNode(head));
  return order;
}