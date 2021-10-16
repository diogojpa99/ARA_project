#include "readFile.h"
#include "calendar.h"
#include "nodes.h"
#include "simulation.h"

/**********************************     Simulation      *****************************************/
/* Vamos acordar cada nó da lista de nós, separadamente. Ou seja, primeiro acordamos um nó x e  */
/* preenchemos as tabelas de encaminhamento dos nós que conseguem chegar ao nó de destino x. E  */
/* Depois fazemos o mesmo para os restantes nós da lista de nós.                                */
/************************************************************************************************/
void simulation(Nodes *nodes_head, Event *event_head){
    
    Nodes *auxT = NULL; 
    
    if(nodes_head == NULL){
        return;
    }else{
        auxT = nodes_head;
        processCalendar(event_head, auxT, nodes_head);
        while( auxT->next != NULL){
            auxT = auxT->next;
            processCalendar(event_head, auxT, nodes_head);
        }
    }
    return;
} 

