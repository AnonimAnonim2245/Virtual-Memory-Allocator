#include"alloc.h"
#include"miniblock.h"
#include"block.h"
#include"traverse.h"
#include"permission.h"


int ERROR_MESSAGE(FILE* gp,size_t size, uint64_t start_address, struct Block* Node)
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
void Gasire(struct Block** Node,struct Miniblock** MiniNode, uint64_t memory_region)
{
    int ok=0;
    typedef struct Miniblock Miniblock;
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

}


void PRINTNode(FILE* gp,struct Block* Node,uint64_t memory,uint64_t occupied_memory, int number_block,int number_miniblocks)
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
        struct Miniblock* MiniNode=(struct Miniblock*)(Node->miniblock_list);
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
void PRINTNode2(FILE* gp,struct Block* Node)
{
    char R,W,X;


    int i=1,j=1;
    while(Node!=NULL)
    {
        fprintf(gp,"Block %d begin\n",i);
        fprintf(gp,"Zone: 0x%x - 0x%x\n",Node->start_address,(Node->start_address+Node->size));
        struct Miniblock* MiniNode=(struct Miniblock*)(Node->miniblock_list);
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
    char* instruction;
    typedef struct Block Block;
    typedef struct Miniblock Miniblock;
    int ok=0;
    //Miniblock *MiniNode = (Miniblock *)malloc(sizeof(Miniblock));
    Block *Node = (Block *)malloc(sizeof(Block));
    Block *Node2 = (Block *)malloc(sizeof(Block));

    Node=NULL;
   // MiniNode=NULL;
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
          ok=0;
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
    typedef struct Miniblock Miniblock;
    typedef struct Block Block;
    FILE *pf,*gp;

    if(((pf = fopen("temasda.txt", "r+t")) == NULL) || ((gp = fopen("outputsda.txt", "w+t")) == NULL))
    {
    printf("Unul sau ambele fisiere nu poate/pot fi deschis/e !\n");
    }

    Program(pf,gp);

    return 0;
}
