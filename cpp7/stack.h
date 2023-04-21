#include <string>

using namespace std;

struct StackNode {
	string value;
	struct StackNode* next;
};

int stackSize(StackNode*);
StackNode* stackCreate(const string&);
StackNode* stackLast(StackNode*);
StackNode* stackGetLastButOne(StackNode*);
void stackAdd(StackNode*&, const string&);
string stackTake(StackNode*&);
void stackPush(StackNode*&, string);
void stackPushBack(StackNode*, string);
void stackClear(StackNode*);
string stackPop(StackNode*&);
string stackPopBack(StackNode*);
void stackPrint(StackNode*, ostream&);