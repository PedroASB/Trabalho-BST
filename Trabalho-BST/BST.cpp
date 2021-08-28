#include "BST.h"

Node * createNode(int value){
	Node * node = (Node *) malloc(sizeof(Node));
	
	node->left = node->right = NULL;

	node->data = value;
	return node;
}

Tree * createTree(void){
	Tree * tree = (Tree *) malloc(sizeof(Tree));
	tree->size = 0;
	tree->root = NULL;

	return tree;
}

int checkNode(Tree * tree, int key){
	Node * tmp = tree->root;

	while (tmp != NULL){
		if (tmp->data == key) 
			return 1;
		if (key > tmp->data) 
			tmp = tmp->right;
		else 
			tmp = tmp->left;
	}

	return 0;
}

void insertNode(Tree * tree, Node * newNode){

	if (tree->root == NULL){
		tree->root = newNode;
		tree->size++;
		return;
	}

	Node * preNode = tree->root;
	while (preNode != NULL){
		if ( newNode->data > preNode->data ){
			if (preNode->right == NULL){
				preNode->right = newNode;
				tree->size++;
			}
			preNode = preNode->right;
		}
		else if (newNode->data < preNode->data){
			if (preNode->left == NULL){
				preNode->left = newNode;
				tree->size++;
			}
			preNode = preNode->left;
		}
		else return;
	}
}

Node * maxNode(Node * root){
	return (!root->right) ? root : maxNode(root->right);
}

Node * removeNode(Tree * tree, Node * root, int value){
	if (tree == NULL || root == NULL) return NULL;

	if (root->data == value){
		Node * temp = NULL;
		tree->size--;
		if (root->right == NULL || root->left == NULL){
				if (!root->right)
					temp = root->left;
				else
					temp = root->right;
				free(root);
				return temp;
		}
		temp = maxNode(root->left);
		root->data = temp->data;
		temp->data = value;
		root->left = removeNode(createTree(), root->left, value);
	}
	else if ( value < root->data ){
		root->left = removeNode(tree, root->left, value);
	} 
	else {
		root->right = removeNode(tree, root->right, value);
	}

	return root;
}

Node * freeNode(Node * node){
	node->left = node->right = NULL;
	node->data = 0;
	free(node);	
	return NULL;
}

void freeAllNodes(Node * root){
	Node * tmp = root;
	if (tmp != NULL){
		freeAllNodes(tmp->left);
		freeAllNodes(tmp->right);
		tmp = freeNode(tmp);
	}
}

Tree * freeTree(Tree * tree){
	if (tree == NULL) return NULL;

	if (tree->root != NULL){
		freeAllNodes(tree->root);
	}

	tree->root = NULL;
	tree->size = 0;
	free(tree);

	return NULL;
}

int counter = 0;

void preOrder(Tree * tree, Node * root){
	Node * tmp = root;
	if (tmp != NULL){
		cout << tmp->data;
		if (counter < tree->size - 1){
			cout << " ";
			counter++;
		}
		else counter = 0;
		preOrder(tree, tmp->left);
		preOrder(tree, tmp->right);
	}
}

void inOrder(Tree * tree, Node * root){
	Node * tmp = root;
	if (tmp != NULL){
		inOrder(tree, tmp->left);
		cout << tmp->data;
		if (counter < tree->size - 1){
			cout << " ";
			counter++;
		}
		else counter = 0;
		inOrder(tree, tmp->right);
	}
}

void postOrder(Tree * tree, Node * root){
	Node * tmp = root;
	if (tmp != NULL){
		postOrder(tree, tmp->left);
		postOrder(tree, tmp->right);
		cout << tmp->data;
		if (counter < tree->size - 1){
			cout << " ";
			counter++;
		}
		else counter = 0;
	}
}