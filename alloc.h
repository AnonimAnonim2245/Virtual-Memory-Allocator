#ifndef alloc_H_INCLUDED
#define alloc_H_INCLUDED
#include"alloc.h"
#include"miniblock.h"
#include"block.h"
#include<stdio.h>
#include<stddef.h>
#include<string.h>
#include<stdint.h>

void ALLOC_ARENA(FILE *pf, uint64_t* memory);
void ALLOC_BLOCK(FILE* pf,FILE* gp,struct Block** Node,uint64_t* occupied_memory,int* number_blocks,int* number_miniblocks);
void ReArrangeBlocks(struct Block** Node,int *number_blocks);
void Free(struct Block** Node);
#endif // alloc_H_INCLUDED

