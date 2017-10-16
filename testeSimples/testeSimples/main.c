#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "string.h"
#include "perfil.h"

int main () {
	GRA_tppGrafo grafo = NULL;
	GRA_tpCondRet ret;
	PER_tppPerfil per, perfil1, perfil2;
	char * val, *email;

	grafo = GRA_criarGrafo(PER_DestruirPerfil,PER_compararPerfil);
	perfil1 = PER_CriarPerfil("perfil", "p@p.com", "rj", 1);
	//email = (perfil1)->email;
	printf("\ncompara: %d \n", PER_compararPerfil(perfil1, "p@p.com"));

	GRA_criarVertice(grafo, perfil1, "p@p.com");
	per = (PER_tppPerfil) GRA_obterValor(grafo);
	printf("\nvertice corrente id: %s \n", PER_recuperaEmail(per));
	
	ret = GRA_irVertice(grafo, PER_recuperaEmail(perfil1));
	per = (PER_tppPerfil) GRA_obterValor(grafo);
	printf("\nir vertice p@p.com - condRet: %d vert corrente: %s \n", ret, PER_recuperaEmail(per));

	ret = GRA_destruirGrafo(&grafo);
	ret = GRA_irVertice(grafo, PER_recuperaEmail(perfil1));
	per = (PER_tppPerfil) GRA_obterValor(grafo);
	if (per == NULL) printf("nulo!! \n");
	printf("\nir vertice p@p.com - condRet: %d vert corrente: %s\n", ret, PER_recuperaEmail(per));

	printf("endereco do grafo: %x \n", grafo);
	//ret = GRA_destruirGrafo(&grafo);
	//printf("\nENDEREÇO: %x", grafo);
	//ret = GRA_criarVertice(grafo, "a@a.com", "a@a.com");
	//val = (char*) GRA_obterValor(grafo);
	//printf("\ncria vertice a - condRet: %d vert corrente: %s \n", ret, val);
	
	printf("\nCRIA VERTICE DE NOVO \n");
	grafo = GRA_criarGrafo(PER_DestruirPerfil,PER_compararPerfil);
	perfil1 = PER_CriarPerfil("perfil", "p@p.com", "rj", 1);
	ret = GRA_criarVertice(grafo, perfil1, PER_recuperaEmail(perfil1));
	ret = GRA_irVertice(grafo, PER_recuperaEmail(perfil1));
	printf("\nir vertice p@p e tentar ir vertice: %d \n", ret);
	
	ret = GRA_excluirVertCorr(grafo);
	ret = GRA_irVertice(grafo, PER_recuperaEmail(perfil1));
	printf("\nexcluir vertice corrente e tentar ir vertice: %d\n", ret);
	
	perfil1 = PER_CriarPerfil("perfil", "p@p.com", "rj", 1);
	ret = GRA_criarVertice(grafo, perfil1, PER_recuperaEmail(perfil1)); 
	per = (PER_tppPerfil)GRA_obterValor(grafo);
	printf("\nvertice corrente: %s\n", PER_recuperaEmail(per));
	ret = GRA_criarAresta(grafo, PER_recuperaEmail(perfil1), PER_recuperaEmail(perfil1));
	printf("\ntenta criar aresta consigo mesmo: %d\n", ret);

	perfil2 = PER_CriarPerfil("nome", "q@q.com", "rj", 2);
	ret = GRA_criarVertice(grafo, perfil2, "q@q.com");
	ret = GRA_criarAresta(grafo, PER_recuperaEmail(perfil1), PER_recuperaEmail(perfil2));
	printf("\ncriar aresta com vertice q-p condRet: %d\n", ret);
	
	per = (PER_tppPerfil) GRA_obterValor(grafo);
	//GRA_irVertice(grafo, "p@p.com");
	ret = GRA_irVizinho(grafo, "p@p.com");
	printf("\nfoi no vizinho p do vertice q: %s %d\n", PER_recuperaEmail(per), ret);

	ret = GRA_irVertice(grafo, "p@p.com");
	printf("\nir vertice p %d\n", ret);
	per = (PER_tppPerfil) GRA_obterValor(grafo);

	ret = GRA_irVertice(grafo, "q@q.com");
	ret = GRA_excluirVertCorr(grafo);
	ret = GRA_irVertice(grafo, "p@p.com");
	ret = GRA_irVizinho(grafo, "q@q.com");
	printf("\nfoi no vizinho q do vertice p: %s %d\n", PER_recuperaEmail(per), ret);
	//printf("ir vertice p@p.com - condRet: %d vert corrente: %s\n", ret, PER_recuperaEmail(per));
	//email = (perfil1)->email;
	
	//printf("compara: %d %s \n", PER_compararPerfil(perfil1, "p@p.com"), PER_recuperaEmail(perfil1));

	return 0;
}