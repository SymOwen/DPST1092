/*

 simple example demonstrating unsafe access to a global variable from threads

$ gcc -O3 -pthread bank_account_broken.c -o bank_account_broken
$ ./bank_account_broken
Andrew's bank account has $108829
$

*/
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <pthread.h>
#include <time.h>

int bank_account = 0;

// add $1 to Andrew's bank account 100,000 times
void *add_100000(void *argument) {

    for (int i = 0; i < 100000; i++) {

        // execution may switch threads in middle of assignment
        // between load of variable value
        // and store of new variable value
        // changes other thread makes to variable will be lost
        nanosleep(&(struct timespec){.tv_nsec = 1}, NULL);
        bank_account = bank_account + 1;
    }

    return NULL;
}

int main(void) {
    //create two threads performing  the same task

    pthread_t thread_id1;
    pthread_create(&thread_id1, NULL, add_100000, NULL);

    pthread_t thread_id2;
    pthread_create(&thread_id2, NULL, add_100000, NULL);

    // wait for the 2 threads to finish
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    // will probably be much less than $200000
    printf("Andrew's bank account has $%d\n", bank_account);
    return 0;
}