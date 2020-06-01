#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(){
	pid_t id_proceso;
	pid_t id_padre;
/*devuelve el ID de proceso (PID) del proceso de llamada. (Esto es
        a menudo utilizado por rutinas que generan nombres de archivos temporales únicos.)
*/
/*devuelve el ID de proceso del padre del proceso de llamada.
        Este será el ID del proceso que creó este proceso.
        utilizando fork (), o, si ese proceso ya ha terminado, el ID del proceso al que este proceso ha sido reparado 
		(ya sea init (1) o un proceso "secundario" definido a través de prctl (2) PR_SET_CHILD_SUBREAPER
        operación).
*/
	id_proceso = getpid();
	id_padre = getppid();

	printf("Identificador de proceso: %d\n", id_proceso);
	printf("Identificador de proceso padre: %d\n", id_padre);
}