#include"miniblock.h"
#include<stddef.h>
#include<stdlib.h>

struct Miniblock *MiniNodeF(uint64_t start_adress, size_t size) {
     typedef struct Miniblock Miniblock;

  Miniblock *newNode = (Miniblock *)malloc(sizeof(Miniblock));
  if (newNode == NULL) {
    printf("Alocarea memoriei a esuat.\n");
    exit(1);
  }
  newNode->start_address = start_adress;
  newNode->size = size;
  newNode->perm = 6;
  newNode->urmator = NULL;
  newNode->anterior = NULL;
  return newNode;
}

void insertBeginingMiniNode(struct Miniblock **head, uint64_t start_address, size_t size) {
     typedef struct Miniblock Miniblock;

  Miniblock *newNode = MiniNodeF(start_address,size);
  newNode->urmator = *head;
  newNode->anterior = NULL;

  if((*head)!=NULL)
  {
      (*head)->anterior = newNode;
  }
  *head = newNode;
}


void insertBeginningMiniNode2(struct Miniblock **head, Miniblock* elem) {

  elem->urmator = *head;

  if((*head)!=NULL)
  {
      (*head)->anterior = elem;
  }
  *head = elem;
}

void insertFinalMiniNode(struct Miniblock **head, uint64_t start_address, size_t size) {
 typedef struct Miniblock Miniblock;
  Miniblock *newNode = MiniNodeF(start_address,size);
  newNode->urmator = NULL;
  (*head)->urmator = newNode;
  newNode->anterior = (*head);
}

void insertFinalMiniNode2(struct Miniblock **head, struct Miniblock* elem) {

  elem->urmator = NULL;
  (*head)->urmator = elem;
  elem->anterior = (*head);
}

void deleteNextMiniNode(struct Miniblock** currentMiniNode)
{
     typedef struct Miniblock Miniblock;

    if(*currentMiniNode==NULL)
    {
         printf("Cannot delete next mini node as it doesn't exist or it's the last node.\n");
        return;
    }
    //printf("####");
    Miniblock* Element = *currentMiniNode;
    if((Element)->urmator!=NULL && (Element)->anterior!=NULL)
        (Element)->urmator->anterior = (Element)->anterior;
    if((Element)->anterior!=NULL)
        (Element)->anterior->urmator = (Element)->urmator;

    free(Element);
   // printf("!@@");

}
