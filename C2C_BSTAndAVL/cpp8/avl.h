struct AVLNode {
    int height;
    int value;
    AVLNode* left;
    AVLNode* right;
};

AVLNode* searchAVL(int value, AVLNode* root);
AVLNode* createAVL(int value);
AVLNode* getMinAVL(AVLNode* node);
AVLNode* getMaxAVL(AVLNode* node);
AVLNode* deleteAVL(int value, AVLNode* root);
AVLNode* insertAVL(int value, AVLNode* root);
void destroyAVL(AVLNode* root);
void printAVL(AVLNode* node, std::ostream& os, const std::string& rpf = "", const std::string& mpf = "", const std::string& lpf = "");
void addAVL(int value, AVLNode*& root);
int sizeAVL(AVLNode* root, int size_count = 0);
void strwAVL(AVLNode* root);
void revwAVL(AVLNode* root);
void symwAVL(AVLNode* root);

int heightAVL(AVLNode* node);
int bfactorAVL(AVLNode* node);
void recalcHeightAVL(AVLNode* p);
AVLNode* rotrightAVL(AVLNode* p);
AVLNode* rotleftAVL(AVLNode* q);
AVLNode* balanceAVL(AVLNode* p);