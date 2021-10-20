#include "readFile.h"

#include "calendar.h"
#include "nodes.h"
#include "simulation.h"

int Dn = 0;
int main(int argc, char **argv)
{
    FILE *fp;
    int tail, head, type, opt;
    Nodes *nodes_head = NULL;
    Event *event_head = NULL;
    char buffer[128];

    int input_dest_id, input_origin_id;

    
    
    fp = fopen("grafo4.txt","r");
    srand(time(0));

    if(fp==NULL){
        perror("Error opening the text file");
        return(-1);
    }

    while( fscanf(fp, "%d %d %d\n", &tail, &head, &type) != EOF ){
        nodes_head = createGraph(nodes_head, tail, head, type);
    }

    //validacao da linha de comandos
    while((opt = getopt(argc, argv, "m:")) != -1){
        switch (opt)
        {
        case 'm':
            strcpy(buffer, optarg);
            if(strcmp(buffer, "interactive") == 0){
                commandLineValidation(argc, argv, &input_origin_id, &input_dest_id, nodes_head);
            }
            else if(strcmp(buffer, "help") == 0){
                commandLineValidation(argc, argv, &input_origin_id, &input_dest_id, nodes_head);
            }else if(strcmp(buffer, "ninteractive") == 0)
            {

            }
            else{

                printf("Error: Bad arguments in program call\n");
                printf("Type: ./graph help\n");
                exit(0);
            }
            break;
        }
    }

    Print_List_of_Adjacencies(nodes_head);
    
    /******************************************** Simulation ***********************************************/

    printf("\n\n ------------ The simulation has started ------------ \n");
    simulation(nodes_head, event_head);
    Print_List_of_Destinations(nodes_head);

    
    

    /**************************************** Interactive Mode ********************************************/



    fclose(fp);
    freeGraphNodes(nodes_head);
    //freeEventsNodes(eventHead);
    return 0;
}

void commandLineValidation(int argc, char **argv, int *origin_id, int *dest_id, Nodes *nodes_head)
{
    char garbage[128], buffer[128];

    if( argc == 3 && (strcmp(argv[2], "help") == 0))
    {
        printf("A aplicação graph é invocada com o comando\n\tgraph -m <interactive/ninteractive>\n");
        exit(1);
    }    
    else if(argc == 3 && strcmp(argv[2], "interactive") == 0)
    {
        printf("List of nodes:\n");
        Print_List_of_Nodes(nodes_head);
        printf("\n");
        printf("Choose an origin node and a destiny node: ");
        fgets(buffer, 128, stdin);
        if(sscanf(buffer, "%d %d%s", origin_id, dest_id , garbage) != 2){
            printf("Error: Bad <origin_id> <dest_id>\n"); exit(1);
        }
        
    }
    
}

