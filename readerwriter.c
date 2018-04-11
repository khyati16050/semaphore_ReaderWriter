#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
void * reader(void *);  
void * writer (void *);  
sem_t data_lock;
sem_t reader_lock;  
int curr_reader = 0;  
int value = 0;

main()  
{  
    int i;
    int num_rthread=0; //number of reader threads
    int num_wthread; //number of writer threads
    sem_init(&data_lock,0,1);  //semaphore initialisation
    sem_init(&reader_lock,0,1); //semaphore initialisation
      if((sem_init(&data_lock,0,1)==-1)||(sem_init(&reader_lock,0,1)==-1))
        {
            error_msg();
        }
    pthread_t Readers_thr[100]; //reader thread array
    pthread_t Writer_thr[100]; //writer thread array
    printf("\nEnter number of Readers thread - ");
    scanf("%d",&num_rthread);
    printf("\nEnter number of Writers thread - ");
    scanf("%d",&num_wthread);
      if(&num_wthread == 0 && &num_rthread == 0 )
        {
          error_msg_1();
        }
    for(i=1;i <= num_rthread;i++) //creates number of reader threads
      {
      pthread_create(&Readers_thr[i],NULL,reader,(void *)i);
      }
    for(i=1;i <= num_wthread;i++) //creates number of writer threads
      {
      pthread_create(&Writer_thr[i],NULL,writer,(void *)i);
      }
    for(i=1;i <= num_rthread;i++) //joins reader threads
      {
      pthread_join(Readers_thr[i],NULL);
      }
    for(i=1;i <= num_wthread;i++) //joins writer threads
      {
      pthread_join(Writer_thr[i],NULL);
      }
    printf("-------------------------------------------------------------------------------\n");
    printf("Threads closed , process has finished\n\n");  //end 
    return 0;
}  
void error_msg()
  {
   printf("Error in initialising semaphore\n");
  }
void error_msg_1()
  {
    printf("Enter greater than 0 for atleast one of the reader of writer");
  }
 
void * reader(void * arg)  
{  
    int id =(int)arg;  
    printf("reader %d is initialised\n",id);  //initialising reader
    sleep(1);  
    sem_wait(&reader_lock);  //lock 
    printf("Acquiring lock\n");
    curr_reader++;   //initially 0
    if(curr_reader==1)  
        sem_wait(&data_lock);
        printf("Acquiring lock\n");  //lock
    sem_post(&reader_lock);  //release
        printf("Releasing lock\n");
    printf("reader %d is reading the value as %d\n",id,value);   //reading data value
    //multiple readers can read data value if it is not being written at that point
    sleep(1);  
    printf("reader %d has finished reading\n",id);  
    sem_wait(&reader_lock);  
    printf("Acquiring lock\n");
    curr_reader--;  
    if(curr_reader==0)  
        sem_post(&data_lock); //release lock
        printf("Releasing lock\n"); 
    sem_post(&reader_lock);  //release lock
    printf("Releasing lock\n");
}  
void * writer(void * arg)  
{  
    int id =(int)arg;  
    printf("writer %d is initialised\n",id);   //initialising writer
    sleep(1);  
    sem_wait(&data_lock);  //lock
    printf("Acquiring lock\n");
    value++;
    printf("writer %d is writing the value as %d\n",id,value);  //writing value of the writer
    sleep(1);  
    printf("writer %d has finished writing\n",id);  
    sem_post(&data_lock); //release lock
    printf("Releasing lock\n");  
}