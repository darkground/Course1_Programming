#include <iostream>
#include "avl.h"

// Создать АВЛ-дерево
AVLNode* createAVL(int value) {
	AVLNode* root = new AVLNode;
	root->left = NULL;
    root->right = NULL;
    root->height = 0;
	root->value = value;
	return root;
}

// Минимальный элемент в АВЛ-дереве 
AVLNode* getMinAVL(AVLNode* root) {
	while (root->left)
		root = root->left;
	return root;
}

// Максимальный элемент в АВЛ-дереве
AVLNode* getMaxAVL(AVLNode* root) {
	while (root->right)
		root = root->right;
	return root;
}

// Размер АВЛ-дерева
int sizeAVL(AVLNode* root, int size_count) {
	if (root) {
		size_count++;
        return sizeAVL(root->left) + sizeAVL(root->right);
	} else
        return size_count;
}

// Вывод АВЛ-дерева в указанный ostream
void printAVL(AVLNode* root, const std::string& rpf, const std::string& mpf, const std::string& lpf, std::ostream& os) {
	if (root != NULL) {
        if (root->right)
            printAVL(root->right, rpf + "   ", rpf + ".-->", rpf + "|  ", os);
        std::cout << mpf << root->value << std::endl;
        if (root->left)
            printAVL(root->left, lpf + "|  ", lpf + "`-->", lpf + "   ", os);
    }
}

// Поиск в АВЛ-дереве значения
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

// Удаление элемента из АВЛ-дерева
AVLNode* deleteAVL(int value, AVLNode* root) {
	if (root == NULL)
		return NULL;

	if (value < root->value)
		root->left = deleteAVL(value, root->left);
	else if (value > root->value)
		root->right = deleteAVL(value, root->right);
	else {
        if (root->left == NULL && root->right == NULL)
            root = NULL;
        else if (root->left == NULL || root->right == NULL)
            root = root->left ? root->left : root->right;
        else {
            AVLNode* minnode = getMinAVL(root->right);
            root->value = minnode->value;
            root->right = deleteAVL(minnode->value, root->right);
        }
	}

    return root ? balanceAVL(root) : NULL;
}

// Добавить значение в АВЛ-дерево
void addAVL(int value, AVLNode*& root) {
    if (root == NULL)
        root = createAVL(value);
    else
        root = insertAVL(value, root);
}

// Добавить значение в АВЛ-дерево (root != null)
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

// Уничтожить АВЛ-дерево
void destroyAVL(AVLNode* root) {
    if(root!=NULL) {
        destroyAVL(root->left);
        destroyAVL(root->right);
        delete root;
    }
}

// Straight-walk: Прямой обход АВЛ-дерева
void strwAVL(AVLNode* root) {
    if(root){
        std::cout << root->value << ' ';
        strwAVL(root->left);
        strwAVL(root->right);
    }
}

// Reverse-walk: Обратный обход АВЛ-дерева
void revwAVL(AVLNode* root) {
    if(root){
        revwAVL(root->left);
        revwAVL(root->right);
        std::cout << root->value << ' ';
    }
}

// Symmetrical-walk: Симметричный обход АВЛ-дерева
void symwAVL(AVLNode* root) {
    if(root){
        symwAVL(root->left);
        std::cout << root->value << ' ';
        symwAVL(root->right);
    }
}

// Получить высоту АВЛ-узла (если узел == null, высота равна 0)
int heightAVL(AVLNode* node) {
	return node == NULL ? 0 : node->height;
}

// Получить фактор сбалансированности АВЛ-узла (если узел == null, фактор равен 0)
int bfactorAVL(AVLNode* node) {
	return node == NULL ? 0 : (heightAVL(node->right) - heightAVL(node->left));
}

// Пересчитать высоту АВЛ-узла и записать в node->height
void recalcHeightAVL(AVLNode* node) {
    int hl = heightAVL(node->left);
	int hr = heightAVL(node->right);
	node->height = (hl>hr ? hl : hr) + 1;
}

// Малое правое вращение
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

// Малое левое вращение
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

// Сбалансировать узел
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
