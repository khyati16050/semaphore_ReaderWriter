#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
void * reader(void *);  
void *writer (void *);  
sem_t wsem;
sem_t mutex;  
int readcount = 0;  
int value = 0;

main()  
{  
    int i;
    int NumberofReaderThread=0; //number of reader threads
    int NumberofWriterThread; //number of writer threads
    sem_init(&wsem,0,1);  //semaphore initialisation
    sem_init(&mutex,0,1); //semaphore initialisation
      if((sem_init(&wsem,0,1)==-1)||(sem_init(&mutex,0,1)==-1))
        {
            error_msg();
        }
    pthread_t Readers_thr[100]; //reader thread array
    pthread_t Writer_thr[100]; //writer thread array
    printf("\nEnter number of Readers thread - ");
    scanf("%d",&NumberofReaderThread);
    printf("\nEnter number of Writers thread - ");
    scanf("%d",&NumberofWriterThread);
      if(&NumberofWriterThread == 0 && &NumberofReaderThread == 0 )
        {
          error_msg_1();
        }
    for(i=1;i <= NumberofReaderThread;i++) //creates number of reader threads
      {
      pthread_create(&Readers_thr[i],NULL,reader,(void *)i);
      }
    for(i=1;i <= NumberofWriterThread;i++) //creates number of writer threads
      {
      pthread_create(&Writer_thr[i],NULL,writer,(void *)i);
      }
    for(i=1;i <= NumberofReaderThread;i++) //joins reader threads
      {
      pthread_join(Readers_thr[i],NULL);
      }
    for(i=1;i <= NumberofWriterThread;i++) //joins writer threads
      {
      pthread_join(Writer_thr[i],NULL);
      }
    printf("-------------------------------------------------------------------------------\n");
    printf("Threads closed , process has finished\n");  //end 
    return 0;
}  
void error_msg()
  {
   printf("Error in semaphore\n");
  }
void error_msg_1()
  {
    printf("Enter greater than 0 for atleast one of the reader of writer");
  }
void * reader(void * arg)  
{  
    int c =(int)arg;  
    printf("reader %d is initialised\n",c);  //initialising reader
    sleep(1);  
    sem_wait(&mutex);  //lock 
    printf("Acquiring lock\n");
    readcount++;   //initially 0
    if(readcount==1)  
        sem_wait(&wsem);
        printf("Acquiring lock\n");  //lock
    sem_post(&mutex);  //release
        printf("Releasing lock\n");
    printf("reader %d is reading the value as %d\n",c,value);   //reading data value
    //multiple readers can read data value if it is not being written at that point
    sleep(1);  
    printf("reader %d has finished reading\n",c);  
    sem_wait(&mutex);  
    printf("Acquiring lock\n");
    readcount--;  
    if(readcount==0)  
        sem_post(&wsem); 
        printf("Releasing lock\n"); 
    sem_post(&mutex);  
    printf("Releasing lock\n");
}  
void * writer(void * arg)  
{  
    int c =(int)arg;  
    printf("writer %d is initialised\n",c);   //initialising writer
    sleep(1);  
    sem_wait(&wsem);  //lock
    printf("Acquiring lock\n");
    value++;
    printf("writer %d is writing the value as %d\n",c,value);  
    sleep(1);  
    printf("writer %d has finished writing\n",c);  
    sem_post(&wsem);
    printf("Releasing lock\n");  
}