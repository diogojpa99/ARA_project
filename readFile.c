#include "readFile.h"
#include "calendar.h"
#include "nodes.h"


int main()
{
    FILE *fp;
    int tail, head, type, node_id, flag = 0, n_nodes, awaken_node;
    Nodes *nodesHead = NULL, *newNode = NULL, *node = NULL;
    Event *eventHead = NULL;

    fp = fopen("grafo1.txt","r");
    srand(time(0));

    if(fp==NULL){
        perror("Error opening the text file");
        return(-1);
    }

    while( fscanf(fp, "%d %d %d\n", &tail, &head, &type) != EOF ){
        nodesHead = createGraph(nodesHead, tail, head, type);
    }
    Print_List_of_Adjacencies(nodesHead);
    
    /******************************************** Simulation ***********************************************/

    printf("The simulation has started!\n");
    n_nodes = walk_trough_nodesList(nodesHead);
    awaken_node = rand()%n_nodes;

    node = wakeNode(nodesHead,awaken_node); //Awake random Node in the Nodes List

    if(node == NULL)
        printf("UPS!\n");
    else
        printf("\nmain: Awaken Node id(rand):%d(%d)\n",node->id,awaken_node);
    //criar eventos de anuncio para o nó que se acordou
    eventHead = announceNode(eventHead, node);



    //Processar o calendário

    printEvents(eventHead);

    /**************************************** Interactive Mode ********************************************
        printf("Insert the id of the node you want to wake: "); fflush(stdout);//prompt
        while(flag==0){ //Problemas: Loop em "abc" e ignora o "a" em "123a"
            if( (scanf("%d", &node_id) != 1) && (node_id<=1 || node_id>=MAX_ID)){
                printf("You have to insert an integer from 1 to %d\n", MAX_ID);
                printf("Insert the id of the node you want to wake: "); fflush(stdout);//promp
            }else{
                flag=1;
            }
        }
        printf("id:%d\n", node_id); fflush(stdout);//prompt
    **********************************************************************************************************/

    fclose(fp);
    //freeGraphNodes(nodesHead);
    //freeEventsNodes(eventHead);
    return 0;
}

