#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "string.h"
#include "perfil.h"

int main () {
	GRA_tppGrafo grafo = NULL;
	GRA_tpCondRet ret;
	PER_tppPerfil perfil1;
	char * val;
	grafo = GRA_criarGrafo(PER_DestruirPerfil,PER_compararPerfil);
	perfil1 = PER_CriarPerfil("perfil", "p@p.com", "rj", 1);
	
	printf("compara: %d \n", PER_compararPerfil(perfil1, "p@p.com"));
	
	
	//ret = GRA_criarVertice(grafo, "a@a.com", "a@a.com");
	//val = (char*) GRA_obterValor(grafo);
	//printf("\ncria vertice a - condRet: %d vert corrente: %s \n", ret, val);

	return 0;
}