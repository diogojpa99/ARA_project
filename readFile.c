#include "readFile.h"

#include "calendar.h"
#include "nodes.h"
#include "simulation.h"
#include "algorithm.h"

int Dn = 0;
int *times_simulations = NULL;
int nr_nodes = 0;

int main(int argc, char **argv)
{
    enum modes_{help, none, interactive_sim, simulation, interactive_algo, algorithm };
    enum modes_ mode = none;

    FILE *fp;

    int tail, head, type, opt;
    char buffer[128];
    int input_dest_id, input_origin_id;

    Nodes *nodes_head = NULL;
    Event *event_head = NULL;
    

    
    
    fp = fopen("grafo2.txt","r");
    srand(time(0));

    if(fp == NULL){
        perror("Error opening the text file");
        return(-1);
    }

    while( fscanf(fp, "%d %d %d\n", &tail, &head, &type) != EOF ){
        nodes_head = createGraph(nodes_head, tail, head, type);
    }

    //Por os Adjacentes a apontar para a posição deles na lista de nós
    nodes_head = AdjToNode(nodes_head);

    //validacao da linha de comandos
    while((opt = getopt(argc, argv, "m:")) != -1){
        switch (opt)
        {
        case 'm':
            strcpy(buffer, optarg);
            if(strcmp(buffer, "interactive_sim") == 0){
                commandLineValidation(argc, argv, &input_origin_id, &input_dest_id, nodes_head);
                mode = interactive_sim;

            }else if(strcmp(buffer, "interactive_algo") == 0){
                commandLineValidation(argc, argv, &input_origin_id, &input_dest_id, nodes_head);
                mode = interactive_algo;

            }else if(strcmp(buffer, "help") == 0){
                commandLineValidation(argc, argv, &input_origin_id, &input_dest_id, nodes_head);

            }else if(strcmp(buffer, "simulation") == 0){
                mode = simulation;

            }else if(strcmp(buffer, "algorithm") == 0){
                mode = algorithm;

            }else{
                printf("Error: Bad arguments in program call\n");
                printf("Type: ./graph -m help\n");
                exit(0);
            }
            break;
        }
    }
    


    switch (mode)
    {
        case interactive_sim:
            /*tem que dar como output o tipo e o comprimento da rota entre um destino e uma source dados na funcao commandLineValidation*/
            printf("\n\n ------------ The simulation has started ------------ \n");
            simulations(nodes_head, event_head);
            Print_List_of_Destinations(nodes_head, simulation);

            break;
        case simulation:
            printf("\n\n ------------ The simulation has started ------------ \n");
            
            simulations(nodes_head, event_head);
            Print_List_of_Destinations(nodes_head, simulation);
            
            write_times_simulations();
            write_types_costs_routs(nodes_head);
            break;

        case interactive_algo:
            printf("\n -------------- Algorithm ------------------------- \n");
            clearAllDest(nodes_head);
            Algorithm(nodes_head);
            Print_List_of_Destinations(nodes_head, algorithm);
            //Print_List_of_Adjacencies(nodes_head);

            break;
        case algorithm:
            printf("\n -------------- Algorithm ------------------------- \n");
            nodes_head = AdjToNode(nodes_head);

            Algorithm(nodes_head);
            Print_List_of_Destinations(nodes_head, algorithm);

            break;
        default:
            printf("Error: Bad arguments in program call\n");
            printf("Type: ./graph -m help\n");
            exit(0);

            break;
    }

    //freeEventsNodes(eventHead);
    freeGraphNodes(nodes_head);
    fclose(fp);
    free(times_simulations);
    return 0;
}

void commandLineValidation(int argc, char **argv, int *origin_id, int *dest_id, Nodes *nodes_head)
{
    char garbage[128], buffer[128];

    if( argc == 3 && (strcmp(argv[2], "help") == 0))
    {
        printf("A aplicação graph é invocada com o comando\n\tgraph -m <interactive_sim/interactive_algo/algorithm/simulation/help>\n");
        exit(1);
    }    
    else if(argc == 3 && (strcmp(argv[2], "interactive") == 0 || strcmp(argv[2], "algorithm") == 0))
    {
        printf("List of nodes:\n");
        Print_List_of_Nodes(nodes_head);
        printf("\n");
        printf("Choose an origin node and a destiny node: ");
        fgets(buffer, 128, stdin);
        
        if(sscanf(buffer, "%d %d%s", origin_id, dest_id , garbage) != 2){
            printf("Error: Bad <origin_id> <dest_id>\n");
        }
        
    }
    
}




void write_times_simulations()
{
    FILE *fp;
    int i;


    fp = fopen("times_simulations.txt","w");

    for(i = 0; i < nr_nodes; i++){
        fprintf(fp, "%d\n", times_simulations[i]);
    }
    fclose(fp);
    
}

void write_types_costs_routs(Nodes *nodes_head)
{
    FILE *fd;
    Nodes *nodes_auxT;
    DestNode *dest_auxT;

    fd = fopen("types_costs_simulations.txt","w");

    

    if(nodes_head==NULL){
        return;
    }else{
        for(nodes_auxT = nodes_head; nodes_auxT != NULL; nodes_auxT = nodes_auxT->next) {
            for(dest_auxT = nodes_auxT->destHead; dest_auxT != NULL; dest_auxT = dest_auxT->next_dest) {
                fprintf(fd,"%d %d\n", dest_auxT->type, dest_auxT->cost);  
            }
        }
    }
    fclose(fd);

    return;
}
