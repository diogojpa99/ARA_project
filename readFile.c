#include "readFile.h"
#include "calendar.h"
#include "nodes.h"
#include "simulation.h"


int main()
{
    FILE *fp;
    int tail, head, type;
    Nodes *nodes_head = NULL;
    Event *event_head = NULL;
    

    fp = fopen("grafo3.txt","r");
    srand(time(0));

    if(fp==NULL){
        perror("Error opening the text file");
        return(-1);
    }

    while( fscanf(fp, "%d %d %d\n", &tail, &head, &type) != EOF ){
        nodes_head = createGraph(nodes_head, tail, head, type);
    }
    Print_List_of_Adjacencies(nodes_head);
    
    /******************************************** Simulation ***********************************************/

    printf("\n\n ------------ The simulation has started ------------ \n");
    
    simulation(nodes_head, event_head);

    Print_List_of_Destinations(nodes_head);

    
    

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
    freeGraphNodes(nodes_head);
    //freeEventsNodes(eventHead);
    return 0;
}

