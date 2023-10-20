#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>
#include"alloc.h"
#include"miniblock.h"
#include"block.h"


void ALLOC_ARENA(FILE *pf, uint64_t* memory)
{
    fscanf(pf,"%"SCNu64,memory);

}
void ALLOC_BLOCK(FILE* pf,FILE* gp,struct Block** Node,uint64_t* occupied_memory,int* number_blocks,int* number_miniblocks)
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

    typedef struct Miniblock Miniblock;

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
void Free(struct Block** Node)
{
    typedef struct Block Block;
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
void ReArrangeBlocks(struct Block** Node,int *number_blocks)
{
        typedef struct Miniblock Miniblock;
    typedef struct Block Block;

    Miniblock* Node2,* Node3,*MiniNode;
    MiniNode = (Miniblock*)((*Node)->miniblock_list);
    //copy = MiniNode;

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
