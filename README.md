We take the input of the number of readers and writers the user wants to specify.We initialise semaphores using sem_init function call with initial value being 1 for the semaphore. Next we initialise a reader and writer array of size 100 which creates threads for reader and writer according to the user input by pthread_create function call. The reader and writer functions are then called. The following are their executions :-
	    WRITER
print the number/id of the writer trying to access database
lock the database so that writer can modify it by using sem_wait. After this increment the value to be written and print it
Release the lock using sem_post after the writer has finished writing so that the database is again open to all other members.
            READER
print the number/id of the reader trying to access database
increment curr_reader by 1 so as to ensure that only one reader is accessing the particular element.
acquire lock so that no updates can be made by the writer while reader is reading using sem_wait
Then we print the value of data read.We release the lock held by the reader using sem_post.We acquire the lock again and decrement the curr_reader.
if 0,locks on database and reader are released.
The threads are then joined together and semaphores are destroyed. the process terminates.
-------------------------------------------------

Compilation
-------------------------------------------------
"make all" can be used to compile the program. (gcc -o rw readerwriter.c -w -lpthread)
it creates the binary as rw
run ./rw and continue the input
"make clean" will remove the binary using rm rw
-------------------------------------------------

Input
-------------------------------------------------
1.) input the number of readers needed
2.) input the number of writers needed
-------------------------------------------------

Output
-------------------------------------------------
Prints the no. of reader/writer accessing/modifying data
prints whether lock has been acquired or released
prints the id of the reader/writer after finishing the work
Ends by printing "Threads closed , process has finished"
-------------------------------------------------

Error handling
-------------------------------------------------
1.) if sem_init()==-1 then prints Error in initialising semaphore
2.) if num_reader and num_writer both are 0 ; the process immediatelly terminates by displaying following two messages:-
	Enter greater than 0 for atleast one of the reader of writer
	Threads closed , process has finished
3.) if sem_destroy()==-1 then prints error in destroying semaphore
--------------------------------------------------

Reference
--------------------------------------------------
http://writeulearn.com/reader-writer-problem-solved-using-semaphore/
---------------------------------------------------
