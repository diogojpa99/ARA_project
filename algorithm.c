#include "readFile.h"
#include "nodes.h"
#include "calendar.h"
#include "algorithm.h"

void Algorithm(Nodes *nodes_head) {

   Nodes *auxT = NULL; 
    
    if(nodes_head == NULL){
        return;
    }else{
        auxT = nodes_head;
        printf("\n ------------ Awaken node: %d -------------- \n", nodes_head->id);
        ReverseDijkstra( nodes_head, auxT);
        while( auxT->next != NULL){
            auxT = auxT->next;
            printf("\n ------------ Awaken node: %d -------------- \n", auxT->id);
            ReverseDijkstra( nodes_head, auxT);
        }
    }
    return;
}

void ReverseDijkstra(Nodes *nodes_head, Nodes *destiny_node){

    Queue *Q=NULL,*Q_1=NULL,*Q_2=NULL,*Q_3=NULL; //Vão ser heaps ou listas normais ??
    /* Q_1, Q_2, Q_3 representam as cabeças de cada uma das filas ordenadas */

    //Iniciar o Reverse Dijkstra
    nodes_head=initReverseDijktra(nodes_head, destiny_node);

    //Colocar o destino na pilha com custo zero 
    Q_1=InsertQ(destiny_node, Q_1);
    
    while ( (Q_1 != NULL) || (Q_2 != NULL) || (Q_3 != NULL)){

        if (Q_1 != NULL){
            Q=Q_1;
            Q_1=Q_1->next;
            //retirar o nó que está na cabeça da pilhaS
            //Ver os meus vizinhos (Mas atenção às restrições comerciais)
            //printf("Node that's being removed from the Q_1: Node_id:%d | Type:%d | Cost:%d \n",Q->node_id,Q->type,Q->cost);
            //Enquanto a lista de adjacências não estiver vazia
            //Relaxation of the link uv
            //Ver os meus vizinhos (Mas atenção às restrições comerciais)
            //Vamos processar esse nó criar um elemento e inserir na respetiva pilha 
            Q=Relaxation(Q, &Q_1, &Q_2, &Q_3);
            //Depois libertamos a cabeça da pilha atual e metemos a nova cabeça
            free(Q);
            /*
            printf("Processar Q_1\n");
            PrintQ(Q_1);
            PrintQ(Q_2);
            PrintQ(Q_3);
            */
        }

        if ( (Q_2 != NULL) && (Q_1 == NULL)){
            Q=Q_2;
            Q_2=Q_2->next;
            //printf("Node that's being removed from the Q_2: Node_id:%d | Type:%d | Cost:%d \n",Q->node_id,Q->type,Q->cost);
            Q=Relaxation(Q, &Q_1, &Q_2, &Q_3);
            free(Q);
            /*
            printf("Processar Q_2\n");
            PrintQ(Q_1);
            PrintQ(Q_2);
            PrintQ(Q_3);
            */
        }

        if ( (Q_3 != NULL) && (Q_1 == NULL) && (Q_2 == NULL) ){
            Q=Q_3;
            Q_3=Q_3->next;
            //printf("Node that's being removed from the Q_3: Node_id:%d | Type:%d | Cost:%d \n",Q->node_id,Q->type,Q->cost);
            Q=Relaxation(Q, &Q_1, &Q_2, &Q_3);  
            free(Q);
            /*
            printf("Processar Q_3\n");
            PrintQ(Q_1);
            PrintQ(Q_2);
            PrintQ(Q_3);
            */
        }
    }

    return;
}

Nodes *initReverseDijktra(Nodes *list_head, Nodes *destiny_node){

    Nodes *auxT;

    if(list_head == NULL){
        return NULL;
    }else{     
        auxT = list_head;
        auxT->destHead=createDestinyAlgorithm(auxT->destHead, auxT->id, destiny_node->id);
        while(auxT->next !=NULL){
            auxT = auxT->next;
            auxT->destHead=createDestinyAlgorithm(auxT->destHead, auxT->id, destiny_node->id);
        }
    }

    return list_head;
}

Queue *InsertQ(Nodes *node, Queue *Q){

    Queue *new_element=NULL, *auxH=NULL, *auxT=NULL;

    new_element=CreateNewElement(new_element, node);

    if(Q == NULL){
        Q=new_element;
    }else{     
        auxH = Q;
        auxT = auxH->next;
        if(new_element->cost < Q->cost){
            new_element->next=Q;
            Q=new_element;
        }
        while((auxT != NULL) && (new_element->cost > auxT->cost)){
                auxH = auxT;
                auxT = auxT->next;
        }
        new_element->next = auxT;
        auxH->next = new_element;
    }
    return Q;
}

Queue *CreateNewElement(Queue *new_element, Nodes *node){

    if((new_element = (Queue*) calloc(1, sizeof(Queue))) == NULL){   //Creation of a New Node 
        printf("Memory is full. Couldn't register request.\n");
	    return NULL;
    } 

    new_element->cost=node->destHead->cost;
    new_element->node_id=node->id;
    new_element->type=node->destHead->type;
    new_element->node=node;
    new_element->dest=node->destHead;
    new_element->next=NULL;

    return new_element;
}

/*
Queue *RemoveNodeFromQ(Queue *Q){

    Queue *auxH=NULL;

    auxH=Q;
    Q=Q->next;

    free(auxH);

    return Q;

}*/

//Relaxação do link uv
Queue *Relaxation(Queue *Q, Queue **Q1, Queue **Q2, Queue **Q3){

    Adj *neighbour=NULL;

    /*
        Nós só vamos tirar o elemento da pilha se e só se o que está na pilha for o que está no destiny do nó
    */
    
    if(Q == NULL){
        return Q;
    }else{
        if((Q->node->destHead->type != Q->type) || (Q->node->destHead->cost != Q->cost)){ // Deve ser || ou && ?
            //printf(" This is not going to be processed: Node_id:%d | Type:%d | Cost:%d, because is not the most recent: Node_id:%d | Type:%d | Cost:%d\n", Q->node->id, Q->node->destHead->type, Q->node->destHead->cost,Q->node_id, Q->type,Q->cost);
            return Q;
        }
        else{
            
            //printf(" This Node is going to be processed: Node_id:%d | Type:%d | Cost:%d\n", Q->node_id, Q->type,Q->cost);
            neighbour = Q->node->adjHead;
            if( (Q->type <= 1 || neighbour->type <= 1) && (neighbour->id != Q->node->destHead->chosen_neighbour_id) ){//Acho que faz sentido, mas confirmar
                //printf(" This Node is going to be relax: Node_id:%d\n", neighbour->id);
                Q = RelaxOfLink(Q, neighbour->node_pointer, neighbour->type, Q1, Q2, Q3);
            }
            while(neighbour->next != NULL){
                neighbour = neighbour->next;
                if( (Q->type <= 1 || neighbour->type <= 1) && (neighbour->id != Q->node->destHead->chosen_neighbour_id)){
                    //printf(" This Node is going to be relax: Node_id:%d\n", neighbour->id);
                    Q = RelaxOfLink(Q, neighbour->node_pointer, neighbour->type, Q1, Q2, Q3);
                }
            }
        }
    }
    return Q;
}

Queue *RelaxOfLink(Queue *Q, Nodes *adj_node, int adj_node_type, Queue **Q1, Queue **Q2, Queue **Q3){

    if( adj_node_type == 1){
        adj_node_type = 3;
    } else if (adj_node_type == 3){
        adj_node_type = 1;
    }

    if( adj_node_type < adj_node->destHead->type){
        //printf("Link was relax: Source: %d || Types: %d < %d\n",adj_node->id,adj_node_type, adj_node->destHead->type);
        adj_node->destHead->type=adj_node_type;
        adj_node->destHead->cost=Q->cost+1;
        adj_node->destHead->chosen_neighbour_id=Q->node_id;
        ChooseQ( Q1 , Q2 , Q3 , adj_node, adj_node->destHead->type);
    } 
    else if(adj_node_type == adj_node->destHead->type) {
        if( (Q->cost+1) < adj_node->destHead->cost){
            //printf("Link was relax: Source: %d || Types: %d = %d || Types: %d < %d\n",adj_node->id,adj_node_type, adj_node->destHead->type, (Q->cost+1),adj_node->destHead->cost);
            adj_node->destHead->type=adj_node_type;
            adj_node->destHead->cost=Q->cost+1;
            adj_node->destHead->chosen_neighbour_id=Q->node_id;
            ChooseQ( Q1 , Q2 , Q3 , adj_node, adj_node->destHead->type);
        }
    }

    return Q;
}

void ChooseQ(Queue **Q1, Queue **Q2, Queue **Q3, Nodes *node, int type)
{

    //printf("Node %d is going to be insert in Queue %d\n",node->id,type);
    if( type == 1){
        *Q1=InsertQ(node, *Q1);
    } else if (type == 2){
        *Q2=InsertQ(node, *Q2);
    } else if (type == 3){
        *Q3=InsertQ(node, *Q3);
    }

    return;
}

void PrintQ(Queue *Q){

    Queue *auxT;

    if(Q == NULL){
        return;
    }else{
        printf("-------- Q_%d ---------\n", Q->type);
        auxT=Q;
        printf("Q_%d: Node:%d | Cost:%d\n", Q->type,Q->node_id,Q->cost);
        auxT=auxT->next;
        while( auxT != NULL){
            printf("Q_%d: Node:%d | Cost:%d\n", auxT->type, auxT->node_id, auxT->cost);
            auxT=auxT->next;
        }
        printf("-------- Q_%d ---------\n", Q->type);
    }

    return;
}