//Rowel Espejo
//Comp 322 Spring 2025
//Project 1 

#include <stdio.h>
#include <stdlib.h>

//Data Structs
typedef struct process {
    int parent;
    int first_child;
    int younger_sibling;
}process;

//Global Variables
process * table = NULL;
int table_size = 0;
//Function Prototypes
void print_table();
void create_process();
void destroy_process();
void destroy_process_recursively(int current_index);

//Functions
int main(){
    //Enter the table size 
    printf("Enter the table size: \n");
    scanf("%d", &table_size);
    if(table_size <= 0){
        printf("Invalid table size. \n");
        return 0;
    }
    //Create the process table
    table = (process *)malloc(table_size * sizeof(process));
    int i;
    for(i = 0; i < table_size; i++){
        table[i].parent = -1;
        table[i].first_child = -1;
        table[i].younger_sibling = -1;
    }
    //Initialize the first process in the table
    table[0].parent = 0;
    //Main Loop
    int option = 0;
    while(option != 4){
        option = 4;
        printf("\n");
        printf("1) Print the table\n");
        printf("2) Create a child process\n");
        printf("3) Destroy all descendants of a process\n");
        printf("4) Quit the program\n");
        printf("Enter selection:\n");
        scanf("%d", &option);
        switch(option){
            case 1:
            print_table();
                break;
            case 2:
            create_process();
                break;
            case 3:
            destroy_process();
                break;
            case 4:
                printf("Goodbye. \n");
                break;
            default:
                printf("Invalid option, try again.\n");
        }//End of the Switch statement
    }//End of the Main Loop
    free(table);
    //Deallocate the process table
    return 0;
}//End of Main Function
void print_table(){
    int i;
    //Print the header row
    printf("Index\tParent\tFirst\tYounger\n");
    //Print every process as a row
    for(i = 0; i < table_size; i++){
        if(table[i].parent == -1){
        continue;
        }
        printf("%d\t%d\t", i, table[i].parent);
        if(table[i].first_child != -1){
            printf("%d", table[i].first_child);
        }
        printf("\t");
        if(table[i].younger_sibling != -1){
        printf("%d",table[i].younger_sibling);
        }
        printf("\n");
}//End of Print Table
}

void create_process(){
    int parent_index = -1;
    int child_index = 1;
    int youngest_index;
    //Enter the parent process index
    printf("Enter the parent process index for the child process:\n");
    scanf("%d", &parent_index);
    if(parent_index < 0 || parent_index >= table_size){
        printf("Invalid process index.\n");
        return;
    }
    if(table[parent_index].parent == -1){
        printf("Process index is not active.\n");
        return;
    }
    //Calculate the next available index as the child process index
    while(table[child_index].parent != -1){
        child_index++;
        if(child_index == table_size){
            printf("Unable to assign an index for the child process. \n");
            return;
        }
    }
    //Set the parent process index for the child process
    table[child_index].parent = parent_index;
    //Set the child process index for the parent process
    if(table[parent_index].first_child == -1){
        //Assign the child process index as the parent process' first child
        table[parent_index].first_child = child_index;
    }   else{
        //Find the youngest sibling process among the parent process' children
        //Note - Start with the oldest and traceltorwards the youngest
        youngest_index = table[parent_index].first_child;
        while(table[youngest_index].younger_sibling != -1){
            youngest_index = table[youngest_index].younger_sibling;
        }
        //Assign the child process inxex as the youngest sibling process' younger sibling
        //Note - This now mkaes the child process the new younges sibling process
        table[youngest_index].younger_sibling = child_index;
    }
    //Confrim that the child process was successfully created
    printf("Process %d was created as a child of process %d.\n" , child_index, parent_index);
}//End of Create Process

void destroy_process(){
    int parent_index = -1;
    printf("Enter the parent process index whose descendants will be destroyed:\n");
    scanf("%d", &parent_index);
    if(parent_index < 0 || parent_index >= table_size){
        printf("Invalid process index.\n");
        return;
    }
    if(table[parent_index].parent == -1){
        printf("Process index is not active.\n");
        return;
    }
    destroy_process_recursively(table[parent_index].first_child);
    table[parent_index].first_child = -1;
    printf("All descendants of process %d were destroyed.\n", parent_index);
}//End of Destroy Process

void destroy_process_recursively(int current_index){
    //Base case - Exits if invalid index
    if(current_index == -1){
        return;
    }
    if(current_index != -1){
        //Recursively destroy from current process younger sibling
        destroy_process_recursively(table[current_index].younger_sibling);
        //Recursively destroys from current prcoess first child
        destroy_process_recursively(table[current_index].first_child);
        //Remove all the data from the current process
        table[current_index].parent = -1;
        table[current_index].younger_sibling = -1;
        table[current_index].first_child = -1;
    }
}//End of Destroy Process Recursuvily
