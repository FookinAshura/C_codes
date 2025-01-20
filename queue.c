#include <stdio.h> 
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define DATA_ARRAY_SIZE 6

// Create a global array to hold 6 elements
typedef struct myQueue
{
    uint16_t*   data;
    int8_t      start_index;
    int8_t      latest_updated_index;
    uint16_t    queue_max_size;
}myQueue_t;

//Function to create a queue of desired size
myQueue_t* createQueue(uint16_t queue_size)
{
    myQueue_t* queue_instance            = (myQueue_t*) malloc(sizeof(myQueue_t));
    queue_instance->data                 = (uint16_t*) malloc(queue_size * sizeof(uint16_t));
    queue_instance->start_index          = (-1);
    queue_instance->latest_updated_index = (-1);
    queue_instance->queue_max_size       = queue_size;
    return (queue_instance);
}

//Function that shifts the data after Processing
void shiftData(myQueue_t* received_queue)
{
    if(received_queue->latest_updated_index == 0)
    {
        return;
    }
    
    for(int index = 0; index < received_queue->latest_updated_index; index++)
    {
        received_queue->data[index] = received_queue->data[index + 1];
    }
    received_queue->data[received_queue->latest_updated_index] = 0; 
    --received_queue->latest_updated_index;
}

//Functionm to print the updated Queue
void printNewQueue(myQueue_t* received_queue)
{
    printf("The updated data array = "); 
    for(int index = 0; index < received_queue->latest_updated_index; index++)
    {
        printf("%d\t",received_queue->data[index]);
    }
    printf("\n");
}
//Create a function to add elements to the data array
void processData(myQueue_t* received_queue)
{
    if(received_queue->start_index == -1)
    {
        printf("The Data Queue is empty \n");
    }
    else
    {
        printf("Processing...\n");
        received_queue->data[0] = 0;
        shiftData(received_queue);
        printNewQueue(received_queue);
    }
}

//Create a function to fetch data from the array and process it 
void updateArray(myQueue_t* received_queue, uint16_t data)
{
    if(received_queue->latest_updated_index == received_queue->queue_max_size - 1)
    {
        printf("Data Array is full...\n");
    }
    else
    {
        received_queue->start_index = 0;
        received_queue->latest_updated_index += 1;
        received_queue->data[received_queue->latest_updated_index] = data;
        printf("Added %hu to the queue at position %d\n", data, received_queue->latest_updated_index);
    }
}

int main()
{
    myQueue_t* queue_1 = createQueue(DATA_ARRAY_SIZE);
    char user_input[10]; 
    uint16_t user_data = 0;
    
    while(1)
    {
        printf("Enter the command Process/Data\n");
        scanf("%s", user_input);
        if(!(strcmp(user_input, "Process")))
        {
            processData(queue_1);
        }
        else if(!(strcmp(user_input, "Data")))
        {
            scanf("%hd", &user_data);
            updateArray(queue_1, user_data);
        }
    }
}