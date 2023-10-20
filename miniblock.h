#ifndef MINIBLOCK_H_INCLUDED
#define MINIBLOCK_H_INCLUDED
#include"miniblock.h"
#include"alloc.h"
#include <inttypes.h>
#include<stddef.h>
#include<string.h>
#include<stdio.h>
#include<stdint.h>

typedef struct Miniblock
{
 uint64_t start_address;// adresa de început a zonei, un indice din arenă
 size_t size;// size-ul miniblock-ului
 uint8_t perm;// permisiunile asociate zonei, by default RW-
 void* rw_buffer;// buffer-ul de date, folosit pentru opearțiile de read() și write()
 struct Miniblock* urmator, * anterior;
}Miniblock;

Miniblock *MiniNodeF(uint64_t start_adress, size_t size);
void insertBeginingMiniNode(struct Miniblock **head, uint64_t start_address, size_t size);
void insertBeginningMiniNode2(struct Miniblock **head,struct Miniblock* elem);
void insertFinalMiniNode(struct Miniblock **head, uint64_t start_address, size_t size);
void insertFinalMiniNode2(struct Miniblock **head, struct Miniblock* elem);
void deleteNextMiniNode(struct Miniblock** currentMiniNode);
#endif
