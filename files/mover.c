#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

//Oscar Gutiérrez Godoy A01635648
//Oscar Fernandez Moreno A07013362
//Carlos Raúl Armenta Pérez A01635371

int main(int argvnum, char **argv){
    char *pathOriginal = argv[1];
    char *pathNuevo = argv[2];
    struct stat sb;
    struct stat sb2;

    if(stat(pathOriginal, &sb) == -1){
        printf("El primer archivo que escribiste no existe \n");
        return -1;
    }

    if(stat(pathNuevo, &sb2) == -1){
        //  ./mover arch1.txt arch2.txt  // renombrar Si arch1.txt exista y arch2.txt no existe lo va a renombrar
        link(pathOriginal, pathNuevo);
        unlink(pathOriginal);
    }else if(S_ISDIR(sb2.st_mode)){
        // ./mover arch1.txt arch2.txt // Si arch2.txt existe me manda un mensaje de error
        char pathDir[100];
        sprintf(pathDir, "%s/%s",pathNuevo,pathOriginal);
        printf("%s \n",pathDir);
        link(pathOriginal,pathDir);
        unlink(pathOriginal);
    }else{
        // ./mover arch1.txt dir2 // Si dir2 existe y es un directorio mueve arch1.txt dentro de dir2
        printf("El segundo archivo ya existe \n");
        return -1;
    }



    return 1;
}