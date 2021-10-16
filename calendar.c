#include "readFile.h"
#include "calendar.h"
#include "nodes.h"
#include "simulation.h"

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
// Mas atenção às leis comerciais !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Basicamente se houver cliente enviamos, senão houver clientes barulho não se envia nada
Event *RepAnnouncement(Event *eventHead, Nodes *node_orig, DestNode *woken_node){

    Adj *neighbor;

    if(node_orig == NULL){
        return eventHead;
    }else{
         neighbor= node_orig->adjHead;
            if( woken_node->type == 1 || neighbor->type == 1)
                eventHead = createEvent(eventHead, node_orig, woken_node->dest_id, neighbor, woken_node->cost);
        while(neighbor->next != NULL){
            neighbor = neighbor->next;
            if( woken_node->type == 1 || neighbor->type == 1)
                eventHead = createEvent(eventHead, node_orig, woken_node->dest_id, neighbor, woken_node->cost);
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
    if (new_event->An < adj->An) new_event->An=adj->An;  //Tratar da fila de espera de cada ligação    
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


Event *insertEventOrdered(Event *list_head, Event *new_event){

    Event *auxT;

    if(list_head == NULL){
        return new_event;
    }else{
        if(new_event->An < list_head->An){
            new_event->next=list_head;
            list_head = new_event;
        }
        else{
            auxT = list_head;
            while(auxT->next != NULL){
                auxT = auxT->next;
                if(new_event->An < auxT->An){
                    new_event->next = auxT;
                    auxT = new_event;
                    return list_head;
                }
            }
            auxT->next = new_event;
            new_event->next = NULL;
        }
    }

    return list_head;
}

void printEvents(Event *listHead){
    
    Event *auxH, *auxT;
    
    if(listHead == NULL){
        return;
    }else{
        auxH = listHead;
        
        printf("\nEvent: \n\torigin %d\n\tdest %d\n \t%d -> %d = %d \n", auxH->origin_node, auxH->dest_node, auxH->message[0], auxH->message[1], auxH->message[2]);
        printf("\t[time=%d|%d->%d|Type:%d]->",auxH->An,auxH->origin_node,auxH->dest_node,auxH->type); fflush(stdout);//prompt
        auxT=listHead->next;
        while( auxT != NULL){
            auxH=auxT;
            auxT=auxT->next;
            printf("\nEvent: \n\torigin %d\n\tdest %d\n \t%d -> %d = %d \n", auxH->origin_node, auxH->dest_node, auxH->message[0], auxH->message[1], auxH->message[2]);
            printf("\t[time=%d|%d->%d|Type:%d]->",auxH->An,auxH->origin_node,auxH->dest_node,auxH->type); fflush(stdout);//prompt
        }
        printf("NULL\n");
    }

    return;
}

void processCalendar(Event *events_Head, Nodes *woken_node, Nodes *nodes_head)
{
    events_Head = announceNode(events_Head, woken_node); //First wake up the node, create the respective events and insert them in the calendar
    
    while(events_Head != NULL){
        processEvent(events_Head, events_Head->dest_node, nodes_head);
        events_Head = popEvent(events_Head);
    }

    return;
}


void processEvent(Event *event_head, int process_node_id , Nodes *nodes_head)
{
   
    Nodes *orig_node = NULL;
    DestNode *woken_node =NULL;

    //Primeiro, encontrar o nó que queremos processar
    orig_node=searchNodesList(nodes_head,process_node_id);

    //Segundo, processar o evento -> Atualizar a tabela de encaminhamento
    woken_node = updateDestToNode(orig_node, event_head->message, event_head->type);
    if (woken_node != NULL)
        event_head = RepAnnouncement(event_head, orig_node, woken_node);

    return;
}


Event *popEvent(Event *event_head)
{
    Event *auxH = NULL;
    
    auxH = event_head;
    event_head = event_head->next;
    free(auxH);

    return event_head;
}

    
