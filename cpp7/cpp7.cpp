#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "stack.h"

using namespace std;

int main()
{
    StackNode* node = NULL;
	stackAdd(node, "hell");
	stackAdd(node, "yeah");
	stackAdd(node, "omg");
    cout << stackSize(node);
    cout << stackPop(node);
    cout << stackPop(node);
    cout << stackPop(node);
	return 0;
}