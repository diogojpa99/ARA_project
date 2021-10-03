#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementar o grafo pelo método de lista de adjacências

typedef struct _Adj{
    char *id, *neighbor; //What's the commercial relation between me and my "list head"
    int type, cost;   //what's the cost from the link between me and my "list head"
    struct _Adj *next;
} Adj;

typedef struct _Nodes{
    char *id;
    Adj *adjHead;
    struct _Nodes *next;
} Nodes;

Nodes *createNode(Nodes *listHead, char *tail, char *head, int type);

Adj *createAdj(Adj *listHead, char *tail, char *head, int type);

Adj *insertAdj(Adj *listHead, Adj *newAdj);

Nodes *insertNode(Nodes *listHead, Nodes *newNode);

Nodes *searchNodesList(Nodes *listHead, char *id);

void Print_List_of_Adjacencies(Nodes *listHead);

void Print_List(Nodes *listHead);

int main()
{
    FILE *fp;
    char tail[12], head[12];
    int type;
    Nodes *NodesHead = NULL, *newNode;

    fp = fopen("grafo1.txt","r");

    if(fp==NULL){
        perror("Error opening the text file");
        return(-1);
    }

    while( fscanf(fp, "%s %s %d\n", tail, head, &type) != EOF ){
        //printf("%s %s %d\n", tail, head, type);
        NodesHead = createNode(NodesHead, tail, head, type);
    }

    Print_List(NodesHead);
    //xPrint_List_of_Adjacencies(NodesHead);

    fclose(fp);
    return 0;
}

/** createNode: Creates a new node in the Nodes List **/
Nodes *createNode(Nodes *listHead, char *tail, char *head, int type){ 

    Nodes *newNode=NULL;
    Adj *newAdj=NULL;

    if (searchNodesList( listHead, tail) == NULL){ //Deve ser tail ou head ? Perguntar ao prof
        if((newNode = (Nodes*) malloc(sizeof(Nodes))) == NULL){   /** Creation of a New Node **/
            printf("Memory is full. Couldn't register request.\n");
		    return listHead;
        }
        newNode->id=tail;
        newNode->next=NULL;
        newNode->adjHead=NULL;
    } 
    else{
        newNode = searchNodesList(listHead, tail);        
    }
    newAdj= createAdj(newNode->adjHead, tail, head, type);
    newNode->adjHead=insertAdj(newNode->adjHead, newAdj);
    listHead=insertNode(listHead, newNode);

    printf("New node: id=%s |-> Adj: id=%s| neighbor=%s| type=%d\n",newNode->id,newAdj->id, newAdj->neighbor, newAdj->type );

    return listHead;
}

/** Creates a new adjacent nodes referent to the Node in the Nodes List **/
Adj *createAdj(Adj *listHead, char *tail, char *head, int type){ //Pensar sobre qual é que vai ser a listHead das Adj

    Adj *newAdj;

    /** Creation of a New Node **/
    if((newAdj = (Adj*) malloc(sizeof(Adj))) == NULL){
        printf("Memory is full. Couldn't register request.\n");
		return listHead;
    }

    newAdj->neighbor=tail;
    newAdj->id=head;
    if( type==2){
        newAdj->type=2;
    } 
    else if( type==1){
        newAdj->type=3;
    } 
    else if( type==3){
        newAdj->type=1;
    }

    return newAdj;
}

/** Insert the new Adj int the end of the respective Adj List **/
Adj *insertAdj(Adj *listHead, Adj *newAdj){ 

    Adj *auxH, *auxT;

    if(listHead == NULL){
        listHead=newAdj;
        listHead->next=NULL;
    }else{
        auxH=listHead;
        auxT=listHead->next;
        while(auxT !=NULL){
            auxH=auxT;
            auxT=auxT->next;
        }
        auxH->next=newAdj;
        newAdj->next=NULL;
    }
    return listHead;
}

Nodes *insertNode(Nodes *listHead, Nodes *newNode){ //Insert the new Node in the end of the Nodes List

    Nodes *auxH, *auxT;

    /** Inserting the new node in the end of the nodes list and returning the list head**/
    if(listHead==NULL){
        listHead=newNode;
        listHead->next = NULL;
    }else{
        auxH=listHead;
        auxT=listHead->next;
        while(auxT != NULL){
            auxH=auxT;
            auxT=auxT->next;
            if(strcmp(auxH->id,"17228")==0)
                printf("auxT=%s ",auxT->id);
        }
        auxH->next=newNode;
        newNode->next=NULL;
    }
    Print_List(listHead);
    return listHead;
}

/*  *
* searchNodeList is a function that returns an 1 or a 0. The fuction searches in the Node List for the Node with a certain id.      *
* If there is a match the function retunrs 1, theis means that the Node is already in the Nodes List, so we don´t create the        * 
* same Nome two times. If there is no match, the fuction returns zero and we can create the new node and add him to the Nodes List. *
*   */
Nodes *searchNodesList(Nodes *listHead, char *id){ 

    Nodes *auxH, *auxT;

    auxH=listHead;

    if(auxH == NULL){
        return NULL;
    }else{     
        auxT=listHead->next;
        while(auxT !=NULL){
            if( strcmp(auxH->id,id) == 0 ){
                return auxH;
            }
            else{
                return NULL;
            }
            auxH=auxT;
            auxT=auxT->next;
        }
    }
    return NULL;
}

void Print_List_of_Adjacencies(Nodes *listHead){
    
    Nodes *nodes_auxH, *nodes_auxT;
    Adj *adj_auxH, *adj_auxT;

    if(listHead==NULL){
        return;
    }else{
        nodes_auxH=listHead;
        nodes_auxT=listHead->next;
        while(nodes_auxT != NULL){
            printf("[%s]->", nodes_auxH->id);
            adj_auxH=nodes_auxH->adjHead;
            adj_auxT=nodes_auxH->adjHead->next;
            while( adj_auxT != NULL){
                printf("[id:%s|type:%d|neighbor:%s]->", adj_auxH->id, adj_auxH->type, adj_auxH->neighbor);
                adj_auxH=adj_auxT;
                adj_auxT=adj_auxT->next;
            }
            printf("NULL\n");
            nodes_auxH=nodes_auxT;
            nodes_auxT=nodes_auxT->next;
        }
        printf("NULL\n");
    }

    return;
}

void Print_List(Nodes *listHead){
    
    Nodes *auxH, *auxT;
    
    if(listHead==NULL){
        return;
    }else{
        auxH=listHead;
        auxT=listHead->next;
        while( auxT != NULL){
            printf("id:%s\n",auxH->id);
            auxH=auxT;
            auxT=auxT->next;
        }
    }
        printf("NULL\n");

    return;
}