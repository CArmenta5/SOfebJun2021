// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *argv[] = { "sh", 0 };

int
main(void)
{
  int pid, wpid;

  if(open("console", O_RDWR) < 0){
    mknod("console", 1, 1);
    open("console", O_RDWR);
  }
  dup(0);  // stdout
  dup(0);  // stderr

  for(;;){
	// 3) Corre perfectamente, pero ahora solo cambia el mensaje cuando comienza el sh por el nuevo mensaje"
    printf(1, "init: starting sh wow Supercalifragilisticexpialidocious\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
		// 1) En la primera modificación existe un loop infinito donde muestra el directorio y muestra todos los archivos que se pueden ejecutar, sale del wait.
		//2) En la segunda modificación el init intenta ejecutar el sh, el exec regresa el fail y el init manda un mensaje que dice que el exec sh ha fallado, el sistema operativo intenta buscar el programa y falla
      exec("sh", argv);
      // Si todo funciona esta parte del código no debería de ejecutarse
      printf(1, "init: exec sh failed\n");
      exit();
    }
    // en el proceso padre se está esperando por un cambio en el proceso hijo, si llega a fallar, despierta y crea otro 
    // durmiendo hasta que termina o muere
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
