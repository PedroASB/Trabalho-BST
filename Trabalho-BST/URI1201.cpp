#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

// Estrutura de um nó
typedef struct node {
	int data;
	struct node *left, *right;
} Node;

// Estrutura de uma árvore
typedef struct tree {
	int size;
	Node *root;
} Tree;

// Cria e aloca um nó
Node * createNode(int value);

// Cria e aloca uma árvore binária
Tree * createTree(void);

// Insere um novo nó em uma árvore
void insertNode(Tree * tree, Node * newNode);

// Remove um nó de uma árvore
Node * removeNode(Tree * tree, Node * root, int value);

// Verifica a existência de um elemento na árvore
int checkNode(Tree * tree, int key);

// Retorna o nó que contém o maior elemento
Node * maxNode(Node * root);

// Libera a memória de todos os nós
void freeAllNodes(Node * root);

// Libera a memória alocada pela estrutura da árvore
Tree * freeTree(Tree * tree);

// Imprime os elementos na notação infixa
void inOrder(Tree * tree, Node * root);

// Imprime os elementos na notação prefixa
void preOrder(Tree * tree, Node * root);

// Imprime os elementos na notação posfixa
void postOrder(Tree * tree, Node * root);

char verifyCommand(char command[20]);
int getIntValue(char * str);

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	Tree * tree = createTree();
	char command[20];
	int commandInt, value;

	while (scanf("%[^\n]%*c", command) != EOF){
		commandInt = verifyCommand(command);
		if (commandInt > 2)	value = getIntValue(command);
		
		switch (commandInt){
			case 0:
				preOrder(tree, tree->root);
				cout << endl;
				break;
			case 1:
				inOrder(tree, tree->root);
				cout << endl;
				break;
			case 2:
				postOrder(tree, tree->root);
				cout << endl;
				break;
			case 3:
				insertNode(tree, createNode(value));
				break;
			case 4:
				cout << value;
				if (!checkNode(tree, value)) cout << " nao";
				cout << " existe" << endl;
				break;
			case 5:
				tree->root = removeNode(tree, tree->root, value);	
				break;
		}
	}

	tree = freeTree(tree);
	return 0;
}

char verifyCommand(char command[20]){
	if (!strcmp(command, "PREFIXA")) return 0;
	if (!strcmp(command, "INFIXA")) return 1;
	if (!strcmp(command, "POSFIXA")) return 2;
	if (command[0] == 'I') return 3;
	if (command[0] == 'P') return 4;
	if (command[0] == 'R') return 5;
	return -1;
}

int getIntValue(char * str){
	if (str == NULL) return 0;

	int len = strlen(str);

	if (len <= 2) return 0;

	string tmp = string(str + 2, str + len);
	int value = stoi(tmp); 

	return value;
}

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
