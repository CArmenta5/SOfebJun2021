#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_RECORDS 20

int buffer[MAX_RECORDS]; // buffer global que compartiran ambos hilos
sem_t empty; // semaforo
sem_t fill;

//función de ese tipo void * referencia pura, podemos recibir cualquier cosa
void *producer(void *d) {  // prototipo de pthread
    int pos = 0;
    while(1){
        sem_wait(&empty); // decrementar empty
        buffer[pos] = pos;
        pos = ((pos+1)%MAX_RECORDS);
        sleep(1); // tiempo para producir el valor
        sem_post(&fill); // incrementar fill
    }  
        pthread_exit(NULL);

}
void *consumer(void *d) {  
    int pos = 0;
    int valor;
    while(1){
        sem_wait(&fill); // decrementar empty
        valor = buffer[pos];
        pos = ((pos+1)%MAX_RECORDS);
        sleep(2); // tiempo para producir el valor
        printf("valor = %d \n", valor);
        sem_post(&empty); // incrementar fill
    }  
    pthread_exit(NULL);
}

int main(){
    //semáforo, 0-entre hilos, 1-entre procesos
    /*Inicializo semaforos*/
    // semaforo a inicializar, tipo de semaforo, records vacios
    sem_init(&empty,0,MAX_RECORDS);  
    sem_init(&fill,0,0);
    
    pthread_t producerThread, consumerThread;
    /*Creación de hilos*/
    pthread_create(&producerThread, NULL, producer,NULL ); 
    pthread_create(&consumerThread, NULL, consumer,NULL );

    pthread_exit(NULL);
}