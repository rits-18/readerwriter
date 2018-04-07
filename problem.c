#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t rcAccess;
sem_t dbAccess;
int readCount=0;

void *Writer(void *arg)
{
  sleep(5);
  int temp=(int)arg;
  printf("\nWriter %d is trying to enter into database for modifying the data",temp);
  sem_wait(&dbAccess);
  printf("\nWriter %d is writting into the database",temp);
  printf("\nWriter %d is leaving the database");
  sem_post(&dbAccess);
}

void *Reader(void *arg)
{
  sleep(1);
  int temp=(int)arg;
  printf("\nReader %d is trying to enter into the Database for reading the data",temp);
  sem_wait(&rcAccess);
  readCount++;
  if(readCount==1)
  {
    sem_wait(&dbAccess);
    printf("\nReader %d is reading the database",temp);
  }
  sem_post(&rcAccess);
  sem_wait(&rcAccess);
  readCount--;
  if(readCount==0)
  {
    printf("\nReader %d is leaving the database",temp);
    sem_post(&dbAccess);
  }
  sem_post(&rcAccess);
}
