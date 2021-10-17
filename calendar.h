#ifndef CALENDAR_INCLUDED
#define CALENDAR_INCLUDED

#include "readFile.h"
#include "nodes.h"
#include "simulation.h"



Event *announceNode(Event *event_head, Nodes *woken_node);

Event *RepAnnouncement(Event *eventHead, Nodes *node_orig, DestNode *woken_node);

Event *createEvent(Event *event_head, Nodes *node_orig, int woken_id, Adj *adj, int cost);

Event *insertEventOrdered(Event *listHead, Event *newEvent);

void printEvents(Event *listHead);

void processCalendar(Event *events_Head, Nodes *woken_node, Nodes *nodes_head);

Event *processEvent(Event *event_head, int process_node_id , Nodes *nodes_head);

Event *popEvent(Event *event_head);

#endif //CALENDAR INCLUDED