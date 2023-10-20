#include"alloc.h"
#include"miniblock.h"
#include"block.h"
#include"traverse.h"
#include"permission.h"
#include<stdio.h>
#include<stdint.h>
#include<stdio.h>
#include <inttypes.h>
#include<stddef.h>
#include<stdlib.h>

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
void PUT(FILE* fp,FILE* gp,struct Miniblock** MiniNode,int size)
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
void SEE(FILE* gp,struct Miniblock** MiniNode,int size)
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
