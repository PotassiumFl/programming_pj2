#include <stdlib.h>
#include "struct.h"
#ifndef NODE_H
#define NODE_H
void movenode(node **last);
node *nodecreate();
void passinfo(node *prev, node *now);
#endif