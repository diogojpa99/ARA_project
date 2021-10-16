#ifndef CALENDAR_INCLUDED
#define CALENDAR_INCLUDED

#include "nodes.h"
#include "readFile.h"


Event *announceNode(Event *event_head, Nodes *woken_node);

Event *RepAnnouncement(Event *eventHead, Nodes *node_orig, DestNode *dest_node, int woken_id);

Event *createEvent(Event *event_head, Nodes *node_orig, int woken_id, Adj *adj, int cost);

Event *insertEventOrdered(Event *listHead, Event *newEvent);

void printEvents(Event *listHead);

void processCalendar(Event *event_head, Nodes *nodes_orig);

Event *processEvent(Event *event, Nodes *nodesHead);

Event *popEvent(Event *event);

#endif //CALENDAR INCLUDED