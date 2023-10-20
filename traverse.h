#ifndef traverse_H_INCLUDED
#define traverse_H_INCLUDED
#include"alloc.h"
#include"miniblock.h"
#include"block.h"
#include"traverse.h"
#include<stdio.h>
#include<stddef.h>
#include<string.h>
#include<stdint.h>

void Traverse(struct Miniblock** MiniNode);
void Traverse2(struct Miniblock** MiniNode,int *sum);
void Traverse_rev(struct Miniblock** MiniNode);
void Traverse_rev2(struct Block** Node);

#endif
