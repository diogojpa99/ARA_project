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

int walk_trough_nodesList(Nodes *listHead){
    
    Nodes *auxH, *auxT;
    int n_nodes = 0;
    
    if(listHead == NULL){
        return n_nodes;
    }else{
        n_nodes++;
        auxH = listHead;
        //printf("id:%d\n",auxH->id);
        auxT = listHead->next;
        while( auxT != NULL){
            n_nodes++;
            auxH = auxT;
            auxT = auxT->next;
            //printf("id:%d\n",auxH->id);
        }
        //printf("NULL\n");
    }

    return n_nodes;
} 

//Função que "Acorda" um nó do grafo
Nodes *wakeNode(Nodes *listHead, int awake_id){

    Nodes *auxT;
    int i = 0;

    if(listHead == NULL){
        return NULL;
    }else{     
        auxT = listHead;
        if(awake_id == 0)
            return auxT;
        i++;
        while(auxT->next != NULL){
            auxT = auxT->next;
            if( i == awake_id )
                return auxT;
            i++;
        }
    }
    return NULL;
}


void updateDestToNode(Nodes *dest_node, int *message)
{
    DestNode *auxH, *auxT  = NULL;

    //Procurar na lista destinos do nó a quem se destina a mensagem o nó de onde vem a mensagem
    auxH = searchDestiny(dest_node->destHead, message[0]);
    if(auxH == NULL){
        //criar o destino para o nó adjacente
        dest_node->destHead = createDestiny(dest_node->destHead, message[0], message[0], message[2]);
    }
    


    /*if(dest_node->destHead == NULL){
        //criar o destino para o nó adjacente que nos enviou a mensagem
        dest_node->destHead = (dest_node->destHead, message);

        //criar o destino que vem na mensagem
    }else{
        auxH = dest_node->destHead;
        //Processar a cabeça caso corresponda ao destino
        if(auxH->dest_id)

        auxT = auxH->next_dest;
        while (auxT != NULL)
        {
            auxH = auxT;
            
            auxT = auxT->next_dest;
        }
        
    }*/
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
    return NULL;
}

DestNode *createDestiny(DestNode *dest_head, int neigbour_id, int dest_id, int cost)
{
    DestNode *aux = NULL;

    aux = dest_head;

    //primeiro destino
    //Se é o primeiro destino então criamos logo dois destinos:
    // - destino para o nó adjacente de onde recebemos a mensagem
    // - destino para o nó anunciado na mensagem
    //
    if(aux == NULL){
        //Destino = nó adjacente
        aux = (DestNode*) calloc(1, sizeof(DestNode));
        if(aux == NULL){
            printf("Error: Could not add destiny");
            return;
        }
        aux->neighbour_id = neigbour_id;
        aux->dest_id = dest_id;
        aux->cost = 1;
    }

}