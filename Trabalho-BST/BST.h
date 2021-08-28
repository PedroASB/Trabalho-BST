#ifndef __BST_H__
#define __BST_H__

// Binary Search Tree

#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct node {
	int data;
	struct node *left, *right;
} Node;

typedef struct tree {
	int size;
	Node *root;
} Tree;

Node * createNode(int value);

Tree * createTree(void);

void insertNode(Tree * tree, Node * newNode);

Node * removeNode(Tree * tree, Node * root, int value);

int checkNode(Tree * tree, int key);

Node * maxNode(Node * root);

void freeAllNodes(Node * root);

Tree * freeTree(Tree * tree);

void preOrder(Tree * tree, Node * root);

void inOrder(Tree * tree, Node * root);

void postOrder(Tree * tree, Node * root);

#endif // __BST_H__