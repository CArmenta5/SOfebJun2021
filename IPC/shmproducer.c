#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

typedef struct m {
    char status;
    int data[4];
} MyData;

// n not ready, coordinación con el consumidor para que se espere
// t ya se han leido los datos
// r ready, ya escribí algo para que alguien más los tome

int main(){
    MyData *datos; // apuntador de tipo MyData
    int key = 27;
    int shmId = shmget(key,sizeof(MyData), IPC_CREAT | 0666); // leemos
    datos = (MyData *)shmat(shmId, NULL, 0); // nos conectamos

    datos->status = 'n'; // variable de coordinación con el consumidor
    datos->data[0] = 40; 
    datos->data[1] = 30;
    datos->data[2] = 10;
    datos->data[3] = 50;
    datos->status = 'r';
    // checará que ya leyó los datos cuando sea igual t
    while(datos->status != 't'){ 
        sleep(1);
    }
    printf("Los datos se consumieron \n");
    return 0;
}