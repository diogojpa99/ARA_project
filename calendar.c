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
    newEvent->next = NULL;

    switch (type_ev)
    {
    case annouce:
        newEvent->message[0] = node->id;
        newEvent->message[1] = node->id;
        newEvent->message[2] = 0;
        break;
    case rep_annouce:// fazer para o caso de estarmos a passar uma mensagem vinda de outro nó
        newEvent->message[0] = node->id;
        newEvent->message[1] = -1;
        newEvent->message[2] = 0;

        break;
    
    default:
        break;
    }
    

    printf("time=%d | out_node=%d | in_node=%d | type=%d\n",newEvent->time,newEvent->origin_node,newEvent->dest_node,newEvent->type);

    return listHead = insertEventOrdered(listHead, newEvent);
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
    
    if(listHead == NULL){
        return;
    }else{
        auxH = listHead;
        
        printf("\nEvent: \n\torigin %d\n\tdest %d\n \t%d -> %d = %d \n", auxH->origin_node, auxH->dest_node, auxH->message[0], auxH->message[1], auxH->message[2]);
        printf("\t[time=%d|%d->%d|Type:%d]->",auxH->time,auxH->origin_node,auxH->dest_node,auxH->type); fflush(stdout);//prompt
        auxT=listHead->next;
        while( auxT != NULL){
            auxH=auxT;
            auxT=auxT->next;
            printf("\nEvent: \n\torigin %d\n\tdest %d\n \t%d -> %d = %d \n", auxH->origin_node, auxH->dest_node, auxH->message[0], auxH->message[1], auxH->message[2]);
            printf("\t[time=%d|%d->%d|Type:%d]->",auxH->time,auxH->origin_node,auxH->dest_node,auxH->type); fflush(stdout);//prompt
        }
        printf("NULL\n");
    }

    return;
}

void processCalendar(Event *events_Head, Nodes *nodes_Head)
{
    Event *auxH, *auxT  = NULL;
    
    if(events_Head == NULL){
        return;
    }else{
        auxH = events_Head;
        processEvent(auxH, nodes_Head);

        auxT = events_Head->next;
        while (auxT != NULL)
        {
            auxH = auxT;
            processEvent(auxT, nodes_Head);
            auxT = auxT->next;
            
            //events_Head = auxT;
            //removeEvent(auxH);
        }
        
    }

    return;
}

Event *processEvent(Event *event, Nodes *nodes_Head)
{
    Nodes *dest_Node, *orig_Node = NULL;

    dest_Node = searchNodesList(nodes_Head, event->dest_node);
    orig_Node = searchNodesList(nodes_Head, event->origin_node);

    updateDestToNode(orig_Node->id, dest_Node);

}

void removeEvent(Event *event)
{
    free(event);
}

    
