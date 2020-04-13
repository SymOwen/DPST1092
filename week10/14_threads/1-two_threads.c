/*

 simple example which launches two threads of execution

$ gcc -pthread two_threads.c -o two_threads
$ ./two_threads|more
Hello this is thread #1 i=0
Hello this is thread #1 i=1
Hello this is thread #1 i=2
Hello this is thread #1 i=3
Hello this is thread #1 i=4
Hello this is thread #2 i=0
Hello this is thread #2 i=1
...

*/

#include <stdio.h>
#include <pthread.h>

// this function is called to start thread execution
// it can be given any pointer as argument (int *) in this example

void *run_thread(void *argument) {
    int *p = argument;

    for (int i = 0; i < 10; i++) {
        printf("Hello this is thread #%d: i=%d\n",  *p, i);
    }

    // a thread finishes when the function returns or  thread_exit is called
    // a pointer of any type can be returned
    // this can be obtained via thread_join's 2nd argument
    return NULL;
}

int main(void) {
    //create two threads performing almost the same task

    pthread_t thread_id1;
    int thread_number1 = 1;
    pthread_create(&thread_id1, NULL, run_thread, &thread_number1);

    int thread_number2 = 2;
    pthread_t thread_id2;
    pthread_create(&thread_id2, NULL, run_thread, &thread_number2);

    // wait for the 2 threads to finish
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    return 0;
}