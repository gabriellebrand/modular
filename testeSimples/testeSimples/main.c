#include <stdlib.h>
#include <stdio.h>
#include "grafo.h"
#include "string.h"

int comparacao(void *pValor1, void *pValor2){
	char *str1, *str2;
	str1 = (char*) pValor1;
	str2 = (char*) pValor2;
	return strcmp(str1, str2);
}

void excluir(void *pValor) {
	pValor = NULL;
}


int main () {
	GRA_tppGrafo grafo = NULL;
	GRA_tpCondRet ret;
	char * val;
	grafo = GRA_criarGrafo(excluir,comparacao);
	
	ret = GRA_criarVertice(grafo, "a@a.com", "a@a.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria vertice a - condRet: %d vert corrente: %s \n", ret, val);
	
	ret = GRA_criarVertice(grafo, "b@b.com", "b@b.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria vertice b - condRet: %d vert corrente: %s \n", ret, val);
	
	ret = GRA_criarVertice(grafo, "c@c.com", "c@c.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria vertice c - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarVertice(grafo, "d@d.com", "d@d.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria vertice d - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarVertice(grafo, "e@e.com", "e@e.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria vertice e - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarVertice(grafo, "b@b.com", "b@b.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\nrepete \ncria vertice b - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarAresta(grafo, "a@a.com", "b@b.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria aresta a-b - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarAresta(grafo, "a@a.com", "e@e.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria aresta a-e - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarAresta(grafo, "a@a.com", "d@d.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria aresta a-d - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarAresta(grafo, "a@a.com", "c@c.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria aresta a-c - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarAresta(grafo, "e@e.com", "d@d.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria aresta e-d - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarAresta(grafo, "e@e.com", "b@b.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria aresta b-e - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarAresta(grafo, "a@a.com", "c@c.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\nrepete: \ncria aresta a-c - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarAresta(grafo, "a@a.com", "x@x.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\nvertice inexistente:\ncria aresta a-x - condRet: %d vert corrente: %s \n", ret, val);


	ret = GRA_irVertice(grafo, "b@b.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\nir vertice b - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_irVertice(grafo, "e@e.com");
	ret = GRA_irVizinho(grafo, "a@a.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\nir vizinho a do vertice e - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_irVertice(grafo, "b@b.com");
	ret = GRA_irVizinho(grafo, "d@d.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\nvertices desconexos: \nir vizinho d do vertice b - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_excluirAresta(grafo, "a@a.com", "e@e.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\nexcluir aresta a-e - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_irVizinho(grafo, "a@a.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\nvertices desconexos: \nir vizinho a do vertice e - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_irVertice(grafo, "a@a.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\nir vertice a - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_excluirVertCorr(grafo);
	ret = GRA_irVertice(grafo, "a@a.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\nexcluiu vertice a: \nir vertice a - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_irVertice(grafo, "d@d.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\nir vertice d - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_irVizinho(grafo, "a@a.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\nvertices desconexos: \nir vizinho a do vertice d - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_destruirGrafo(grafo);
	printf("\n excluir grafo, ret = %d \n", ret);
	if (grafo == NULL) printf("\ngrafo nao existe mais"); 

	return 0;
}