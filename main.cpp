/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: debian
 *
 * Created on 8. Dezember 2017, 16:27
 */

#include <pthread.h>
#include <cstdlib>
#include <iostream>
#include <semaphore.h>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>
#include <vector>

using namespace std;

#define NUM_OF_THREADS_WRITER 2
#define NUM_OF_THREADS_READER 10
#define ARRAYSIZE 2
#define NUM_OF_THREADS (NUM_OF_THREADS_WRITER + NUM_OF_THREADS_READER)

int array[ARRAYSIZE];


pthread_mutex_t writer_lock;
pthread_mutex_t reader_lock;
sem_t active_reader;
sem_t active_writer;
bool run = true;
bool test[ARRAYSIZE];


void sigint_handler(int signum) {
    std::cerr << "Pressed C" << signum << std::endl;
    run = false;
}

void sigstop_handler(int signum) {
    std::cerr << "Pressed Z: " << signum << std::endl;
    run = false;
}

bool Check(int index){
        if (test[index]){
            test[index] = false;
            return true;
        }
        cout << "WAIT" << endl;
        return false;
}

void* write(void* args) {
    //Writer Threads    
    while(run){
        
        sleep(1);
    
    pthread_mutex_lock(&writer_lock); //lock
    for (int i = 0;i < ARRAYSIZE; i++)
    {
        int sem_wait(sem_t * active_reader);
    }
    for (int i = 0; i < ARRAYSIZE; i++) {
        int random_number = rand() % 42;
        array[i] = random_number;
        cout << "Index: "<< i << " Random: " << random_number << endl;
    }
    for (int i = 0;i < ARRAYSIZE; i++)
    {
        int sem_post(sem_t * active_reader);
    }
    pthread_mutex_unlock(&writer_lock); //unlock
    
    }
}

void* read(void* args) {
    //Reader Threads
    while (run) {
        
        //sleep(1);
        
    int sem_wait(sem_t * active_reader);
    int sem_wait(sem_t * active_writer);
    pthread_mutex_lock(&reader_lock); //lock
    int index = rand() % ARRAYSIZE;
    if (Check(index)){
        sleep(1);
    int val = array[index];
    cout << "Read from index: " << index << " Value: " << val << " Thread: " << args <<endl;
    test[index] = true;
    }
    int sem_post(sem_t * active_reader);
    int sem_post(sem_t * active_writer);
    pthread_mutex_unlock(&reader_lock); //unlock
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    signal(SIGINT, sigint_handler);
    signal(SIGSTOP, sigstop_handler);
    writer_lock = PTHREAD_MUTEX_INITIALIZER;
    reader_lock = PTHREAD_MUTEX_INITIALIZER;
    sem_init(&active_reader, 0, ARRAYSIZE);
    sem_init(&active_writer, 0, 1);
    pthread_t threads [NUM_OF_THREADS];

    srand(time(NULL));
    
    for (int i = 0; i < ARRAYSIZE; i++){
        test[i]=true;
    }

    //Writer Threads
    for (int i = 0; i < NUM_OF_THREADS_WRITER; i++) {
        int result_code = pthread_create(&threads[i], NULL, write, NULL);
    }

    //Reader Threads
    for (int i = NUM_OF_THREADS_WRITER; i < NUM_OF_THREADS; i++) {
        int result_code = pthread_create(&threads[i], NULL, read, (void*)i - NUM_OF_THREADS_WRITER);
    }

    //Wait for Threads
    for (int i = 0; i < NUM_OF_THREADS; i++) {
        int result_code = pthread_join(threads[i], NULL);
        cout << "Thread: " << i << " finished" << endl;
    }

    return 0;
}