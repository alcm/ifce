#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "sync_communication.h"
#include "utils.h"

void run_mgr(void)
{
    int vector[12] = {[0 ... 11] = 0};
    int curr_idx = 0, id = 0, msg = 0;

    while (1) {	
        int chann = alt_wait();
		
        receive_sync(&vector[curr_idx++], chann);	
        if (curr_idx == 12) {
            for (int i = 0; i < 12; i++) {
                findBytes(vector[i], &msg , &id);

                send_sync(&msg, id);
            }

            curr_idx = 0;
        }
    }
}

void * thread_a(void * args)
{
    const int id = 4;
    const int value = 10;
    const int msg = parseValue(value, id);

    while (1) {
        usleep(2000000);
        send_sync(&msg, 0);
    }	
}

void * thread_b(void * args)
{
    const int id = 5;
    const int value = 20;
    const int msg = parseValue(value, id);

    while (1) {
        usleep(2000000);
        send_sync(&msg, 1);
    }
}

void * thread_c(void * args)
{
    const int id = 6;
    const int value = 30;
    const int msg = parseValue(value, id);

    while (1) {
        usleep(2000000);
        send_sync(&msg, 2);
    }
}

void * thread_d(void * args)
{
    const int id = 7;
    const int value = 40;	
    const int msg = parseValue(value, id);

    while (1) {
        usleep(2000000);
        send_sync(&msg, 3);
    }
}

void * thread_e(void * args)
{
    int msg = 0;

    while (1) {
        receive_sync(&msg, 4);
        printf("[Thread e] Valor recebido: %d\n", msg);
    }
}

void * thread_f(void * args)
{
    int msg = 0;

    while (1) {
        receive_sync(&msg, 5);
        printf("[Thread f] Valor recebido: %d\n", msg);
    }
}

void * thread_g(void * args)
{
    int msg = 0;

    while (1) {
        receive_sync(&msg, 6);
        printf("[Thread g] Valor recebido: %d\n", msg);
    }
}

void * thread_h(void * args)
{
    int msg = 0;

    while (1) {
        receive_sync(&msg, 7);
        printf("[Thread h] Valor recebido: %d\n", msg);
    }
}

void start_threads(void)
{
    pthread_t tid;

    pthread_create(&tid, NULL, thread_a, NULL);
    pthread_create(&tid, NULL, thread_b, NULL);
    pthread_create(&tid, NULL, thread_c, NULL);
    pthread_create(&tid, NULL, thread_d, NULL);
    pthread_create(&tid, NULL, thread_e, NULL);
    pthread_create(&tid, NULL, thread_f, NULL);
    pthread_create(&tid, NULL, thread_g, NULL);
    pthread_create(&tid, NULL, thread_h, NULL);
}

int main(void)
{
    start_threads();
    run_mgr();
}
