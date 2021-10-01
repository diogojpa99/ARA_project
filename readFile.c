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
        NodesHead = createNode(NodesHead, tail, head, type);


    }

    fclose(fp);
    return 0;
}


Nodes *createNode(Nodes *listHead, char *tail, char *head, char type){ 

    Nodes *newNode, *auxH, *auxT;

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

/*  *
* searchNodeList is a function that returns an 1 or a 0. The fuction searches in the Node List for the Node with a certain id.      *
* If there is a match the function retunrs 1, theis means that the Node is already in the Nodes List, so we don´t create the        * 
* same Nome two times. If there is no match, the fuction returns zero and we can create the new node and add him to the Nodes List. *
*   */
int searchNodesList(Nodes *listHead, int id){ 

    Nodes *auxH, *auxT;

    if(listHead == NULL){
        return 0;
    }else{
        auxH=listHead;
        auxT=listHead->next;
        while(auxT !=NULL){
            auxH=auxT;
            auxT=auxT->next;
            if(auxH->id==id){
                return 1;
            }
        }
    }
    return 0;
}