#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>


int main(int argvnum, char **argv){
    // Apuntador a toda esa cadena
    char *path = argv[1];
    // Nuevo tipo de dato
    struct stat sb;
    // pasarle el path y la dirección de esa estructura
    stat(path, &sb);

    if(stat(path, &sb) == -1){
        printf("El archivo que escribiste no existe \n");
        return -1;
    }
    // puedo ver si este es un directorio
    if(S_ISDIR(sb.st_mode)){
        printf("Es un directorio \n");       
    }
    // puedo ver si este es un archivo
    if(S_ISREG(sb.st_mode)){
        printf("Es un archivo normal \n");
    }
    return 1;
}