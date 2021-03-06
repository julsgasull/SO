#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

//SEQUENCIAL

/*
	//Ejemplo esquema secuencial
	for (i=0;i<num_hijos;i++){
		pid=fork();
		if (pid==0) {
		// código hijo
		exit(0);// Solo si el hijo no muta y queremos que termine
	}
	// Esperamos a que termine antes de crear el siguiente
	waitpid(...); // los parámetros depende de lo que queramos
}	
*/

void error_y_exit(char *s, int error) {
	perror(s);
	exit(error);
}

int main(int argc, char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		int ret = fork();
		char s[50];
		switch (ret) {
			case 0:
				sprintf(s, "Soy el proceso HIJO: %d de %s\n", getpid(), argv[i]);
				write(1, s, strlen(s));
				exit(0);
				break;
			case -1:
				sprintf(s,"Ha fallado el fork del proceso: %d\n", getpid());
				error_y_exit(s, 1);
				break;
			default:
				waitpid(-1, NULL, 0);
				break;
		}
	}
}
