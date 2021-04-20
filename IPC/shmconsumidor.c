
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

// definición deltipo de dato m
// 18 y 20 solo se dedican a la comunicación 
typedef struct m {
    char status;
    int data[4];
} MyData;

// podemos usar MyData para el tipo de dato m (alias)
int main(){
    MyData *datos;
    int key = 27;
    // IPC_CREATE, si no existe crealo | (permisos) -> 0666 lectura y escritura para todo
    int shmId = shmget(key,sizeof(MyData), IPC_CREAT | 0666); // este shmId identificará a ese bloque
    //dirección en donde quiero que empiece (al inicio del bloque),
    datos = (MyData *) shmat(shmId, NULL, 0); // regresa void*, pero debemos castearlos al tipo de dato en el cual pueda utilizarlo
    
    while(datos->status != 'r'){
        sleep(1);
    }
    printf("Los datos son: %d %d %d %d \n",
            datos->data[0],
            datos->data[1],
            datos->data[2],
            datos->data[3]);
    datos->status = 't';
    return 0;
}
