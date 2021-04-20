#include <unistd.h>
#include <stdio.h>

int main(){
    // execl("/usr/bin/ls","ls","-l",NULL); esta llamada al sistema cambiaría todo nuestro código
    int fd[2];
    int pid;
    pipe(fd); // llama la sistema y crea la tuberia
    pid = fork(); // proceso clon creado como hijo
    if(pid == 0){
        // HIJO
        close(fd[1]); // cerramos la otra conexión que no vamos a utilizar en el proceso hijo (entrada)
        // fd[1] salida de mi piope
        dup2(fd[0],STDIN_FILENO); // la salida la conectamos con la entrada de tr
        
        // antes de exec hay que conectar entradas y salidas
        execl("/usr/bin/tr","tr","' '","-",NULL); // exec s
    }
    if(pid > 0){
        // PADRE
        close(fd[0]); // cerramos la otra conexión que no vamos a utilizar en el proceso padre (salida)
        // fd[1] salida de mi piope
        dup2(fd[1],STDOUT_FILENO); // la entrada la conectamos con la salida de cat        
        execl("/usr/bin/cat","cat",NULL);
    }
    printf("Esto no debe verse \n");
    return 0;
}