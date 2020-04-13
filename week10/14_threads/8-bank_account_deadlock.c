// simple example which launches two threads of execution
// which increment a global variable

#include <stdio.h>
#include <pthread.h>

int andrews_bank_account1 = 100;
pthread_mutex_t bank_account1_lock = PTHREAD_MUTEX_INITIALIZER;

int andrews_bank_account2 = 200;
pthread_mutex_t bank_account2_lock = PTHREAD_MUTEX_INITIALIZER;

// swap values between Andrew's two bank account 100,000 times
void *swap1(void *argument) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&bank_account1_lock);
        pthread_mutex_lock(&bank_account2_lock);

        int tmp = andrews_bank_account1;
        andrews_bank_account1 = andrews_bank_account2;
        andrews_bank_account2 = tmp;

        pthread_mutex_unlock(&bank_account2_lock);
        pthread_mutex_unlock(&bank_account1_lock);

    }

    return NULL;
}

// swap values between Andrew's two bank account 100,000 times
void *swap2(void *argument) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&bank_account2_lock);
        pthread_mutex_lock(&bank_account1_lock);

        int tmp = andrews_bank_account1;
        andrews_bank_account1 = andrews_bank_account2;
        andrews_bank_account2 = tmp;

        pthread_mutex_unlock(&bank_account1_lock);
        pthread_mutex_unlock(&bank_account2_lock);

    }

    return NULL;
}
int main(void) {
    //create two threads performing almost the same task

    pthread_t thread_id1;
    pthread_create(&thread_id1, NULL, swap1, NULL);

    pthread_t thread_id2;
    pthread_create(&thread_id2, NULL, swap2, NULL);

    // threads will probably never finish
    // deadlock will likely likely core
    // with one thread holding  bank_account1_lock
    // and waiting for bank_account2_lock
    // and the other  thread holding  bank_account2_lock
    // and waiting for bank_account1_lock

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    return 0;
}