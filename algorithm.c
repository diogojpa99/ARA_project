#include "readFile.h"
#include "nodes.h"

void Algorithm(Nodes *nodes_head, int destiny_id) {

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

void ReverseDijkstra(Nodes *nodes_head, Nodes *destiny_node) {

    Queue *Q_1,*Q_2,*Q_3; //Vão ser heaps ou listas normais ??

    nodes_head=initReverseDijktra(nodes_head, destiny_node, Q_1);

    return;
}

Nodes *initReverseDijktra(Nodes *list_head, Nodes *destiny_node, Queue *Q_1){

    Nodes *auxT;

    if(list_head == NULL){
        return NULL;
    }else{     
        auxT = list_head;
        if(auxT->id == destiny_node->id)
        auxT->destHead=createDestinyAlgorithm(auxT->destHead, destiny_node);
        while(auxT->next !=NULL){
            auxT = auxT->next;
            auxT->destHead=createDestinyAlgorithm(auxT->destHead, destiny_node);
        }
    }

    return list_head;
}