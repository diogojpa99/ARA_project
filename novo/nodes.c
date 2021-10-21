#include "nodes.h"
#include "calendar.h"
#include "readFile.h"
#include "simulation.h"

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

    //newNode->destHead = createDestiny(newNode->destHead, newNode->id, newNode->id, 0, 0);

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

void Print_List_of_Nodes(Nodes *listHead){
    
    Nodes *nodes_auxT;

    if(listHead==NULL){
        return;
    }else{
        for(nodes_auxT = listHead; nodes_auxT != NULL; nodes_auxT = nodes_auxT->next) {
            printf("\n\t%d", nodes_auxT->id);   fflush(stdout);
        }
    }

    return;
}

void Print_List_of_Adjacencies(Nodes *listHead){
    
    Nodes *nodes_auxT;
    Adj *adj_auxT;

    if(listHead==NULL){
        return;
    }else{
        for(nodes_auxT = listHead; nodes_auxT != NULL; nodes_auxT = nodes_auxT->next) {
            printf("\n[%d]->", nodes_auxT->id);   fflush(stdout);
            for(adj_auxT = nodes_auxT->adjHead; adj_auxT != NULL; adj_auxT = adj_auxT->next) {
                printf("[id:%d|type:%d]->", adj_auxT->id, adj_auxT->type);  fflush(stdout);
            }
            printf("NULL\n");
        }
    }

    return;
}


/*
updateDestToNode: Se a tabela de encaminhamento de um dado nó for alterada (retorna-se 1), então esse nó tem que anunciar isso
aos seus vizinhos, logo é necessário criar novos eventos. Caso a tabela de encaminhamento não altere (retorna-se 0), o nó não
anuncia nada.
*/
DestNode *updateDestToNode(Nodes *process_node, int *message, int type)
{
    DestNode *current_dest = NULL;
    Neighbours *chosen_neighbour = NULL;

    current_dest = searchDestiny(process_node->destHead, message[1]);

    if(current_dest == NULL){
        //criar o destino para o nó adjacente e inserir no topo
        process_node->destHead = createDestiny(process_node->destHead, message[0], message[1], message[2], type);

        //Criar o nó vizinho a partir do qual chegamos ao destino, para o inserir na lista de nós desse destino
        chosen_neighbour = createNeighbourToDestiny(message, type);
        //Inserir ordenadamente o novo vizinho na lista de vizinhos que conseguem chegar ao destino
        process_node->destHead->neighbours_head = insertNeighbourtOrdered(process_node->destHead->neighbours_head, chosen_neighbour);  
        return process_node->destHead;
    }else{
        //O destino já existe e temos de verificar se vale apena mudar caso a estimativa melhore
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ATENÇÃO ÀS RELAÇÕES COMERCIAIS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        //encontrar o vizinho pelo qual conseguimos chegar a um dado destino
        chosen_neighbour = searchForNeighbourToDestiny(current_dest->neighbours_head, message[0]);
        if(chosen_neighbour == NULL){//se não o encontrámos temos que criar
            chosen_neighbour = createNeighbourToDestiny(message, type);
            current_dest->neighbours_head = insertNeighbourtOrdered(current_dest->neighbours_head, chosen_neighbour);//inserimos ordenadamente para que na cabeça da lista de vizinhos que chegam a um dado destino ficar sempre o que tem melhor custo
        }else{//se o encontrámos temos que o atualizar com o novo custo e depois reordenar a lista de vizinhos que chegam a um dado destino
            chosen_neighbour->neighbour_estim_cost = message[2] + 1;
            //printf("NEIGHBOURS HEAD: %d", current_dest->neighbours_head->neighbour_id);
            current_dest->neighbours_head = orderNeighboursToDestinyAscendent(current_dest->neighbours_head);
            
        }

        //print list of neighbours to that destiny
        printf("\n\t\tPRINTING DESTINIES OF NODE %d\n", process_node->id);
        printDestiny(process_node->destHead);

        //Atualizar a informação que temos para chegar a esse destino
        //updateDestiny(current_dest, message, type); //fazer esta função

        if( type < current_dest->type){ //1<2<3
            printf("\nAlteracao pela relacao comercial\n");
            current_dest->chosen_neighbour_id = message[0];
            current_dest->type = type;
            current_dest->cost = message[2] + 1;
            return current_dest;
        }else if( type == current_dest->type){ //Se a relação comercial for a mesma então vemos pelo custo
            printf("\nAlteracao pelo custo\n");
            if(message[2] + 1 < current_dest->cost){
                current_dest->chosen_neighbour_id = message[0];
                current_dest->cost = message[2] + 1;
                return current_dest;
            }else if(current_dest->chosen_neighbour_id == message[0]){
                printf("\nAlteracao forcada\n");
                current_dest->chosen_neighbour_id = message[0];
                current_dest->cost = message[2] + 1;
                return current_dest;
            }
        }
    } 

    return NULL;  //Se nada mudar, então não se anuncia nada
}

void printDestiny(DestNode *destiny_head)
{
    printf("\n\t\tPRINTING DESTINIES\n");
    DestNode *destiny_auxT;
    Neighbours *neighbour_auxT;

    if(destiny_head == NULL){
        return;
    }else{
        for(destiny_auxT = destiny_head; destiny_auxT != NULL; destiny_auxT = destiny_auxT->next_dest) {
            printf("\n[%d]->", destiny_auxT->dest_id);   fflush(stdout);
            for(neighbour_auxT = destiny_auxT->neighbours_head; neighbour_auxT != NULL; neighbour_auxT = neighbour_auxT->next_neighbour) {
                printf("[id:%d|type:%d|cost%d]->", neighbour_auxT->neighbour_id, neighbour_auxT->type, neighbour_auxT->neighbour_estim_cost);  fflush(stdout);
            }
            printf("NULL\n");
        }
    }
    return;
}

Neighbours *createNeighbourToDestiny(int *message, int type)
{
    Neighbours *aux = NULL;

    if((aux = (Neighbours*)calloc(1, sizeof(Neighbours))) == NULL){
        printf("Error: Could not create neighbour to destiny");
        return NULL;
    }
    aux->neighbour_id = message[0];
    aux->neighbour_estim_cost = message[2] + 1;
    aux->type = type;
    aux->next_neighbour = NULL;

    return aux;
}

Neighbours *insertNeighbourtOrdered(Neighbours *neighbours_head, Neighbours *neighbour_to_insert)
{
    Neighbours *auxH, *auxT;

    if(neighbours_head == NULL){
        return neighbour_to_insert;
    }else{
        if(neighbour_to_insert->neighbour_estim_cost < neighbours_head->neighbour_estim_cost){
            neighbour_to_insert->next_neighbour = neighbours_head;
            neighbours_head = neighbour_to_insert;
        }
        else{
            auxH = neighbours_head;
            auxT = neighbours_head->next_neighbour;
            while((auxT != NULL) && (neighbour_to_insert->neighbour_estim_cost >= auxT->neighbour_estim_cost)){
                auxH = auxT;
                auxT = auxT->next_neighbour;
            }
            neighbour_to_insert->next_neighbour = auxT;
            auxH->next_neighbour = neighbour_to_insert;
        }
    }
    printf("\n ----------- 269 -------------- \n");
    
    printf("\n ----------- 271 -------------- \n");
    return neighbours_head;
}

Neighbours *searchForNeighbourToDestiny(Neighbours *neighbours_head, int neighbour_id)
{
    Neighbours *auxT;

    if(neighbours_head == NULL){
        return NULL;
    }else{     
        auxT = neighbours_head;
        if(auxT->neighbour_id == neighbour_id)
            return auxT;
        while(auxT->next_neighbour != NULL){
            auxT = auxT->next_neighbour;
            if( auxT->neighbour_id == neighbour_id ) return auxT;
        }
    }
    //Se não se tiver encontrado o destino 
    return NULL;
}

Neighbours *orderNeighboursToDestinyAscendent(Neighbours *neighbours_head)
{
    Neighbours *right = NULL, *left = NULL, *head, aux_struct;
    head = &aux_struct;
    head->next_neighbour = neighbours_head;

    bool trocas = true;

    printf("\n%d\n", neighbours_head->neighbour_id); fflush(stdout);
    printf("\n%d\n", neighbours_head->neighbour_estim_cost); fflush(stdout);
    printf("\n%d\n", neighbours_head->type); fflush(stdout);

    if((neighbours_head->next_neighbour != NULL) && (neighbours_head != NULL)){
        while(trocas){

            trocas = false;
            right = head->next_neighbour;
            left = head;

            while(right->next_neighbour != NULL){

                if(right->neighbour_estim_cost < right->next_neighbour->neighbour_estim_cost){
                    trocas = true;
                    left->next_neighbour = switch_neighbours(right, right->next_neighbour);

                }

                left = right;

                if(right->next_neighbour != NULL){
                    right = right->next_neighbour;
                }
            }

        }
    }
    right = head->next_neighbour;
    return right;
}

Neighbours *switch_neighbours(Neighbours *left, Neighbours *right)
{
    left->next_neighbour = right->next_neighbour;
    right->next_neighbour = left;
    return right;
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
            if( auxT->dest_id == dest_id ) return auxT;
        }
    }
    //Se não se tiver encontrado o destino 
    return NULL;
}


/*
chosen_neighbour_id - vizinho por onde conseguimos chegar a um dado destino
dest_id - nó de destino
type ralaçao do nó atual para o nó com o chosen_neighbour_id
*/
DestNode *createDestiny(DestNode *dest_head, int neigbour_id, int dest_id, int cost, int type)
{
    DestNode *new_dest = NULL;

    //primeiro destino
    //Se é o primeiro destino então criamos logo dois destinos:
    // - destino para o nó adjacente de onde recebemos a mensagem
    // - destino para o nó anunciado na mensagem
    if((new_dest = (DestNode*) calloc(1, sizeof(DestNode))) == NULL){   
        printf("Error: Could not add destiny");
        return NULL;
    }
    new_dest->chosen_neighbour_id = neigbour_id;
    new_dest->dest_id = dest_id;
    new_dest->cost = cost + 1;
    new_dest->type = type;
    new_dest->next_dest = NULL;

    if(dest_head == NULL){
        //se for o primeiro destino a ser criado
        dest_head = new_dest;
        dest_head->next_dest = NULL;
    }else{
        //Se já existirem destinos inserimos na cabeça da lista
        new_dest->next_dest = dest_head;
        dest_head = new_dest;
    }

    return dest_head;
}

void Print_List_of_Destinations(Nodes *nodes_Head)
{
    Nodes *nodes_auxT;
    DestNode *dest_auxT;

    if(nodes_Head==NULL){
        return;
    }else{
        for(nodes_auxT = nodes_Head; nodes_auxT != NULL; nodes_auxT = nodes_auxT->next) {
            printf("\n[%d]->", nodes_auxT->id);   fflush(stdout);
            for(dest_auxT = nodes_auxT->destHead; dest_auxT != NULL; dest_auxT = dest_auxT->next_dest) {
                printf("[dest_id:%d|neihbour_id:%d|type:%d|cost:%d]->", dest_auxT->dest_id,dest_auxT->chosen_neighbour_id, dest_auxT->type,dest_auxT->cost);  fflush(stdout);
            }
            printf("NULL\n");
        }
    }

    return;
}

void freeGraphNodes(Nodes *nodes_head)
{
    Nodes *auxH = NULL; 
    Adj *aux_adj = NULL;
    DestNode *aux_dest = NULL;

    if(nodes_head == NULL)
    {
        return;
    }else{
        while (nodes_head != NULL)
        {
            auxH = nodes_head;
            nodes_head = nodes_head->next;

            while(auxH->adjHead != NULL)
            {
                aux_adj = auxH->adjHead;
                auxH->adjHead = auxH->adjHead->next; 
                free(aux_adj);
            }
            while(auxH->destHead != NULL)
            {
                aux_dest = auxH->destHead;
                auxH->destHead = auxH->destHead->next_dest; 
                free(aux_dest);
            }
        }
        free(auxH);

    }
}
