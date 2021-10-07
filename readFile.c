#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ID 65535
// Implementar o grafo pelo método de lista de adjacências

typedef struct _Adj{
    int id, neighbor, type, cost; //What's the commercial relation between me and my "list head"  and what's the cost from the link between me and my "list head"
    char message[128]; //new
    struct _Adj *next;
} Adj;

typedef struct _Nodes{
    int id;
    char message[128]; //new
    Adj *adjHead;
    struct _Nodes *next;
} Nodes;

//Estrutura para o calendário - lista simplesmente ligada
typedef struct _Event{
    float time;
    int in_node;
    int out_node; 

} Event;


Nodes *createNode(Nodes *listHead, int tail, int head, int type);

Adj *createAdj(Adj *listHead, int tail, int head, int type);

Adj *insertAdj(Adj *listHead, Adj *newAdj);

Nodes *insertNode(Nodes *listHead, Nodes *newNode, int id);

Nodes *searchNodesList(Nodes *listHead, int id);

void Print_List_of_Adjacencies(Nodes *listHead);

void Print_List(Nodes *listHead);


void createEventNode(Event *new_node);

int main()
{
    FILE *fp;
    int tail, head, type, node_id, flag=0;
    Nodes *NodesHead = NULL, *newNode=NULL;

    fp = fopen("grafo1.txt","r");

    if(fp==NULL){
        perror("Error opening the text file");
        return(-1);
    }

    while( fscanf(fp, "%d %d %d\n", &tail, &head, &type) != EOF ){
        NodesHead = createNode(NodesHead, tail, head, type);
    }
    
    
    printf("Insert the id of the node you want to wake: "); fflush(stdout);//prompt
    
    while(flag==0){ //Problemas: Loop em "abc" e ignora o "a" em "123a"
		if( (scanf("%d", &node_id) != 1) && (node_id<=1 || node_id>=MAX_ID)){
			printf("You have to insert an integer from 1 to %d\n", MAX_ID);
			printf("Insert the id of the node you want to wake: "); fflush(stdout);//promp
		}else{
			flag=1;
		}
	}
	/*while((scanf("%d", &node_id) == 1) && (node_id>=1 && node_id<=MAX_ID)){
			printf("You have to insert an integer from 1 to %d\n", MAX_ID);
			printf("Insert the id of the node you want to wake: "); fflush(stdout);//promp
	}*/
	
	printf("id:%d\n", node_id); fflush(stdout);//prompt
    //Print_List(NodesHead);
    Print_List_of_Adjacencies(NodesHead);

    fclose(fp);
    return 0;
}

/** createNode: Creates a new node in the Nodes List **/
Nodes *createNode(Nodes *listHead, int tail, int head, int type){ 

    Nodes *newNode=NULL;
    Adj *newAdj=NULL;
    
    if (searchNodesList(listHead, tail) == NULL){ //Deve ser tail ou head ? Perguntar ao prof
        if((newNode = (Nodes*) malloc(sizeof(Nodes))) == NULL){   /** Creation of a New Node **/
            printf("Memory is full. Couldn't register request.\n");
		    return listHead;
        } 
        newNode->id=tail;
        newNode->next=NULL;
        newNode->adjHead=NULL;
        listHead=insertNode(listHead, newNode, newNode->id);    
    }
    else{
        newNode = searchNodesList(listHead, tail);
    }

    newAdj= createAdj(newNode->adjHead, tail, head, type);
    newNode->adjHead=insertAdj(newNode->adjHead, newAdj);

    return listHead;
}

/** Creates a new adjacent nodes referent to the Node in the Nodes List **/
Adj *createAdj(Adj *listHead, int tail, int head, int type){ 

    Adj *newAdj;

    /** Creation of a New Node **/
    if((newAdj = (Adj*) malloc(sizeof(Adj))) == NULL){
		return listHead;
    }

    newAdj->neighbor=tail;
    newAdj->id=head;
    newAdj->type=type;

    return newAdj;
}

/** Insert the new Adj int the end of the respective Adj List **/
Adj *insertAdj(Adj *listHead, Adj *newAdj){ 

    Adj *auxH, *auxT;

    if(listHead == NULL){
        listHead=newAdj;
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

Nodes *insertNode(Nodes *listHead, Nodes *newNode, int id){ //Insert the new Node in the end of the Nodes List

    Nodes *auxT;

    /** Inserting the new node in the end of the nodes list and returning the list head**/
    if(listHead==NULL){
        listHead=newNode;
    }else{
        auxT=listHead;
        while(auxT->next != NULL){
            if( auxT->id == id){
                return listHead;
            }
            auxT=auxT->next;
        }
        auxT->next=newNode;
        newNode->next=NULL;
    }
    return listHead;
}

/*  *
* searchNodeList is a function that returns an 1 or a 0. The fuction searches in the Node List for the Node with a certain id.      *
* If there is a match the function retunrs 1, theis means that the Node is already in the Nodes List, so we don´t create the        * 
* same Nome two times. If there is no match, the fuction returns zero and we can create the new node and add him to the Nodes List. *
*   */
Nodes *searchNodesList(Nodes *listHead, int id){ 

    Nodes *auxT;

    if(listHead == NULL){
        return NULL;
    }else{     
        auxT=listHead;
        if(auxT->id == id)
            return auxT;
        while(auxT->next !=NULL){
            auxT=auxT->next;
            if( auxT->id == id ){
                //printf("searchNodesList: auxT encontrado: %d\n", auxT->id); // DÚVIDA: A imprimir duas vezes, porquê ?
                return auxT;
            }
        }
    }
    return NULL;
}

void Print_List_of_Adjacencies(Nodes *listHead){
    
    Nodes *nodes_auxT;
    Adj *adj_auxT;

    if(listHead==NULL){
        return;
    }else{
        for(nodes_auxT = listHead; nodes_auxT != NULL; nodes_auxT = nodes_auxT->next) {
            printf("[%d]->", nodes_auxT->id);   fflush(stdout);
            for(adj_auxT = nodes_auxT->adjHead; adj_auxT != NULL; adj_auxT = adj_auxT->next) {
                printf("[id:%d|type:%d]->", adj_auxT->id, adj_auxT->type);  fflush(stdout);
            }
            printf("NULL\n");
        }
    }

    return;
}

void Print_List(Nodes *listHead){
    
    Nodes *auxH, *auxT;
    
    if(listHead==NULL){
        printf("ups!\n");
        return;
    }else{
        auxH=listHead;
        printf("id:%d\n",auxH->id);
        auxT=listHead->next;
        while( auxT != NULL){
            auxH=auxT;
            auxT=auxT->next;
            printf("id:%d\n",auxH->id);
        }
        printf("NULL\n");
    }

    return;
} 



//Funcao que cria um novo evento para poder ser inserido no calendario
void createEventNode(Event *new_node)
{
    
}
