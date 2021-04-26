#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUMTHREADS 10000 //definimos cantidad de hilos
int total;
pthread_mutex_t lock; // pa que lo vean todos los hilos

// función para ejecutar los hilos
void *suma(void *datos) {  // por default recibe un apuntador génerico y regresa un apuntador génerico
    printf("Hello world desde un hilo %d\n", *(int *)datos); // apuntador de entero, y saco su valor, no queremos la dirección aquí
    // inicio región crítica
    pthread_mutex_lock(&lock);
    total += 100;
    pthread_mutex_unlock(&lock);
    // termina región crítica
    pthread_exit(NULL); // puedo regresar el valor que tenga en su parametro, lo puedo regresar al hilo principal a traves de otra variable que puede cacahr con el mismo exit
}

int main() { 
    pthread_t myThreads[NUMTHREADS]; // en esta variable guardo la info de ese hilo
    int tIds[NUMTHREADS]; // arreglo de variables que no cambien
    pthread_mutex_init(&lock, NULL); // lo inicializamos
    pthread_mutex_unlock(&lock); // garantizamos que se encuentre abierto
    total = 0;
    for(int i = 0; i< NUMTHREADS; i++){ // cuantás varias i exites: 1, todos los hilos tienen la misma i y asumen que su misma i, pero esa la cambia el hilo principal y pone el valor de esa variable
         tIds[i] = i; // contexto nuevo para i
         // dirección del thread donde guardo info del hilo, atributos del hilo (tamaño del stack), función a ejecutar y valor a pasar a esa función
         pthread_create(&myThreads[i], NULL,suma, &tIds[i]); // parecida al fork, pero creamos hilos, paso dirección por referencia
    }
    printf("%d\n",total); // no hay garantia de que se acaben los threads

    for(int i = 0; i< NUMTHREADS; i++){
         pthread_join(myThreads[i], NULL); // espera a que el hilo que se le pasa por parametro termina, si no acaba espera
    }
    printf("%d\n",total); // ya se han acabado los hilos

    pthread_exit(NULL); //  este hilo se quedará dormido en esta función hasta que todos los hilos ejecuten este  pthread_exit el hilo principal espera q que se terminen los demás
}
