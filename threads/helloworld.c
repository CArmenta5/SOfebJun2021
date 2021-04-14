#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUMTHREADS 10000
int total;
pthread_mutex_t lock;
void *suma(void *datos) {  // paso apuntador, pasar dato independiente, si es dirección vairbale compartida
    printf("Hello world desde un hilo %d\n", *(int *)datos); //contapuntador de entero
    pthread_mutex_lock(&lock);
    total+=100;
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

int main() { 
    pthread_t myThreads[NUMTHREADS];
    int tIds[NUMTHREADS];
    pthread_mutex_init(&lock, NULL);
    pthread_mutex_unlock(&lock);
    total = 0;
    for(int i = 0; i< NUMTHREADS; i++){ // cuantás varias i exites: 1, todos los hilos tienen la misma i y asumen que su misma i, pero esa la cambia el hilo principal y pone el valor de esa variable
         tIds[i] = i; // contexto nuevo para i
         pthread_create(&myThreads[i], NULL,suma, &tIds[i]); // paso dirección por referencia
         //     for(long i = 0; i< NUMTHREADS; i++){ pthread_create(&myThreads[i],NULL,printHelloWorld, (void *) i);  tratala como un apuntado 
    }
       printf("%d\n",total); // no hay garantia de que se acaben los threads

    for(int i = 0; i< NUMTHREADS; i++){
         pthread_join(myThreads[i], NULL); // espera a que el hilo que se le pasa por parametro termina, si no acaba espera
    }
   printf("%d\n",total); // ya se han acabado los hilos

    pthread_exit(NULL); // hace que el hilo principal se mate jajaj xd
}
