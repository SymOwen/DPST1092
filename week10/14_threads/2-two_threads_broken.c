/*

 simple example which launches two threads of execution
 but demonstrates the perils of accessing non-local variables
 from a thread

$ gcc -pthread two_threads_broken.c -o two_threads_broken
$ ./two_threads_broken|more
Hello this is thread 2: i=0
Hello this is thread 2: i=1
Hello this is thread 2: i=2
Hello this is thread 2: i=3
Hello this is thread 2: i=4
Hello this is thread 2: i=5
Hello this is thread 2: i=6
Hello this is thread 2: i=7
Hello this is thread 2: i=8
Hello this is thread 2: i=9
Hello this is thread 2: i=0
Hello this is thread 2: i=1
Hello this is thread 2: i=2
Hello this is thread 2: i=3
Hello this is thread 2: i=4
Hello this is thread 2: i=5
Hello this is thread 2: i=6
Hello this is thread 2: i=7
Hello this is thread 2: i=8
Hello this is thread 2: i=9
$...

*/

#include <stdio.h>
#include <pthread.h>

void *run_thread(void *argument) {
    int *p = argument;

    for (int i = 0; i < 10; i++) {

        // variable thread number will probably have changed in main
        // before execution reaches here
        printf("Hello this is thread %d: i=%d\n",  *p, i);

    }

    return NULL;
}

int main(void) {
    pthread_t thread_id1;
    int thread_number = 1;
    pthread_create(&thread_id1, NULL, run_thread, &thread_number);

    thread_number = 2;
    pthread_t thread_id2;
    pthread_create(&thread_id2, NULL, run_thread, &thread_number);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    return 0;
}