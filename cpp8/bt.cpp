#include <iostream>
#include "bt.h"

// Создать бинарное дерево
BTNode* createBT(int value) {
	BTNode* root = new BTNode;
	root->left = NULL;
    root->right = NULL;
	root->value = value;
	return root;
}

// Минимальный элемент в бинарном дереве 
BTNode* getMinBT(BTNode* root) {
	while (root->left)
		root = root->left;
	return root;
}

// Максимальный элемент в бинарном дереве
BTNode* getMaxBT(BTNode* root) {
	while (root->right)
		root = root->right;
	return root;
}

// Размер бинарного дерева
int sizeBT(BTNode* root, int size_count) {
	if (root) {
		size_count++;
        return sizeBT(root->left) + sizeBT(root->right);
	} else
        return size_count;
}

// Вывод бинарного дерева в указанный ostream
void printBT(BTNode* root, const std::string& rpf, const std::string& mpf, const std::string& lpf, std::ostream& os) {
	if (root != NULL) {
        if (root->right)
            printBT(root->right, rpf + "   ", rpf + ".-->", rpf + "|  ", os);
        std::cout << mpf << root->value << std::endl;
        if (root->left)
            printBT(root->left, lpf + "|  ", lpf + "`-->", lpf + "   ", os);
    }
}

// Поиск в бинарном дереве значения
BTNode* searchBT(int value, BTNode* root) {
    if (root != nullptr)
    {
        if (value == root->value)
            return root;
        if (value < root->value)
            return searchBT(value, root->left);
        else
            return searchBT(value, root->right);
    }
    else return NULL;
}

// Удаление элемента из бинарного дерева
BTNode* deleteBT(int value, BTNode* root) {
    if (root == NULL)
        return NULL;
 
    if (value < root->value)
        root->left = deleteBT(value, root->left);
    else if (value > root->value)
        root->right = deleteBT(value, root->right);
    else {
        if (root->left == NULL && root->right == NULL)
            root = NULL;
        else if (root->left == NULL || root->right == NULL)
            root = root->left ? root->left : root->right;
        else {
            BTNode* minnode = getMinBT(root->right);
            root->value = minnode->value;
            root->right = deleteBT(minnode->value, root->right);
        }
    }

    return root;
}

// Добавить значение в бинарное дерево
void addBT(int value, BTNode*& root) {
    if (root == NULL)
        root = createBT(value);
    else
        insertBT(value, root);
}

// Добавить значение в бинарное дерево (root != null)
void insertBT(int value, BTNode* root) {
    if (!root) return;                            
    if (value < root->value)
    {
        if (root->left != NULL)
            insertBT(value, root->left);
        else {
            root->left = new BTNode;
            root->left->value = value;
            root->left->left = NULL;
            root->left->right = NULL;
        }
    } else if (value >= root->value) {
        if (root->right != NULL)
            insertBT(value, root->right);
        else {
            root->right = new BTNode;
            root->right->value = value;
            root->right->left = NULL;
            root->right->right = NULL;
        }
    }
}

// Уничтожить бинарное дерево
void destroyBT(BTNode* root) {
    if(root!=NULL) {
        destroyBT(root->left);
        destroyBT(root->right);
        delete root;
    }
}

// Straight-walk: Прямой обход бинарного дерева
void strwBT(BTNode* root) {
    if(root){
        std::cout << root->value << ' ';
        strwBT(root->left);
        strwBT(root->right);
    }
}

// Reverse-walk: Обратный обход бинарного дерева
void revwBT(BTNode* root) {
    if(root){
        revwBT(root->left);
        revwBT(root->right);
        std::cout << root->value << ' ';
    }
}

// Symmetrical-walk: Симметричный обход бинарного дерева
void symwBT(BTNode* root) {
    if(root){
        symwBT(root->left);
        std::cout << root->value << ' ';
        symwBT(root->right);
    }
}