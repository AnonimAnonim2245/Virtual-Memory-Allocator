#include"block.h"
#include"miniblock.h"

#include<stdlib.h>

Block *NodeF(struct Miniblock* Node) {
    typedef struct Miniblock Miniblock;
  Block *newNode = (Block *)malloc(sizeof(Block));
  if (newNode == NULL) {
    printf("Alocarea memoriei a esuat.\n");
    exit(1);
  }
  newNode->start_address = Node->start_address;
  newNode->size = Node->size;
  newNode->miniblock_list = Node;
  newNode->urmator = NULL;
  newNode->anterior = NULL;
  return newNode;
}



void insertBeginingNode(Block **head, Miniblock *MiniNode) {
  Block *newNode = NodeF(MiniNode);
  newNode->urmator = *head;
  newNode->anterior = NULL;

  if((*head)!=NULL)
  {
      (*head)->anterior = newNode;
  }
}

void insertFinalNode(Block **head, Miniblock *MiniNode) {
  Block *newNode = NodeF(MiniNode);
  newNode->urmator = NULL;
  (*head)->urmator = newNode;
  newNode->anterior = (*head);


}

void insertMiddleNode(Block **head, Miniblock *MiniNode) {
  Block *newNode = NodeF(MiniNode);

  newNode->urmator = (*head)->urmator;
  (*head)->urmator = newNode;
  newNode->anterior = (*head);

  if(newNode->urmator!=NULL)
  {
      newNode->urmator->anterior = newNode;
  }
}

void deleteNextNode(Block** currentNode) {
    if ((*currentNode) == NULL || (*currentNode)->urmator == NULL) {
        printf("Cannot delete next node as it doesn't exist or it's the last node.\n");
        return;
    }
    Block* nodeToDelete = (*currentNode)->urmator;

    (*currentNode)->urmator = nodeToDelete->urmator; // Update current node's next pointer
    if (nodeToDelete->urmator != NULL && nodeToDelete!=NULL) {
        nodeToDelete->urmator->anterior = (*currentNode); // Update next node's prev pointer
    }

    free(nodeToDelete); // Free memory occupied by the eliminated node
}

