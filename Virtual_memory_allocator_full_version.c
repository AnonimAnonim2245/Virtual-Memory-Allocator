#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include <inttypes.h>
#include<string.h>
#include<locale.h>
typedef struct mini
{
 uint64_t start_address;// adresa de început a zonei, un indice din arenă
 size_t size;// size-ul miniblock-ului
 uint8_t perm;// permisiunile asociate zonei, by default RW-
 void* rw_buffer;// buffer-ul de date, folosit pentru opearțiile de read() și write()
 struct mini* urmator, * anterior;
}Miniblock;

typedef struct block
{
   uint64_t start_address; // adresa de început a zonei, un indice din arenă
   size_t size; // dimensiunea totală a zonei, suma size-urilor miniblock-urilor
   void* miniblock_list; // lista de miniblock-uri adiacente
   struct block* urmator, * anterior;
} Block;
Miniblock *MiniNodeF(uint64_t start_adress, size_t size) {
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

Block *NodeF(Miniblock* Node) {
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

void insertBeginingMiniNode(Miniblock **head, uint64_t start_address, size_t size) {
  Miniblock *newNode = MiniNodeF(start_address,size);
  newNode->urmator = *head;
  newNode->anterior = NULL;

  if((*head)!=NULL)
  {
      (*head)->anterior = newNode;
  }
  *head = newNode;
}


void insertBeginningMiniNode2(Miniblock **head, Miniblock* elem) {

  elem->urmator = *head;

  if((*head)!=NULL)
  {
      (*head)->anterior = elem;
  }
  *head = elem;
}

void insertFinalMiniNode(Miniblock **head, uint64_t start_address, size_t size) {
  Miniblock *newNode = MiniNodeF(start_address,size);
  newNode->urmator = NULL;
  (*head)->urmator = newNode;
  newNode->anterior = (*head);
}

void insertFinalMiniNode2(Miniblock **head, Miniblock* elem) {

  elem->urmator = NULL;
  (*head)->urmator = elem;
  elem->anterior = (*head);
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
void deleteNextMiniNode(Miniblock** currentMiniNode)
{
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

void ALLOC_ARENA(FILE *pf, uint64_t* memory)
{
    fscanf(pf,"%"SCNu64,memory);

}
void Traverse(Miniblock** MiniNode)
{
    while((*MiniNode)->urmator!=NULL)
    {
        (*MiniNode)=(*MiniNode)->urmator;
    }


}
void Free(Block** Node)
{
    Block* Node2=*Node,*copy;
    while((Node2)!=NULL)
    {
         copy=Node2;
         Miniblock* MiniNode2=(Miniblock*)(Node2->miniblock_list);
         Miniblock* Copy;
         while(MiniNode2!=NULL)
         {
             Copy=MiniNode2;
             MiniNode2=MiniNode2->urmator;
             free(Copy);
         }
        (Node2)=(Node2)->urmator;
         free(copy);
    }


}
void Traverse2(Miniblock** MiniNode,int *sum)
{
    while((*MiniNode)->urmator!=NULL)
    {
        *sum+=(*MiniNode)->size;
        (*MiniNode)=(*MiniNode)->urmator;
    }

}
void Traverse_rev(Miniblock** MiniNode)
{
    while((*MiniNode)->anterior!=NULL)
    {
        (*MiniNode)=(*MiniNode)->anterior;
    }
}
void Traverse_rev2(Block** Node)
{
    while((*Node)->anterior!=NULL)
    {
        Miniblock* MiniNode=(Miniblock*)((*Node)->miniblock_list);
            //printf("%"PRIu64" ",(MiniNode)->perm);

        (*Node)=(*Node)->anterior;
    }
}
void Permission(uint8_t num,char *R,char *W,char *X)
{
    int i=0;
    if(num==0)
    {
        *R='-';
        *W='-';
        *X='-';
    }
    while(num>0)
    {
        if(i==0)
        {
            if(num%2==1)
             *X='X';
            else
             *X='-';
        }
        else if(i==1)
        {
            if(num%2==1)
             *W='W';
            else
             *W='-';
        }
        else if(i==2)
        {
            if(num%2==1)
             *R='R';
            else
             *R='-';
        }
        i++;
        num=num/2;
    }

}
int ERROR_MESSAGE(FILE* gp,size_t size, uint64_t start_address, Block* Node)
{

    if(start_address<=(Node)->start_address && start_address+size>(Node)->start_address)
    {
                       fprintf(gp,"ERROR: Already allocated\n");
                        return 1;
    }
    if(start_address>=(Node)->start_address && start_address<(Node)->start_address+(Node)->size)
    {
                        fprintf(gp,"ERROR: Already allocated\n");
                        return 1;
    }
    return 0;
}
void Gasire(Block** Node, Miniblock** MiniNode, uint64_t memory_region)
{
    int ok=0;

    while(ok==0 && Node!=NULL)
    {
        (*MiniNode) = (Miniblock*)((*Node)->miniblock_list);

        while((*MiniNode)->start_address != memory_region && (*MiniNode)!=NULL)
        {
            (*MiniNode)=(*MiniNode)->urmator;
            if((*MiniNode)==NULL)
                break;

        }
        if((*MiniNode)!=NULL)
           ok=1;
        else
        {(*Node)=(*Node)->urmator;}

    }

//printf("%"PRIu64"=== ",(*MiniNode)->perm);

}

void PUT(FILE* fp,FILE* gp,Miniblock** MiniNode,int size)
{
    char c,R,W,X;

    Permission((*MiniNode)->perm,&R,&W,&X);

    if(W=='-'){
    fprintf(gp,"Invalid permissions for write.");
    return;
    }

    if((*MiniNode)->size < size)
        {fprintf(gp,"Warning: size was bigger than the block size. Writing %zu characters.\n",(*MiniNode)->size);
        size=(*MiniNode)->size+1;
        }
    else
    {
        size=size+1;
    }
    char* Element;
    (*MiniNode)->rw_buffer=(void*)malloc(sizeof(void)*size);;
    Element = (char*)((*MiniNode)->rw_buffer);

    c=fgetc(fp);
    fgets(Element,size,fp);
    (*MiniNode)->rw_buffer = Element;
}
void SEE(FILE* gp,Miniblock** MiniNode,int size)
{
    char R,W,X;
    Permission((*MiniNode)->perm,&R,&W,&X);
    if(R=='-')
    {
      fprintf(gp,"Invalid permissions for read.");
      return;
    }
    if((*MiniNode)->size < size)
        {fprintf(gp,"Warning: size was bigger than the block size. Writing %zu characters.\n",(*MiniNode)->size);
        size=(*MiniNode)->size+1;
        }
    else
    {
        size=size+1;
    }
    char* Element;
    Element = (char*)(sizeof(char)*size);
    Element = (char*)((*MiniNode)->rw_buffer);
    fputs(Element,gp);
    fprintf(gp,"\n");
}

void ReArrangeBlocks(Block** Node,int *number_blocks)
{
    Miniblock* Node2,* Node3,* Node4,* copy,*MiniNode;
    MiniNode = (Miniblock*)((*Node)->miniblock_list);
    copy = MiniNode;

    while((MiniNode)->start_address+(MiniNode)->size==(MiniNode)->urmator->start_address)
    {
        (MiniNode)=(MiniNode)->urmator;
    }
    Node2 = MiniNode;

    Node3 = MiniNode->urmator;

    Traverse_rev(&Node2);
    Node2->urmator = NULL;
    Node3->anterior=NULL;


    int sum=0;
    Traverse2(&Node3,&sum);
    (*Node)->size-=sum;

    Traverse_rev(&Node3);
    insertMiddleNode(Node,Node3);
    (*Node)->urmator->size=sum;
    Traverse_rev2(Node);


    (*number_blocks)++;




}
void ALLOC_BLOCK(FILE* pf,FILE* gp,Block** Node,uint64_t* occupied_memory,int* number_blocks,int* number_miniblocks)
{
    uint64_t start_address;
    size_t size;
    Block* headcopy;
    Block* prev,*next;

    headcopy = *Node;
    prev = *Node;
    next = *Node;

    fscanf(pf,"%"SCNu64,&start_address);
    fscanf(pf,"%zu",&size);


    if(headcopy==NULL)
    {
         Miniblock* MiniNode=NULL;
         MiniNode = MiniNodeF(start_address,size);
         *Node = NodeF(MiniNode);
         (*occupied_memory)=(*Node)->size;
         (*number_blocks)++;
         (*number_miniblocks)++;
    }
    else
    {
            /// incercam prima data o strategie in care punem inaintea elementului
            int ok;
            Miniblock* MiniNode1;
            if(start_address < (*Node)->start_address)
            {
                ok=1;
                while(start_address<=(*Node)->start_address && (*Node)->anterior!=NULL)
                {
                    if(ERROR_MESSAGE(gp,size,start_address,(*Node))==1){
                     return;}

                    (*Node)=(*Node)->anterior;
                }
                if((*Node)->start_address < start_address)
                {
                (*Node) = (*Node)->urmator;
                }
                MiniNode1 = (Miniblock*)((*Node)->miniblock_list);
                while(start_address>(MiniNode1)->start_address && (MiniNode1)->urmator!=NULL)
                {
                    MiniNode1 = MiniNode1->urmator;
                }

            }
            else if(start_address > (*Node)->start_address)
            {
                ok=2;
                while(start_address>=(*Node)->start_address && (*Node)->urmator!=NULL)
                {
                    if(ERROR_MESSAGE(gp,size,start_address,(*Node))==1){
                        return;}
                    (*Node)=(*Node)->urmator;
                }
                if((*Node)->start_address > start_address)
                {
                (*Node) = (*Node)->anterior;
                }
                MiniNode1 = (Miniblock*)((*Node)->miniblock_list);
                while(start_address>(MiniNode1)->start_address && (MiniNode1)->urmator!=NULL)
                {
                    MiniNode1 = MiniNode1->urmator;
                }
            }

            if(MiniNode1->anterior==NULL && (*Node)->anterior==NULL)
            {


                if((start_address + size) != (*Node)->start_address)
                {
                    Miniblock* MiniNode=NULL;
                    MiniNode = MiniNodeF(start_address,size);
                    insertBeginingNode(Node,MiniNode);
                    (*occupied_memory)+=(*Node)->size;
                    (*number_blocks)++;
                    (*number_miniblocks)++;

                }
                else
                {
                    Miniblock* MiniNode2;
                    size_t cop=0;
                    MiniNode2 = (Miniblock*)((*Node)->miniblock_list);
                    cop=((*Node)->size)+size;
                    insertBeginingMiniNode(&MiniNode2,start_address,size);
                    insertBeginingNode(Node,MiniNode2);
                    *Node=(*Node)->anterior;
                    (*Node)->size=cop;
                    (*occupied_memory)+=(*Node)->size;
                    (*number_miniblocks)++;
                    deleteNextNode(Node);


                }
            }
            else if((*Node)->urmator==NULL)
            {
                Miniblock* MiniNode4=(Miniblock*)malloc(sizeof(Miniblock));
                MiniNode4 = (Miniblock*)((*Node)->miniblock_list);

                Traverse(&MiniNode4);

                if(start_address != (MiniNode4->start_address+(MiniNode4)->size))
                {
                    Miniblock* MiniNode=NULL;
                    MiniNode = MiniNodeF(start_address,size);
                    insertFinalNode(Node,MiniNode);
                    (*occupied_memory)+=(*Node)->size;
                    (*number_blocks)++;
                    (*number_miniblocks)++;

                }
                else if(start_address == (MiniNode4->start_address+(MiniNode4)->size))
                {
                    Miniblock* MiniNode2, *copy;
                    size_t cop=0;
                    MiniNode2 = (Miniblock*)((*Node)->miniblock_list);
                    cop=(*Node)->size+size;
                    insertFinalMiniNode(&MiniNode4,start_address,size);
                    Traverse_rev(&MiniNode4);
                    (*Node)->size=cop;
                    (*occupied_memory)+=(*Node)->size;
                    (*number_miniblocks)++;
                    (*Node)->miniblock_list=MiniNode4;
                }
            }
            else
            {
                Miniblock* MiniNode4=(Miniblock*)malloc(sizeof(Miniblock));
                MiniNode4 = (Miniblock*)((*Node)->miniblock_list);
                Traverse(&MiniNode4);
                if(((start_address + size) != (*Node)->urmator->start_address)
                    || (start_address!= (MiniNode4->start_address+size)))
                {
                    if(ok==2)
                      {(*Node)=(*Node)->urmator;}

                    if((start_address+size)==(*Node)->start_address)
                    {
                        size_t cop=0;
                        Miniblock* MiniNode2;
                        MiniNode2 = (Miniblock*)((*Node)->miniblock_list);
                        cop=(*Node)->size+size;
                        insertBeginingMiniNode(&MiniNode2,start_address,size);
                        insertMiddleNode(Node,MiniNode2);

                        (*Node) = (*Node)->anterior;
                        (*Node)->size=cop;
                        (*occupied_memory)+=(*Node)->size;
                        (*number_miniblocks)++;
                        deleteNextNode(Node);

                    }
                    else if((start_address== (MiniNode4->start_address+MiniNode4->size)))
                    {
                        if(ok==2)
                            (*Node)=(*Node)->anterior;
                        insertFinalMiniNode(&MiniNode4,start_address,size);
                        (*Node)->size+=size;
                        (*occupied_memory)+=(*Node)->size;
                        (*number_miniblocks)++;

                        Traverse_rev(&MiniNode4);
                        ((*Node)->miniblock_list) = MiniNode4;


                    }
                    else
                    {
                        if(ok==2){(*Node)=(*Node)->anterior;}
                        Miniblock* MiniNode=NULL;
                        MiniNode = MiniNodeF(start_address,size);
                        insertMiddleNode(Node,MiniNode);
                        (*occupied_memory)+=(*Node)->size;
                        (*number_blocks)++;
                        (*number_miniblocks)++;

                    }


                }
                else
                {
                    size_t cop=0;
                    Miniblock* MiniNode2,* MiniNode3,*copy;
                    MiniNode2 = (Miniblock*)((*Node)->miniblock_list);
                    copy = MiniNode2;
                    Traverse(&MiniNode2);
                    cop =MiniNode2->size + (*Node)->size;
                    MiniNode3 = (Miniblock*)((*Node)->urmator->miniblock_list);

                    insertFinalMiniNode(&MiniNode2,start_address,size);
                    MiniNode2 = MiniNode2->urmator;
                    insertFinalMiniNode2(&MiniNode2,MiniNode3);
                    cop +=MiniNode3->size;

                    MiniNode2 = copy;
                    ((*Node)->miniblock_list) = MiniNode2;
                    (*Node)->size = cop;
                    (*occupied_memory)+=(*Node)->size;
                    (*number_blocks)--;
                    (*number_miniblocks)+=1;
                    deleteNextNode((Node));
                }
            }
        }
}


void PRINTNode(FILE* gp,Block* Node,uint64_t memory,uint64_t occupied_memory, int number_block,int number_miniblocks)
{
    char R,W,X;
    fprintf(gp,"Total memory: 0x%x\n",memory);
    fprintf(gp,"Free memory: 0x%x\n",(memory-occupied_memory));
    fprintf(gp,"Number of allocated blocks: %d\n",number_block);
    fprintf(gp,"Number of allocated miniblocks: %d\n\n",number_miniblocks);

    int i=1,j=1;
    while(Node!=NULL)
    {
        fprintf(gp,"Block %d begin\n",i);
        fprintf(gp,"Zone: 0x%x - 0x%x\n",Node->start_address,(Node->start_address+Node->size));
        Miniblock* MiniNode=(Miniblock*)(Node->miniblock_list);
        j=1;
        while(MiniNode!=NULL)
        {
         Permission(MiniNode->perm,&R,&W,&X);
         fprintf(gp,"Miniblock %d:\t\t0x%x\t\t-\t\t0x%x\t\t| %c%c%c\n",j,MiniNode->start_address,(MiniNode->start_address+MiniNode->size),R,W,X);
         MiniNode=MiniNode->urmator;
         j++;
        }
        fprintf(gp,"Block %d end\n\n",i);
        i++;
        Node=Node->urmator;
    }
}
void PRINTNode2(FILE* gp,Block* Node)
{
    char R,W,X;


    int i=1,j=1;
    while(Node!=NULL)
    {
        fprintf(gp,"Block %d begin\n",i);
        fprintf(gp,"Zone: 0x%x - 0x%x\n",Node->start_address,(Node->start_address+Node->size));
        Miniblock* MiniNode=(Miniblock*)(Node->miniblock_list);
        j=1;
        while(MiniNode!=NULL)
        {
         Permission(MiniNode->perm,&R,&W,&X);
         fprintf(gp,"Miniblock %d:\t\t0x%x\t\t-\t\t0x%x\t\t| %c%c%c\n",j,MiniNode->start_address,(MiniNode->start_address+MiniNode->size),R,W,X);
         MiniNode=MiniNode->urmator;
         j++;
        }
        fprintf(gp,"Block %d end\n\n",i);
        i++;
        Node=Node->urmator;
    }
}



void Program(FILE* pf,FILE* gp)
{
    char* instruction,ok=0;
    Miniblock *MiniNode = (Miniblock *)malloc(sizeof(Miniblock));
    Block *Node = (Block *)malloc(sizeof(Block));
    Block *Node2 = (Block *)malloc(sizeof(Block));

    Node=NULL;
    MiniNode=NULL;
    uint64_t memory, occupied_memory=0,memory_region;
    int number_blocks=0,number_miniblocks=0,word_numbers;
    instruction = (char*)malloc(sizeof(char)*15);

    while(!feof(pf))
    {
        fscanf(pf,"%s",instruction);
       // printf("%s\n",instruction);

        if(strcmp(instruction,"ALLOC_ARENA")==0)
        {
            ALLOC_ARENA(pf,&memory);
        }
        else if(strcmp(instruction,"ALLOC_BLOCK")==0)
        {
            if(Node==NULL)
                ok=2;
            ALLOC_BLOCK(pf,gp,&Node,&occupied_memory,&number_blocks,&number_miniblocks);

        }
        else if(strcmp(instruction,"PMAP")==0)
        {

            Node2=Node;

            while(Node2->anterior!=NULL)
            {
                Node2=Node2->anterior;
            }
            PRINTNode(gp,Node2,memory,occupied_memory,number_blocks,number_miniblocks);
        }
        else if(strcmp(instruction,"WRITE")==0)
        {
            fscanf(pf,"%"SCNu64,&memory_region);
            fscanf(pf,"%d",&word_numbers);
            Miniblock* MiniNode;
            Traverse_rev2(&Node);
            Gasire(&Node,&MiniNode,memory_region);
            PUT(pf,gp,&MiniNode,word_numbers);

        }
        else if(strcmp(instruction,"READ")==0)
        {
            fscanf(pf,"%"SCNu64,&memory_region);
            fscanf(pf,"%d",&word_numbers);
            Miniblock* MiniNode;
            Traverse_rev2(&Node);
            Gasire(&Node,&MiniNode,memory_region);
            SEE(gp,&MiniNode,word_numbers);

        }
        else if(strcmp(instruction,"FREE_BLOCK")==0)
        {
          int ok=0;
          fscanf(pf,"%"SCNu64,&memory_region);
          Miniblock* MiniNode;
          Traverse_rev2(&Node);
          Gasire(&Node,&MiniNode,memory_region);
          if(MiniNode->anterior!=NULL || MiniNode->urmator!=NULL)
            {ok=1;}
          number_miniblocks--;
          Node->size-=MiniNode->size;
          deleteNextMiniNode(&MiniNode);
          if(MiniNode->anterior!=NULL)
            MiniNode=MiniNode->anterior;
          else if(MiniNode->urmator!=NULL)
            MiniNode=MiniNode->urmator;
          Traverse_rev(&MiniNode);
          Node->miniblock_list=MiniNode;
          if(ok==1)
          {ReArrangeBlocks(&Node,&number_blocks);}
          Traverse_rev2(&Node);

        }
        else if(strcmp(instruction,"MPROTECT")==0)
        {
          fscanf(pf,"%"SCNu64,&memory_region);
          Miniblock* MiniNode;
          Traverse_rev2(&Node);
          Gasire(&Node,&MiniNode,memory_region);
          fscanf(pf,"%s",instruction);

          if(strcmp(instruction,"PROT_NONE")==0)
          {
             MiniNode->perm = 0;
          }
          else if(strcmp(instruction,"PROT_READ")==0)
          {
              MiniNode->perm=4;
          }
          else if(strcmp(instruction,"PROT_WRITE")==0)
          {
              MiniNode->perm=2;
          }
          else if(strcmp(instruction,"PROT_EXEC")==0)
          {
              MiniNode->perm=1;
          }
          Traverse_rev(&MiniNode);
          Node->miniblock_list=MiniNode;
          Traverse_rev2(&Node);


        }
        else if(strcmp(instruction,"DEALLOC_ARENA")==0)
        {
            Traverse_rev2(&Node);
            Free(&Node);
            memory=0;
            occupied_memory=0;
        }

    }
    fclose(pf);
    fclose(gp);

}
int main()
{
    typedef struct mini Miniblock;
    typedef struct block Block;

    Miniblock* mini1= (Miniblock*)malloc(sizeof(Miniblock));
    // Initialize miniblock1
    FILE *pf,*gp;
    Block *nod;
    Miniblock *mininod;
    if(((pf = fopen("temasda.txt", "r+t")) == NULL) || ((gp = fopen("outputsda.txt", "w+t")) == NULL))
    {
    printf("Unul sau ambele fisiere nu poate/pot fi deschis/e !\n");
    }

    Program(pf,gp);

    return 0;
}
