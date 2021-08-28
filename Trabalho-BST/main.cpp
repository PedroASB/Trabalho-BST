#include <iostream>
#include <string.h>
#include "BST.h"

using namespace std;

int getIntValue(char * str);

char verifyCommand(char command[20]);

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