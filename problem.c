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

void *Reader(void *arg)
{
  sleep(1);
  int temp=(int)arg;
  printf(“\nReader %d is trying to enter into the Database for reading the data”,temp);
  sem_wait(&readCountAccess);
  readCount++;
  if(readCount==1)
  {
    sem_wait(&databaseAccess);
    printf(“\nReader %d is reading the database”,temp);
  }
  sem_post(&readCountAccess);
  sem_wait(&readCountAccess);
  readCount–;
  if(readCount==0)
  {
    printf(“\nReader %d is leaving the database”,temp);
    sem_post(&databaseAccess);
  }
  sem_post(&readCountAccess);
}
