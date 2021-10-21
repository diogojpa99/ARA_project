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

void ReverseDijkstra(Nodes *nodes_head, Nodes *destiny_node){

    Queue *Q_1=NULL,*Q_2=NULL,*Q_3=NULL; //Vão ser heaps ou listas normais ??
    /* Q_1, Q_2, Q_3 representam as cabeças de cada uma das filas ordenadas */

    //Iniciar o Reverse Dijkstra
    nodes_head=initReverseDijktra(nodes_head, destiny_node);

    //Colocar o destino na pilha com custo zero 
    Q_1=InsertQ(destiny_node, Q_1);

    while (Q_1 != NULL){
        //retirar o nó que está na cabeça da pilhaS

        if(Q_1->cost < Q_1->node->destHead->cost){ //Temos que atualizar -> Atualizamos só quando é melhor ou sempre ??
            Q_1->node->destHead->cost=Q_1->cost;
            //node->destHead->chosen_neighbour_id=??
            
            //Ver os meus vizinhos (Mas atenção às restrições comerciais)
            //Enquanto a lista de adjacências não estiver vazia
            //Vamos processar esse nó criar um elemento e inserir na respetiva pilha 

            //Depois libertamos a cabeça da pilha atual e metemos a nova cabeça
        }

    }

    while (Q_2 != NULL){
        
    }

    while (Q_2 != NULL){
        
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
        while((auxT != NULL) && (new_element->cost > new_element->cost)){
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

Nodes *RemoveTopNodeFromQ(Queue *Q){


}