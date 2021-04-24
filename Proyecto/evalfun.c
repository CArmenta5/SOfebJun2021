
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

void signalHandler(int sig){
    exit(0);

}

int main()
{
   
    signal(2,signalHandler);
    // from parent to child, parent write, child read
    int pp2c[2];
    // from child to parent, child write, parent read
    int pc2p[2];

    pipe(pp2c);
    pipe(pc2p);

    switch (fork()) {
        // fork failed
        case -1:
            break;
        // child
        case 0: 
            // connect pp2c to stdin
            close(pp2c[1]);
            dup2(pp2c[0], STDIN_FILENO);
            close(pp2c[0]);
            // connect pc2p to stdout
            close(pc2p[0]);
            dup2(pc2p[1], STDOUT_FILENO);
            close(pc2p[1]);

            // exec "rev" to reverse lines
            execlp("/usr/bin/bc","bc","-l", (char*) NULL);
          break;
        // parent
        default:
            // close unnecessary pipes       
            close(pp2c[0]);
            close(pc2p[1]);
            // open pipes as stream
           // this is need to use fprintf/scanf to write/read from the pipes
            FILE *out = fdopen(pp2c[1], "w");
            FILE *in = fdopen(pc2p[0], "r");

            char funcion[1024];
              
            char str[80]; // String función
            float ini, fin, puntos, sum,rango;
              float average;
                float salidaDato;
            while(1){
            /******/
                

                scanf("%s", funcion); // leemos la función a evaluar
                while((fgetc(stdin)) != '\n');
                fflush(stdout);
                scanf("%f %f %f", &ini, &fin ,&puntos); // leemos los 3 puntos
                while((fgetc(stdin)) != '\n');
                fflush(stdout);

                rango = (fin-ini) / puntos;
              
                
               
                for(float i = rango; i <= fin; i+=rango){
                    // redirect input to child process
                    
                    fprintf(out, "x=%f\n",i); // escribimos el primer punto a evaluar
                    fprintf(out, "%s\n", funcion); // escribimos la función a evaluar
                    fflush(out);
                   
                    // read child process output
                    fscanf(in, "%f", &salidaDato);
                        fflush(in);
                        sum += salidaDato;
                    
                   
                    
                } 
                average = sum/puntos;
                printf("%f\n", average);
                fflush(stdout);
                sum = 0;
                
                
            }
           	fclose(out);
			fclose(in);

            // call wait on finished child
            wait(NULL);
            break;
    }

    return 0;
}
