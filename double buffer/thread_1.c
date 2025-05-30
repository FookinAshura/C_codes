#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

pthread_t writeThread;
pthread_t readThread;
pthread_mutex_t bufferMutex = PTHREAD_MUTEX_INITIALIZER;

char buffer1[] = {"Logs:30/05/2025"};
char buffer2[] = {0};

struct mutex_shared {
    int stillReading, stillWriting, not_over;
    char *writeBuff, *readBuff;
}SHARED;

void* writeBuffer(void *ptr)
{
    pthread_mutex_lock(&bufferMutex);

    strcpy(SHARED.writeBuff, "Logs:30/05/2025");
    SHARED.stillWriting = 0;
    SHARED.not_over = 1;

    pthread_mutex_unlock(&bufferMutex);

    return NULL;
}

void* readBuffer(void *data)
{
    while(SHARED.stillWriting);

    pthread_mutex_lock(&bufferMutex);
    strcpy(SHARED.readBuff, SHARED.writeBuff);
    printf("\n Reader : %s \n", SHARED.readBuff);

    SHARED.stillReading = 0;
    pthread_mutex_unlock(&bufferMutex);

    return NULL;
}

int main()
{
    SHARED.writeBuff = buffer1;
    SHARED.readBuff = buffer2;
    printf("%p \n", SHARED.writeBuff);
    printf("%p \n", SHARED.readBuff);

    SHARED.stillWriting = 1;
    SHARED.stillReading = 1;
    SHARED.not_over = 0;

    pthread_create(&writeThread, NULL, writeBuffer, NULL);
    pthread_create(&readThread, NULL, readBuffer, NULL);

    pthread_join(writeThread, NULL);
    pthread_join(readThread, NULL);

    return 0;
}
