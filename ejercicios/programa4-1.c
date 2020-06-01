#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

 int main(void){
	
	pid_t pid;
	int i=0, estado;

	pid = fork();
	switch(pid) {
		case -1: /*error de fork*/
			perror("Error en el fork");
			break;
		case 0: /*proceso hijo*/
			printf("Soy el hijo: PID %d; PPID = %d i = %d\n", getpid(), getppid(), ++i);
			exit(0);
			break;
		default: /*proceso padre */
			printf("Soy el padre: PID %d; PPID = %d i = %d\n", getpid(), getppid(), --i);
			wait(&estado);
			exit(0);
	}
}
/*fork: crea un nuevo proceso, al ejecutar se tienen dos procesos idénticos
proceso padre(original) e hijo, 
Para reconocer quién es quién fork devuelve un valor distinto al proceso padre
*/