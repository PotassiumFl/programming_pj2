#include <stdio.h>
#include <windows.h>
#include "struct.h"
#include "node.h"
#ifndef DATA_H
#define DATA_H
void initialization(int i, node *head);
void iftreasure(node *last);
void manualcal(node *last);
void mapimport(int i, node *head);
void mapupdate(node *last);
void movement(node **last);
void treasurechange(node *last);
#endif