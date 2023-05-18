#include <string>

struct BTNode
{
    int value;
    BTNode* left;
    BTNode* right;
};

BTNode* searchBT(int key, BTNode* root);
BTNode* createBT(int value);
BTNode* getMinBT(BTNode* root);
BTNode* getMaxBT(BTNode* root);
void insertBT(int key, BTNode* root);
void destroyBT(BTNode* root);
void printBT(BTNode* node, const std::string& prefix = "", bool isLeft = false);
void addBT(int value, BTNode*& root);
int sizeBT(BTNode* root, int size_count = 0);