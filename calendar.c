#include "calendar.h"
#include "nodes.h"
#include "readFile.h"

//AnnounceNode: Para cada ligação (adjacente), vai se criar um novo evento.
Event *announceNode(Event *event_head, Nodes *woken_node){

    Adj *auxT;

    if(woken_node == NULL){
        return event_head;
    }else{
        auxT = woken_node->adjHead;
            event_head = createEvent(event_head, woken_node, woken_node->id, auxT, 0);
        while(auxT->next != NULL){
            auxT = auxT->next;
            event_head = createEvent(event_head, woken_node, woken_node->id, auxT, 0);
        }
    }
    return event_head;
}

//RepAnnouncement: Para cada ligação (adjacente), vai se criar um novo evento.
Event *RepAnnouncement(Event *eventHead, Nodes *node_orig, DestNode *dest_node, int woken_id){

    Adj *auxT;

    if(node == NULL){
        return eventHead;
    }else{
        auxT = node_orig->adjHead;
            eventHead = createEvent(eventHead, node_orig, woken_id, auxT, dest_node->cost);
        while(auxT->next != NULL){
            auxT = auxT->next;
            eventHead = createEvent(eventHead, node_orig, woken_id, auxT, dest_node->cost);
        }
    }
    return eventHead;
}

//Funcao que cria um novo evento para ser inserido no calendario
/*Parametros:
list_head - cabeça da lista de eventos*/

Event *createEvent(Event *event_head, Nodes *node_orig, int woken_node_id, Adj *adj, int cost) 
{
    Event *new_event = NULL;
    int Sn = 0;
   
    if((new_event = (Event*) calloc(1, sizeof(Event))) == NULL){   /** Creation of a New Event **/
        printf("Memory is full. Couldn't register request.\n");
		return event_head;
    }

    Sn = 1 + rand()%3;
    new_event->An = Dn + Sn;
    if (new_event->An < adj->An) //Tratar da fila de espera de cada ligação 
        new_event->An=adj->An;     
    new_event->origin_node = node_orig->id; // nó que está a enviar a sms
    new_event->dest_node = adj->id; // nó a quem se destina a sms
    new_event->type = adj->type; //relaçao entre os dois nós
    new_event->next = NULL;

    //Message sent from an node x to his neighbor
    new_event->message[0] = node_orig->id;
    new_event->message[1] = woken_node_id;
    new_event->message[2] = cost; 

    //printf("time=%d | out_node=%d | in_node=%d | type=%d\n",newEvent->time,newEvent->origin_node,newEvent->dest_node,newEvent->type);

    return event_head = insertEventOrdered(event_head, new_event);
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

void processCalendar(Event *events_Head, Nodes *woken_node)
{
    event_Head = announceNode(event_head, woken_node); //First wake up the node, create the respective events and insert them in the calendar
    
    while(events_Head != NULL){
        processEvent(events_Head, event_Head->dest_node);
    }

    return;
}



Event *processEvent(Event *event, Nodes *nodes_Head)
{
    Nodes *dest_Node = NULL, *orig_Node = NULL;

    dest_Node = searchNodesList(nodes_Head, event->dest_node);//nó de destino da mensagem
    orig_Node = searchNodesList(nodes_Head, event->origin_node);//nó de origem da mensagem

    updateDestToNode(dest_Node, event->message);

}

Event *popEvent(Event *event_head)
{
    Event *auxH = NULL;
    
    auxH = event_head;
    event_head = event_head->next;
    free(auxH);

    return event_head;
}

    
