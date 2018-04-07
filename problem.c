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
int main()
{
  int i,rt,wt;
  sem_init(&rcAccess,0,1);
  sem_init(&dbAccess,0,1);
  pthread_t Readers_thr[100],Writer_thr[100];
  printf("\nEnter number of Readers thread");
  scanf("%d",&rt);
  printf("\nEnter number of Writers thread");
  scanf("%d",&wt);
  for(i=0;i<rt;i++)
  {
      if(pthread_create(&Readers_thr[i],NULL,Reader,(void *)i) != 0)
	    {
		      fprintf(stderr, "Error while creating Reader's thread\n");
		      exit(1);
	     }
  }
  for(i=0;i<wt;i++)
  {
      if(pthread_create(&Writer_thr[i],NULL,Writer,(void *)i); != 0)
	    {
		      fprintf(stderr, "Error while creating writer's thread\n");
		      exit(1);
	    }
  }
  for(i=0;i<wt;i++)
  {
	    pthread_join(Writer_thr[i],NULL);
   }
   for(i=0;i<rt;i++)
   {
	    pthread_join(Readers_thr[i],NULL);
   }
   return 0;
} 
