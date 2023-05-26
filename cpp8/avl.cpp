#include <iostream>
#include "avl.h"

AVLNode* createAVL(int value) {
	AVLNode* root = new AVLNode;
	root->left = NULL;
    root->right = NULL;
    root->height = 0;
	root->value = value;
	return root;
}

AVLNode* getMinAVL(AVLNode* node) {
	AVLNode* current = node;
	while (current->left)
		current = current->left;
	return current;
}

AVLNode* getMaxAVL(AVLNode* node) {
    AVLNode* current = node;
	while (current->right)
		current = current->right;
	return current;
}

int sizeAVL(AVLNode* root, int size_count) {
	if (root) {
		size_count++;
        return sizeAVL(root->left) + sizeAVL(root->right);
	} else
        return size_count;
}

void printAVL(AVLNode* node, const std::string& rpf, const std::string& mpf, const std::string& lpf) {
	if (node != NULL) {
        if (node->right)
            printAVL(node->right, rpf + "   ", rpf + ".-->", rpf + "|  ");
        std::cout << mpf << node->value << std::endl;
        if (node->left)
            printAVL(node->left, lpf + "|  ", lpf + "`-->", lpf + "   ");
    }
}

AVLNode* searchAVL(int value, AVLNode* root) {
    if (root != nullptr) {
        if (value == root->value)
            return root;
        if (value < root->value)
            return searchAVL(value, root->left);
        else
            return searchAVL(value, root->right);
    } else return NULL;
}

AVLNode* deleteAVL(int value, AVLNode* root) {
	if (root == NULL)
		return root;

	if (value < root->value)
		root->left = deleteAVL(value, root->left);
	else if (value > root->value)
		root->right = deleteAVL(value, root->right);
	else {
        if (root->left == NULL && root->right == NULL) { // Нет потомков
            root = NULL;
        } else if (root->left == NULL || root->right == NULL) { // Один потомок
            root = root->left ? root->left : root->right;
        } else { // Два потомка
			AVLNode* minnode = getMinAVL(root->right);
			root->value = minnode->value;
			root->right = deleteAVL(minnode->value, root->right);
		}
	}

    return root ? balanceAVL(root) : NULL;
}

void addAVL(int value, AVLNode*& root) {
    if (root == NULL)
        root = createAVL(value);
    else
        root = insertAVL(value, root);
}

AVLNode* insertAVL(int value, AVLNode* root) {
	if(!root) {
        root = new AVLNode;
        root->value = value;
        root->height = 1;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
	if(value < root->value)
		root->left = insertAVL(value, root->left);
	else if (value > root->value)
		root->right = insertAVL(value, root->right);
	return balanceAVL(root);
}

void destroyAVL(AVLNode* root) {
    if(root!=NULL) {
        destroyAVL(root->left);
        destroyAVL(root->right);
        delete root;
    }
}

void strwAVL(AVLNode* root) {
    if(root){
        std::cout << root->value << ' ';
        strwAVL(root->left);
        strwAVL(root->right);
    }
}
void revwAVL(AVLNode* root) {
    if(root){
        revwAVL(root->left);
        revwAVL(root->right);
        std::cout << root->value << ' ';
    }
}
void symwAVL(AVLNode* root) {
    if(root){
        symwAVL(root->left);
        std::cout << root->value << ' ';
        symwAVL(root->right);
    }
}

int heightAVL(AVLNode* node) {
	return node == NULL ? 0 : node->height;
}

int bfactorAVL(AVLNode* node) {
	return node == NULL ? 0 : (heightAVL(node->right) - heightAVL(node->left));
}

void recalcHeightAVL(AVLNode* node) {
    int hl = heightAVL(node->left);
	int hr = heightAVL(node->right);
	node->height = (hl>hr ? hl : hr) + 1;
}

AVLNode* rotrightAVL(AVLNode* node)
{
    AVLNode* ltree = node->left;
    AVLNode* subtree = ltree->right;

    ltree->right = node;
    node->left = subtree;

    recalcHeightAVL(node);
    recalcHeightAVL(ltree);

    return ltree;
}

AVLNode* rotleftAVL(AVLNode* node)
{
    AVLNode* rtree = node->right;
    AVLNode* subtree = rtree->left;
 
    rtree->left = node;
    node->right = subtree;
 
    recalcHeightAVL(node);
    recalcHeightAVL(rtree);

    return rtree;
}

AVLNode* balanceAVL(AVLNode* node) {
	recalcHeightAVL(node);

	if(bfactorAVL(node) == 2) {
		if(bfactorAVL(node->right) < 0)
			node->right = rotrightAVL(node->right);
		return rotleftAVL(node);
	}
	if(bfactorAVL(node) == -2) {
		if(bfactorAVL(node->left) > 0)
			node->left = rotleftAVL(node->left);
		return rotrightAVL(node);
	}

	return node; 
}
