#include <stdio.h> // 
#include <stdlib.h>

int main (int argc, char *argv[]){ //se pasan parametros, argv es doble apuntador, argc lee numero de argumentos, guarda los argumentos argv
int tokens, toknum=0;
	while(argv[toknum]!=NULL){
		toknum++;
	}
	for(tokens = 0; tokens < toknum; tokens++){
		if(argv[tokens][0] == '-')
			printf("opcion: %s\n", argv[tokens]+1);
		else
			printf("argumento %d: %s\n", tokens, argv[tokens]);
	}
	exit(0);
}
/*Este programa no lee nada, solo lee lo que se pase por linea de comando 
*/