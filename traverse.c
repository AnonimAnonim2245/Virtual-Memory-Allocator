#include<stdio.h>
#include"alloc.h"
#include"miniblock.h"
#include"block.h"
#include<stddef.h>
#include<stdlib.h>
void Traverse(struct Miniblock** MiniNode)
{
    while((*MiniNode)->urmator!=NULL)
    {
        (*MiniNode)=(*MiniNode)->urmator;
    }


}

void Traverse2(struct Miniblock** MiniNode,int *sum)
{
    while((*MiniNode)->urmator!=NULL)
    {
        *sum+=(*MiniNode)->size;
        (*MiniNode)=(*MiniNode)->urmator;
    }

}
void Traverse_rev(struct Miniblock** MiniNode)
{
    while((*MiniNode)->anterior!=NULL)
    {
        (*MiniNode)=(*MiniNode)->anterior;
    }
}
void Traverse_rev2(struct Block** Node)
{
    while((*Node)->anterior!=NULL)
    {
        //Miniblock* MiniNode=(Miniblock*)((*Node)->miniblock_list);
            //printf("%"PRIu64" ",(MiniNode)->perm);

        (*Node)=(*Node)->anterior;
    }
}

