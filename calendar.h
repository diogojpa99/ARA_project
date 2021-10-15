#ifndef CALENDAR_INCLUDED
#define CALENDAR_INCLUDED

#include "nodes.h"
#include "readFile.h"


Event *announceNode(Event *eventHead, Nodes *node);

Event *createEvent(Event *listHead, Nodes *node, Adj *adj, int type_ev);

Event *insertEventOrdered(Event *listHead, Event *newEvent);

void printEvents(Event *listHead);

void processCalendar(Event *listHead, Nodes *nodesHead);

Event *processEvent(Event *event, Nodes *nodesHead);

void removeEvent(Event *event);

#endif //CALENDAR INCLUDED