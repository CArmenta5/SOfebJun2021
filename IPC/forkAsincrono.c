#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void signalHandler(int sig){
    printf("Recibi segnal %d\n", sig);
    int pidHijoTermino = wait(NULL);
    printf("Mi Hijo terminó %d \n",pidHijoTermino);

}
int main(){
    //signal(17,signalHandler);
    int pid = fork(); // guardamos el id del proceso
    int pidHijoTermino;
    if(pid == 0){
        //Proceso hijo
        printf("Soy el proceso hijo\n");
    }else{
        
        printf ("Soy el proceso padre y mi hijo es %d\n",pid);
        pidHijoTermino = wait(NULL); //Aseguro de ya no tener a los zombies de manera asincrona, ya que el proceso padre se espera a que su hijo termine
        // espera por cualquier hijo
        // linea 2 espera a que el hijo termine
        printf("Mi hijo terminó %d\n",pidHijoTermino);
        
    }
    printf("Terminando\n");
    return 0;
}