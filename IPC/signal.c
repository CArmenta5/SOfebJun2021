#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int varGlobal = 0;

void signalHandler(int sig){
    // el SO lo saca para que ejecute el código que tiene que ver con la señal
  printf("Recibi segnal %d\n", sig);
	varGlobal = 1;
}

int main(){
    // cuando registramos una función solo pasamos el nombre de la función
    // cuando se registre luego se encargará de ejecutarla con la señal que recibió
  signal(2, signalHandler); // decirle para que señal voy a recibir, cuando reciba la señal 15 ejecuta signalhandler
  // signalHandler no lleva en este caso parametros, aquí solo lo estoy registrando, no significa que lo esté ejecutando en ese momento
  // while para darle chance de que reciba la señal jeje

  while(1){
    printf("Trabajando\n");
    if(varGlobal == 1){
		break;
	}
    // sleep para que no se trabe 
	sleep(1);
  }
  printf("Ya voy a terminar \n");
  return 0;
}