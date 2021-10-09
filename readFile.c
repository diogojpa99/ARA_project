#include <stdio.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_ID 65535

// Implementar o grafo pelo método de lista de adjacências

typedef struct _Adj{
    int id, neighbor, type; //What's the commercial relation between me and my "list head"  and what's the cost from the link between me and my "list head"
    char message[6]; 
    struct _Adj *next;
} Adj;

typedef struct _Nodes{
    int id;
    char message[6]; 
    Adj *adjHead;
    struct _Nodes *next;
} Nodes;

//Estrutura para o calendário - lista simplesmente ligada
typedef struct _Event{
    int time, in_node, out_node, type; 
    struct _Event *next;
} Event;


Nodes *createGraph(Nodes *listHead, int tail, int head, int type);

Nodes *createNode(Nodes *listHead, int tail);

Adj *createAdj(Adj *listHead, int tail, int head, int type);

Adj *insertAdj(Adj *listHead, Adj *newAdj);

Nodes *insertNode(Nodes *listHead, Nodes *newNode, int id);

Nodes *searchNodesList(Nodes *listHead, int id);

void Print_List_of_Adjacencies(Nodes *listHead);

int walk_trough_nodesList(Nodes *listHead);

Nodes *wakeNode(Nodes *listHead, int awake_id);

Event *searchNeighbors(Event *eventHead, Nodes *node);

Event *createEvent(Event *listHead, Nodes *node, Adj *adj);

Event *insertEvent(Event *listHead, Event *newEvent);

void printEvents(Event *listHead);

int main()
{
    FILE *fp;
    int tail, head, type, node_id, flag=0, n_nodes, awaken_node;
    Nodes *NodesHead = NULL, *newNode=NULL, *node=NULL;
    Event *eventHead=NULL;

    fp = fopen("grafo1.txt","r");
    srand(time(0));

    if(fp==NULL){
        perror("Error opening the text file");
        return(-1);
    }

    while( fscanf(fp, "%d %d %d\n", &tail, &head, &type) != EOF ){
        NodesHead = createGraph(NodesHead, tail, head, type);
    }
    Print_List_of_Adjacencies(NodesHead);
    
    /******************************************** Simulation ***********************************************/

    printf("The simulation has started!\n");
    n_nodes=walk_trough_nodesList(NodesHead);
    awaken_node=rand()%n_nodes;
    node = wakeNode(NodesHead,awaken_node); //Awake random Node in the Nodes List
    if(node==NULL)
        printf("UPS!\n");
    else
        printf("Awaken Node id(rand):%d(%d)\n",node->id,awaken_node);

    eventHead=searchNeighbors(eventHead, node);
    printEvents(eventHead);

    /**************************************** Interactive Mode ********************************************/
    /**printf("Insert the id of the node you want to wake: "); fflush(stdout);//prompt
    while(flag==0){ //Problemas: Loop em "abc" e ignora o "a" em "123a"
		if( (scanf("%d", &node_id) != 1) && (node_id<=1 || node_id>=MAX_ID)){
			printf("You have to insert an integer from 1 to %d\n", MAX_ID);
			printf("Insert the id of the node you want to wake: "); fflush(stdout);//promp
		}else{
			flag=1;
		}
	}
	printf("id:%d\n", node_id); fflush(stdout);//prompt
    **********************************************************************************************************/

    fclose(fp);
    return 0;
}

/** createNode: Creates a new node in the Nodes List **/
Nodes *createGraph(Nodes *listHead, int tail, int head, int type){ 

    Nodes *newNode=NULL;
    Adj *newAdj=NULL;
    
    if (searchNodesList(listHead, tail) == NULL){ //Deve ser tail ou head ? Perguntar ao prof
        newNode=createNode(listHead,tail);
        listHead=insertNode(listHead, newNode, newNode->id);    
    }
    else{
        newNode = searchNodesList(listHead, tail);
    }

    newAdj= createAdj(newNode->adjHead, tail, head, type);
    newNode->adjHead=insertAdj(newNode->adjHead, newAdj);

    return listHead;
}

/** Creation of a new node (list of Nodes) **/
Nodes *createNode(Nodes *listHead, int tail){ 

    Nodes *newNode=NULL;
    
    if((newNode = (Nodes*) malloc(sizeof(Nodes))) == NULL){   //Creation of a New Node 
        printf("Memory is full. Couldn't register request.\n");
	    return listHead;
    } 
    
    newNode->id=tail;
    newNode->next=NULL;
    newNode->adjHead=NULL;

    return newNode;
}

/** Creates a new adjacent nodes referent to the Node in the Nodes List **/
Adj *createAdj(Adj *listHead, int tail, int head, int type){ 

    Adj *newAdj;

    if((newAdj = (Adj*) malloc(sizeof(Adj))) == NULL){ //Create a new Adjacent
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

int walk_trough_nodesList(Nodes *listHead){
    
    Nodes *auxH, *auxT;
    int n_nodes=0;
    
    if(listHead==NULL){
        return n_nodes;
    }else{
        n_nodes++;
        auxH=listHead;
        //printf("id:%d\n",auxH->id);
        auxT=listHead->next;
        while( auxT != NULL){
            n_nodes++;
            auxH=auxT;
            auxT=auxT->next;
            //printf("id:%d\n",auxH->id);
        }
        //printf("NULL\n");
    }

    return n_nodes;
} 

//Função que "Acorda" um nó do grafo
Nodes *wakeNode(Nodes *listHead, int awake_id){

    Nodes *auxT;
    int i=0;

    if(listHead == NULL){
        return NULL;
    }else{     
        auxT=listHead;
        if(awake_id == 0)
            return auxT;
        i++;
        while(auxT->next !=NULL){
            auxT=auxT->next;
            if( i == awake_id )
                return auxT;
            i++;
        }
    }
    return NULL;
}

Event *searchNeighbors(Event *eventHead, Nodes *node){

    Adj *auxT;

    if(node==NULL){
        return eventHead;
    }else{
        auxT=node->adjHead;
            eventHead=createEvent(eventHead, node, auxT);
        while(auxT->next != NULL){
            auxT=auxT->next;
            eventHead=createEvent(eventHead, node, auxT);
        }
    }
    return eventHead;
}

//Funcao que cria um novo evento para poder ser inserido no calendario
Event *createEvent(Event *listHead, Nodes *node, Adj *adj) //Também é necessário a cabeça da lista de eventos
{
    Event *newEvent=NULL;
   
    if((newEvent = (Event*) malloc(sizeof(Event))) == NULL){   /** Creation of a New Event **/
        printf("Memory is full. Couldn't register request.\n");
		return listHead;
    } 
    newEvent->time=1+rand()%3;
    newEvent->out_node=node->id;
    newEvent->in_node=adj->id;
    newEvent->type=adj->type;
    printf("time=%d | out_node=%d | in_node=%d | type=%d\n",newEvent->time,newEvent->out_node,newEvent->in_node,newEvent->type);

    return listHead=insertEvent(listHead, newEvent);
}

Event *insertEvent(Event *listHead, Event *newEvent){

    Event *auxT;

    if(listHead==NULL){
        return newEvent;
    }else{
        if(newEvent->time < listHead->time){
            newEvent->next=listHead;
            listHead=newEvent;
        }
        else{
            auxT=listHead;
            while(auxT->next!=NULL){
                auxT=auxT->next;
                if(newEvent->time < auxT->time){
                    newEvent->next=auxT;
                    auxT=newEvent;
                    return listHead;
                }
            }
            auxT->next=newEvent;
            newEvent->next=NULL;
        }
    }

    return listHead;
}

void printEvents(Event *listHead){
    
    Event *auxH, *auxT;
    
    if(listHead==NULL){
        return;
    }else{
        auxH=listHead;
        printf("[time=%d|%d->%d|Type:%d]->",auxH->time,auxH->out_node,auxH->in_node,auxH->type); fflush(stdout);//prompt
        auxT=listHead->next;
        while( auxT != NULL){
            auxH=auxT;
            auxT=auxT->next;
            printf("[time=%d|%d->%d|Type:%d]->",auxH->time,auxH->out_node,auxH->in_node,auxH->type); fflush(stdout);//prompt
        }
        printf("NULL\n");
    }

    return;
} 