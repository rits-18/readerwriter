#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t readCountAccess;
sem_t databaseAccess;
int readCount=0;

void *Writer(void *arg)
{
sleep(1);
int temp=(int)arg;
printf("\nWriter %d is trying to enter into database for modifying the data",temp);
sem_wait(&databaseAccess);
printf("\nWriter %d is writting into the database",temp);
printf("\nWriter %d is leaving the database");
sem_post(&databaseAccess);
}
