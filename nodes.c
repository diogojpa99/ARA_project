#include "nodes.h"
#include "calendar.h"
#include "readFile.h"

/** createNode: Creates a new node in the Nodes List **/
Nodes *createGraph(Nodes *listHead, int tail, int head, int type){ 

    Nodes *newNode = NULL;
    Adj *newAdj = NULL;
    
    
    if (searchNodesList(listHead, tail) == NULL){ //Deve ser tail ou head ? Perguntar ao prof
        newNode = createNode(listHead, tail);
        listHead = insertNode(listHead, newNode, newNode->id);    
    }
    else{
        newNode = searchNodesList(listHead, tail);
    }

    newAdj = createAdj(newNode->adjHead, tail, head, type);
    newNode->adjHead = insertAdj(newNode->adjHead, newAdj);

    return listHead;
}

/** Creation of a new node (list of Nodes) **/
Nodes *createNode(Nodes *listHead, int tail){ 

    Nodes *newNode = NULL;
    
    if((newNode = (Nodes*) calloc(1, sizeof(Nodes))) == NULL){   //Creation of a New Node 
        printf("Memory is full. Couldn't register request.\n");
	    return listHead;
    } 
    
    newNode->id = tail;
    newNode->next = NULL;
    newNode->adjHead = NULL;
    newNode->destHead = NULL;

    return newNode;
}

/** Creates a new adjacent nodes referent to the Node in the Nodes List **/
Adj *createAdj(Adj *listHead, int tail, int head, int type){ 

    Adj *newAdj;

    if((newAdj = (Adj*) calloc(1, sizeof(Adj))) == NULL){ //Create a new Adjacent
		return listHead;
    }

    newAdj->neighbor = tail;
    newAdj->id = head;
    newAdj->type = type;
    newAdj->An = 0;
    newAdj->next = NULL;

    return newAdj;
}

/** Insert the new Adj int the end of the respective Adj List **/
Adj *insertAdj(Adj *listHead, Adj *newAdj){ 

    Adj *auxH, *auxT;

    if(listHead == NULL){
        listHead = newAdj;
    }else{
        auxH = listHead;
        auxT = listHead->next;
        while(auxT != NULL){
            auxH = auxT;
            auxT = auxT->next;
        }
        auxH->next = newAdj;
        newAdj->next = NULL;
    }
    return listHead;
}

Nodes *insertNode(Nodes *listHead, Nodes *newNode, int id){ //Insert the new Node in the end of the Nodes List

    Nodes *auxT;

    /** Inserting the new node in the end of the nodes list and returning the list head**/
    if(listHead == NULL){
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
Nodes *searchNodesList(Nodes *list_Head, int id){ 

    Nodes *auxT;

    if(list_Head == NULL){
        return NULL;
    }else{     
        auxT = list_Head;
        if(auxT->id == id)
            return auxT;
        while(auxT->next !=NULL){
            auxT = auxT->next;
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

void updateDestToNode(Nodes *dest_node, int *message)
{
    DestNode *auxH, *auxT  = NULL;

    //Procurar na lista destinos do nó a quem se destina a mensagem o nó de onde vem a mensagem
    auxH = searchDestiny(dest_node->destHead, message[0]);

    if(auxH == NULL){
        //criar o destino para o nó adjacente
        dest_node->destHead = createDestiny(dest_node->destHead, message[0], message[0], 1);
    }
    /*Temos que criar eventos a dizer que o no que recebeu a sms consegue chegar ao seu adjacente*/



    auxH = searchDestiny(dest_node->destHead, message[1]);
    if(auxH == NULL){
        //criar o destino para o nó adjacente
        dest_node->destHead = createDestiny(dest_node->destHead, message[0], message[1], message[2]);
    }else{
        //O destino já existe e temos de verificar se vale apena mudar caso a estimativa melhore
        if(auxH->cost > message[2]){
            auxH->cost = message[2];
            auxH->neighbour_id = message[1];
        }
    }
    
}

DestNode *searchDestiny(DestNode *dest_head, int dest_id)
{
    DestNode *auxT;

    if(dest_head == NULL){
        return NULL;
    }else{     
        auxT = dest_head;
        if(auxT->dest_id == dest_id)
            return auxT;
        while(auxT->next_dest != NULL){
            auxT = auxT->next_dest;
            if( auxT->dest_id == dest_id ){
                
                return auxT;
            }
        }
    }
    //Se não se tiver encontrado o destino 
    return NULL;
}

DestNode *createDestiny(DestNode *dest_head, int neigbour_id, int dest_id, int cost)
{
    DestNode *auxH, *auxT = NULL;

    //primeiro destino
    //Se é o primeiro destino então criamos logo dois destinos:
    // - destino para o nó adjacente de onde recebemos a mensagem
    // - destino para o nó anunciado na mensagem
    //
    auxH = (DestNode*) calloc(1, sizeof(DestNode));
        if(auxH == NULL){
            printf("Error: Could not add destiny");
            return NULL;
        }
    auxH->neighbour_id = neigbour_id;
    auxH->dest_id = dest_id;
    auxH->cost = 1;
    auxH->next_dest = NULL;

    if(dest_head == NULL){
        //se for o primeiro destino a ser criado
        dest_head = auxH;
        dest_head->next_dest = NULL;
    }else{
        //Se já existirem destinos inserimos na cabeça da lista
        auxT = auxH;
        auxH = dest_head->next_dest;
        dest_head = auxT;
        dest_head->next_dest = auxH;
    }
    return dest_head;
}