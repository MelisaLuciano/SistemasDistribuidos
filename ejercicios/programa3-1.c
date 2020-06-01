#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(){
	uid_t getuid(void);
	printf ("Identificador de usuario:  %d\n", getuid());
}