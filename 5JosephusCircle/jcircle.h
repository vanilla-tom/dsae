#include<iostream>

using namespace std;

typedef struct node{
  int num;
  int code;
  node *next;
}node;

node *createNode(int code);
node *addNode(node *head, int num, int code);
int deleteNextNode(node *head);
node *generateCircle(int n, int code[]);
int *outOrder(int n, int m, int code[]);