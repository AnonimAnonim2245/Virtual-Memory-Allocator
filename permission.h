#ifndef permission_H_INCLUDED
#define permission_H_INCLUDED
#include"alloc.h"
#include"miniblock.h"
#include"block.h"
#include"traverse.h"
#include"permission.h"
#include<stdint.h>
#include <inttypes.h>
#include<stdio.h>
#include<stddef.h>
#include<string.h>
#include<stdint.h>

void Permission(uint8_t num,char *R,char *W,char *X);
void PUT(FILE* fp,FILE* gp,struct Miniblock** MiniNode,int size);
void SEE(FILE* gp,struct Miniblock** MiniNode,int size);
#endif
