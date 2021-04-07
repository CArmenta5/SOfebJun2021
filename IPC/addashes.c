#include <unistd.h>
#include <stdio.h>

int main(){
    //int pid =fork()
   // execl("/usr/bin/tr","ls","-l",NULL);
    int fd[2];
    int pid;
    pipe(fd);
    pid=fork(); //Dos procesos
    if(pid==0){
        close(fd[1]); //cerramos la parte padre
        //fd[1] salida de mi piope
        dup2(fd[0],STDIN_FILENO);//conectamos salida de cat a fd 0
        
        execl("/usr/bin/tr","tr","' '","-",NULL);
    }
    if(pid > 0){
        //padre
        close(fd[0]); //cerramos la parte padre
        //fd[1] salida de mi piope
        dup2(fd[1],STDOUT_FILENO);//conectamos salida de cat a fd 0
        
        execl("/usr/bin/cat","cat",NULL);
    }
    printf("Esto no debe verse \n");
    return 0;
}