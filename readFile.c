#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementar o grafo pelo método de lista de adjacências

typedef struct _Nodes{
    char id;
    Adj *nextAdj;
    struct _Nodes *next;
} Nodes;

typedef struct _Adj{
    char id, type; //What's the commercial relation between me and my "list head"
    int cost;   //what's the cost from the link between me and my "list head"
    struct _Adj *next;
} Adj;

int main()
{
    FILE *fp;
    char tail[5], head[5], type;
    Nodes *NodesHead = NULL, *newNode;
    Adj *newAdj;

    fp = fopen("grafo1.txt","r");

    if(fp==NULL){
        perror("Error opening the text file");
        return(-1);
    }

    while( fscanf(fp, "%s %s %c\n", tail, head, &type) != EOF ){
        NodesHead = creatNode(NodesHead, tail, head, type);


    }

    fclose(fp);
    return 0;
}


Nodes *newNode(Nodes *listHead, char *tail, char *head, char type){ 

    Nodes *newNode, *auxH, *auxT;
    Edges *newlink;

    /** Creation of a New Node **/

    if(newNode = (Nodes*) malloc(sizeof(Nodes)) == NULL){
        printf("Memory is full. Couldn't register request.\n");
		return listHead;
    }
    
    if(newlink = (Edges*) malloc(sizeof(Edges)) == NULL){
        printf("Memory is full. Couldn't register request.\n");
		return listHead; //what do we retunr ??
    }

        
    newNode->id=tail;
    newNode->next=NULL;
    newlink->tail= tail;
    newlink->head= head;
    newlink->tpe= type;
    newlink->cost=1; //Ver se será preciso definir isto

    /** Inserting the new node in the end of the nodes list and returning the list head**/

    if(listHead == NULL){
        listHead=newNode;
    }else{
        auxH=listHead;
        auxT=listHead->next;
        while(auxT !=NULL){
            auxH=auxT;
            auxT=auxT->next;
        }
        auxT->next=newNode;
    }

    return listHead;
}

Nodes *insertNode(Nodes *listHead, Nodes *newNode){ //Insert the new Node in the end of the Nodes List

    Nodes *auxH, *auxT;


    /** Inserting the new node in the end of the nodes list and returning the list head**/

    if(listHead == NULL){
        listHead=newNode;
    }else{
        auxH=listHead;
        auxT=listHead->next;
        while(auxT !=NULL){
            auxH=auxT;
            auxT=auxT->next;
        }
        auxT->next=newNode;
    }

    return listHead;
}