#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED
#include"block.h"
#include"miniblock.h"
#include"alloc.h"

#include <inttypes.h>
#include<stddef.h>
#include<string.h>
#include<stdio.h>
#include<stdint.h>

typedef struct Block
{
   uint64_t start_address; // adresa de început a zonei, un indice din arenă
   size_t size; // dimensiunea totală a zonei, suma size-urilor miniblock-urilor
   void* miniblock_list; // lista de miniblock-uri adiacente
   struct Block* urmator, * anterior;
}Block;
//typedef struct block Block;
Block *NodeF(struct Miniblock* Node);
void insertBeginingNode(struct  Block **head,struct Miniblock *MiniNode);
void insertFinalNode(struct Block **head,struct Miniblock *MiniNode);
void insertMiddleNode(struct Block **head, struct Miniblock *MiniNode);
void deleteNextNode(struct Block** currentNode);
#endif
