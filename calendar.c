#include "calendar.h"
#include "nodes.h"
#include "readFile.h"




//Funcao que cria um novo evento para poder ser inserido no calendario
Event *createEvent(Event *listHead, Nodes *node, Adj *adj, int type_ev) //Também é necessário a cabeça da lista de eventos
{
    Event *newEvent = NULL;
   
    if((newEvent = (Event*) calloc(1, sizeof(Event))) == NULL){   /** Creation of a New Event **/
        printf("Memory is full. Couldn't register request.\n");
		return listHead;
    } 
    newEvent->time = 1+rand()%3;
    newEvent->origin_node = node->id;
    newEvent->dest_node = adj->id;
    newEvent->type = adj->type;

    switch (type_ev)
    {
    case annouce:
        newEvent->cost[0] = node->id;
        newEvent->cost[1] = node->id;
        newEvent->cost[2] = 0;
        break;
    case rep_annouce:// fazer para o caso de estarmos a passar uma mensagem vinda de outro nó
        newEvent->cost[0] = node->id;
        newEvent->cost[1] = -1;
        newEvent->cost[2] = 0;

        break;
    
    default:
        break;
    }
    

    printf("time=%d | out_node=%d | in_node=%d | type=%d\n",newEvent->time,newEvent->origin_node,newEvent->dest_node,newEvent->type);

    return listHead=insertEventOrdered(listHead, newEvent);
}

Event *announceNode(Event *eventHead, Nodes *node){

    Adj *auxT;

    if(node == NULL){
        return eventHead;
    }else{
        auxT = node->adjHead;
            eventHead = createEvent(eventHead, node, auxT, annouce);
        while(auxT->next != NULL){
            auxT = auxT->next;
            eventHead = createEvent(eventHead, node, auxT, annouce);
        }
    }
    return eventHead;
}


Event *insertEventOrdered(Event *listHead, Event *newEvent){

    Event *auxT;

    if(listHead == NULL){
        return newEvent;
    }else{
        if(newEvent->time < listHead->time){
            newEvent->next=listHead;
            listHead = newEvent;
        }
        else{
            auxT = listHead;
            while(auxT->next != NULL){
                auxT = auxT->next;
                if(newEvent->time < auxT->time){
                    newEvent->next = auxT;
                    auxT = newEvent;
                    return listHead;
                }
            }
            auxT->next = newEvent;
            newEvent->next = NULL;
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
        
        printf("\nEvent: \n\torigin %d\n\tdest %d\n \t%d -> %d = %d \n", auxH->origin_node, auxH->dest_node, auxH->cost[0], auxH->cost[1], auxH->cost[2]);
        printf("\t[time=%d|%d->%d|Type:%d]->",auxH->time,auxH->origin_node,auxH->dest_node,auxH->type); fflush(stdout);//prompt
        auxT=listHead->next;
        while( auxT != NULL){
            auxH=auxT;
            auxT=auxT->next;
            printf("\nEvent: \n\torigin %d\n\tdest %d\n \t%d -> %d = %d \n", auxH->origin_node, auxH->dest_node, auxH->cost[0], auxH->cost[1], auxH->cost[2]);
            printf("\t[time=%d|%d->%d|Type:%d]->",auxH->time,auxH->origin_node,auxH->dest_node,auxH->type); fflush(stdout);//prompt
        }
        printf("NULL\n");
    }

    return;
}


    
