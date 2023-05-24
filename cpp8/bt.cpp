#include <iostream>
#include "bt.h"

BTNode* createBT(int value) {
	BTNode* root = new BTNode;
	root->left = NULL;
    root->right = NULL;
	root->value = value;
	return root;
}

BTNode* getMinBT(BTNode* root) {
	while (root->left) {
		root = root->left;
	}
	return root;
}

BTNode* getMaxBT(BTNode* root) {
	while (root->right) {
		root = root->right;
	}
	return root;
}

int sizeBT(BTNode* root, int size_count) {
	if (root) {
		size_count++;
        return sizeBT(root->left) + sizeBT(root->right);
	} else
        return size_count;
}

void printBT(BTNode* node, const std::string& rpf, const std::string& mpf, const std::string& lpf) {
	if (node != NULL) {
        if (node->right)
            printBT(node->right, rpf + "   ", rpf + ".-->", rpf + "|  ");
        std::cout << mpf << node->value << std::endl;
        if (node->left)
            printBT(node->left, lpf + "|  ", lpf + "`-->", lpf + "   ");
    }
}

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

BTNode* deleteBT(int key, BTNode* root) {
    if (root == NULL)
        return NULL;
 
    if (key < root->value)
        root->left = deleteBT(key, root->left);
    else if (key > root->value)
        root->right = deleteBT(key, root->right);
    else {
        if (root->left == NULL && root->right == NULL)
            return NULL;
        else if (root->left == NULL) {
            BTNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            BTNode* temp = root->left;
            delete root;
            return temp;
        }
        BTNode* temp = getMinBT(root->right);
        root->value = temp->value;
        root->right = deleteBT(temp->value, root->right);
    }
    return root;
}

void addBT(int value, BTNode*& root) {
    if (root == NULL)
        root = createBT(value);
    else
        insertBT(value, root);
}

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

void strBT(BTNode* root) {
    if(root){
        std::cout << root->value << ' ';
        strBT(root->left);
        strBT(root->right);
    }
}
void revBT(BTNode* root) {
    if(root){
        revBT(root->left);
        revBT(root->right);
        std::cout << root->value << ' ';
    }
}
void symBT(BTNode* root) {
    if(root){
        symBT(root->left);
        std::cout << root->value << ' ';
        symBT(root->right);
    }
}

void destroyBT(BTNode* root) {
    if(root!=NULL) {
        destroyBT(root->left);
        destroyBT(root->right);
        delete root;
    }
}