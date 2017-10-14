#include <stdlib.h>
#include <stdio.h>
#include "LISTA.h"
#include "string.h"

/*#define GRAFO_OWN
#include "GRAFO.h"
#undef GRAFO_OWN
*/
/****** PROVISORIO ATE CRIAR O .H: TYPEDEF DO ENUM ******/
 typedef enum {
     
 /* 0 */ GRA_CondRetOK ,
               /* Concluiu corretamente */

 /* 1 */ GRA_CondRetGrafoVazio ,
               /* O grafo n�o cont�m v�rtices */

 /* 2 */ GRA_CondRetFimDoGrafo ,
               /* Foi atingido o fim do grafo */

 /* 3 */ GRA_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

 /* 4 */ GRA_CondRetFaltouMemoria,
               /* Faltou mem�ria ao tentar criar um v�rtice do grafo */
       
 /* 5 */ GRA_CondRetGrafoNaoExiste,
         /* Grafo n�o existe ao inserir */

 /* 6 */ GRA_CondRetNaoCriouOrigem,
         /* N�o criou vertice origem */
     
 /* 7 */ GRA_CondRetNaoPossuiAresta,
         /* N�o possui aresta para o vertice */

 /* 8 */ GRA_CondRetVerticeNaoExiste,
        /* Vertice nao Existe */
     
 /* 9 */ GRA_CondRetArestaNaoExiste,
        /* N�o possui arestas */

 /* 10 */ GRA_CondRetArestaJaExiste
        /* Ja possui essa aresta */,

 /* 11 */ GRA_CondRetVerticeJaExiste,
        /* Vertice ja Existe */

 /* 12 */ GRA_CondRetArestaIlegal,
        /* Aresta para o proprio v�rtice */

 /* 13 */  GRA_CondRetValorNulo
        /* Ponteiro nulo */

   } GRA_tpCondRet ;

 /***********************************************************************
*
*  $TC Tipo de dados: GRA descritor da cabe�a do grafo
*
* *********************************************************************/

typedef struct GRA_tagGrafo {
  LIS_tppLista pVertices;
    /* ponteiro para a cabeca da lista Vertices */

  LIS_tppLista pVertCorr;
    /* ponteiro para o vertice corrente */

  int (* compara) (void * pValor1, void * pValor2) ;
  /*ponteiro para a funcao que compara o valor armazenado no vertice com a chave identificadora - retorna zero se forem iguais */

  void (* exclui) (void * pValor) ;
  /*ponteiro para a funcao que compara o valor armazenado no vertice com a chave identificadora - retorna zero se forem iguais */

} GRA_tpGrafo;

//MARK: TYPEDEF DEFINIDO AQUI PROVISORIAMENTE (at� criar o .h)
typedef struct GRA_tagGrafo * GRA_tppGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA conte�do de um v�rtice
*
* *********************************************************************/

typedef struct GRA_tagConteudoVert {
  LIS_tppLista pArestas;
    /* ponteiro para a cabeca da lista de arestas do vertice */

  void * pValor;
    /* ponteiro para o valor do vertice */

  int (* compara)(void * pValor1, void * pValor2);

} GRA_tpConteudoVert;

/***** Prot�tipos das fun��es exportadas pelo m�dulo *****/

GRA_tppGrafo GRA_criarGrafo(void ( * ExcluirValor )( void * pValor ), int (*CompararValor)(void * pValor1, void * pValor2)); //done  
GRA_tpCondRet GRA_destruirGrafo(GRA_tppGrafo pGrafo); //done
GRA_tpCondRet GRA_irVertice (GRA_tppGrafo pGrafo, void *pValor); //done
GRA_tpCondRet GRA_irVizinho (GRA_tppGrafo pGrafo, void *pValor); //done
LIS_tppLista GRA_obterCorrente(GRA_tppGrafo pGrafo); //done
void * GRA_obterValor( GRA_tppGrafo pGrafo); //done
GRA_tpCondRet GRA_criarVertice(GRA_tppGrafo pGrafo, void *pValor); //done
GRA_tpCondRet GRA_destruirVertCorr(GRA_tppGrafo pGrafo); //done
GRA_tpCondRet GRA_criarAresta(GRA_tppGrafo pGrafo, void * pValor1, void * pValor2); //done
/********************************************************/

/***** Prot�tipos das fun��es encapsuladas pelo m�dulo *****/
void GRA_destruirVertice(void *pValor);
void GRA_destruirConteudoVert(void * conteudoVertice);
int GRA_compararVertice(void *pValor1, void *pValor2);
int GRA_compararConteudoVert(void *pValor1, void *pValor2);
void GRA_esvaziarGrafo(GRA_tppGrafo pGrafo);
GRA_tpCondRet GRA_inserirVertice(GRA_tppGrafo pGrafo, LIS_tppLista pVertice);
void GRA_destruirValorListaAresta(void * pValor);

/********************************************************/

/***************************************************************************
*  Fun��o: GRA  &Criar Grafo
* **************************************************************************/

GRA_tppGrafo GRA_criarGrafo(void (* ExcluirValor)(void * pValor), int (* CompararValor)(void * pValor1, void * pValor2)) {
  GRA_tpGrafo *pGrafo = NULL;

  pGrafo = (GRA_tpGrafo*)malloc(sizeof(GRA_tpGrafo));
  if (pGrafo == NULL) {
    return NULL;
  } /* if */

  pGrafo->pVertCorr = NULL; /* grafo est� vazio, entao nao ha vertice corrente */
  pGrafo->compara = CompararValor;
  pGrafo->exclui = ExcluirValor;

  pGrafo->pVertices = LIS_CriarLista(GRA_destruirVertice, GRA_compararVertice);  
  /*cria a lista de vertices vazia passando a funcao que sabe destruir o valor do vertice*/
   
  if (pGrafo->pVertices == NULL) {
    free(pGrafo); /*libera memoria alocada para o grafo*/
    return NULL;
  } /*if */

  return pGrafo;
}/* Fim fun��o: GRA  &Criar Grafo */

 /***********************************************************************
*  $FC Fun��o: GRA - Destruir Vertice
*  $ED Descri��o da fun��o
*  Destroi a lista VERTICE
*  Essa funcao deve ser enviada como parametro do campo ExcluirValor da lista VERTICES
***********************************************************************/

 void GRA_destruirVertice(void *pValor) {
  LIS_tppLista pVertice;

  pVertice = (LIS_tppLista) pValor;

  LIS_DestruirLista(pVertice);
  pVertice = NULL;
 } 

/***********************************************************************
*  $FC Fun��o: GRA - Destruir Conteudo do Vertice
*  $ED Descri��o da fun��o
*  Dando um free no dado armazenado pelo vertice, e destruindo a lista arestas
*  Essa funcao deve ser enviada como parametro do campo ExcluirValor da lista VERTICE
***********************************************************************/

void GRA_destruirConteudoVert(void * conteudoVertice) {
  GRA_tpConteudoVert *conteudo;
  conteudo = (GRA_tpConteudoVert *) conteudoVertice; 

  free(conteudo->pValor) ;

  LIS_DestruirLista(conteudo->pArestas) ;

  free(conteudoVertice);
  conteudoVertice = NULL;
} /* Fim fun��o: GRA - Destruir Conteudo Vertice */

/***************************************************************************
*  Fun��o: GRA  &Comparar V�rtice
*  $ED Descri��o da fun��o
*  Essa funcao deve ser passada para o campo 'compara' da lista VERTICES e da lista ARESTAS
*  **************************************************************************/

int GRA_compararVertice(void *pValor1, void *pValor2){
  LIS_tppLista pVertice;
  GRA_tpConteudoVert * pValorVert;
  
  /*faz um typecast do valor1 (que deve ser uma lista VERTICE)*/
  pVertice = (LIS_tppLista) pValor1;

  /*obtem o pValor da lista VERTICE e chama a funcao compara da propria lista vertice como valor de retorno */
  pValorVert = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice);
  return GRA_compararConteudoVert(pValorVert, pValor2);
}

/***************************************************************************
*  Fun��o: GRA  &Comparar Conteudo de V�rtice
*  $ED Descri��o da fun��o
*  Essa funcao deve ser passada para o campo 'compara' da lista VERTICE
* **************************************************************************/

int GRA_compararConteudoVert(void *pValor1, void *pValor2){
  GRA_tpConteudoVert * pValorVert;
  /*faz um typecast do valor1 (que deve ser uma estrutura do tipo tpConteudoVert!)*/
  pValorVert = (GRA_tpConteudoVert *) pValor1;

  /*chama a funcao compara do conteudo do vertice como valor de retorno */
  return pValorVert->compara(pValorVert->pValor, pValor2);
}

/***************************************************************************
*  Fun��o: GRA  &Destruir Grafo
* **************************************************************************/

GRA_tpCondRet GRA_destruirGrafo(GRA_tppGrafo pGrafo) {

  if (!pGrafo){
    return GRA_CondRetGrafoNaoExiste ;
  } /*if */

  GRA_esvaziarGrafo(pGrafo);
  free(pGrafo);
  pGrafo = NULL;

  return GRA_CondRetOK;
} /* Fim fun��o: GRA  &Destruir Grafo */

/***************************************************************************
*  Fun��o: GRA  &Esvaziar Grafo
* **************************************************************************/

void GRA_esvaziarGrafo(GRA_tppGrafo pGrafo) {
  LIS_DestruirLista(pGrafo->pVertices);
  LIS_DestruirLista(pGrafo->pVertCorr);
} /* Fim fun��o: GRA  &Esvaziar Grafo */

/***************************************************************************
*
*  Fun��o: GRA  &Criar Vertice
* **************************************************************************/

GRA_tpCondRet GRA_criarVertice(GRA_tppGrafo pGrafo, void *pValor) {
  //TODO: VERIFICAR SE J� EXISTE UM VERTICE COM O PVALOR ESCOLHIDO
  LIS_tppLista pVertice;
  LIS_tppLista pArestas;
  GRA_tpConteudoVert * pConteudoVert;

  if (!pGrafo) {
    return GRA_CondRetGrafoNaoExiste;
  } /* if */

  if (GRA_irVertice(pGrafo, pValor) == GRA_CondRetOK) {
	  return GRA_CondRetVerticeJaExiste;
  }

  pArestas = LIS_CriarLista(GRA_destruirValorListaAresta, GRA_compararVertice);
  /*OBS: a fun��o de destrui��o de arestas n�o deve destruir seu pValor, pois ele est� referenciado tamb�m na lista v�rticeS */
  if (!pArestas) {
    return GRA_CondRetFaltouMemoria;
  } /* if */

  /* inicializando a estrutura que armazena o valor do v�rtice e sua lista de arestas */
  pConteudoVert = (GRA_tpConteudoVert *)malloc(sizeof(GRA_tpConteudoVert));

  if (!pConteudoVert) {
    LIS_DestruirLista(pArestas);
    return GRA_CondRetFaltouMemoria;
  } /* if */

  pConteudoVert->pArestas = pArestas;
  pConteudoVert->pValor = pValor;
  pConteudoVert->compara = pGrafo->compara;

  /* cria lista v�rtice de apenas um n� */
  pVertice = LIS_CriarLista(GRA_destruirConteudoVert, GRA_compararConteudoVert);
  if (!pVertice){
    return GRA_CondRetFaltouMemoria;
  }

  LIS_InserirElementoApos(pVertice, pConteudoVert);

  return GRA_inserirVertice(pGrafo, pVertice);
}

/***************************************************************************
*
*  Fun��o: GRA  &Inserir Vertice
* ****/

GRA_tpCondRet GRA_inserirVertice(GRA_tppGrafo pGrafo, LIS_tppLista pVertice) {
  if (!pVertice){
    return GRA_CondRetVerticeNaoExiste;
  } /* if */

  LIS_InserirElementoApos(pGrafo->pVertices, pVertice);
  pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(pGrafo->pVertices);
  return GRA_CondRetOK;
}

/***************************************************************************
*  Fun��o: GRA  Ir Vertice
*  $ED Descri��o da fun��o
*  Essa funcao recebe um pValor que � a chave de busca do grafo.
*  O vertice corrente do grafo passa a ser o vertice buscado, caso seja encontrado.
*  Se n�o for encontrado, o vertice corrente continua o mesmo.
* **************************************************************************/

GRA_tpCondRet GRA_irVertice (GRA_tppGrafo pGrafo, void *pValor) {

  LIS_tppLista pVertices;

  if (!pGrafo) {
    return GRA_CondRetGrafoNaoExiste;
  }
  if (!pGrafo->pVertCorr) {
    return GRA_CondRetGrafoVazio;
  }
  pVertices = pGrafo->pVertices;
  /* vai para o inicio da lista vertices */
  IrInicioLista(pVertices);
  //pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(pVertices);

  /* procura na lista de vertices o vertice atraves da chave identificadora */
  if (LIS_ProcurarPorConteudo(pGrafo->pVertices , pValor) == LIS_CondRetOK) {
    /*achou o vertice, entao vertice corrente passa a ser o vertice buscado*/
    pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(pVertices);
    return GRA_CondRetOK;
  }
  return GRA_CondRetNaoAchou;
}

/***************************************************************************
*  Fun��o: GRA  Ir Vizinho
*  $ED Descri��o da fun��o
*  Essa funcao recebe um pValor que � a chave de busca do grafo.
*  O vertice buscado passa a ser o vertice corrente do grafo , caso seja encontrado.
*  Se n�o for encontrado, o vertice corrente continua o mesmo.
*  A busca � feita na lista de arestas do vertice corrente.
* **************************************************************************/

GRA_tpCondRet GRA_irVizinho (GRA_tppGrafo pGrafo, void *pValor) {

  LIS_tppLista pVerticeCorr, listaArestas;
  GRA_tpConteudoVert *conteudoVert;

  if (!pGrafo) {
    return GRA_CondRetGrafoNaoExiste;
  }

  pVerticeCorr = pGrafo->pVertCorr;
  if (!pVerticeCorr) {
    return GRA_CondRetGrafoVazio;
  }

  
  conteudoVert = (GRA_tpConteudoVert *) LIS_ObterValor(pVerticeCorr);
  if (!conteudoVert) { return GRA_CondRetValorNulo; }

  listaArestas = conteudoVert->pArestas;

  if (LIS_ObterValor(listaArestas) == NULL) {
    return GRA_CondRetNaoPossuiAresta;
  }

  /* vai para o inicio da lista vertices */
  IrInicioLista(listaArestas);

  /* procura na lista de arestas o vertice atraves da chave identificadora */
  if (LIS_ProcurarPorConteudo(listaArestas , pValor) == LIS_CondRetOK) {
    /*achou o vertice, entao vertice corrente passa a ser o vertice buscado*/
    pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(listaArestas);
    return GRA_CondRetOK;
  }
  return GRA_CondRetArestaNaoExiste;
}

/***********************************************************************
*  $FC Fun��o: GRA - Destruir Aresta
*  $ED Descri��o da fun��o
*    Ele nao faz nada com o valor1(vertice). Pois se voce matasse
*    esse valor, voce estaria matando o v�rtice em si.
*    Como n�o queremos isso, s� ira ser apagada a referencia 
*    para tal valor.
***********************************************************************/

void GRA_destruirValorListaAresta(void * pValor) {}

/***********************************************************************
*  $FC Fun��o: GRA - Obter Corrente
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o vertice corrente da lista vertices
*     Se o grafo n�o existir (ponteiro nulo), ele retorna nulo. 
*     Se o grafo estiver vazio (vertice corrente nulo), tambem � retornado nulo.
***********************************************************************/

LIS_tppLista GRA_obterCorrente(GRA_tppGrafo pGrafo) {
  if (!pGrafo) { return NULL; /*Grafo nao existe*/ }
  return pGrafo->pVertCorr;
}

/***********************************************************************
*  $FC Fun��o: GRA - Obter Valor
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia do pValor contido dentro do vertice corrente.
*     - retorna NULL, se o grafo n�o existir (ponteiro nulo), ele retorna nulo. 
*     - retorna NULL, se o grafo estiver vazio (vertice corrente nulo).
*     - retorna NULL, se o conteudo do vertice nao existir.
*     - demais casos, retorna o valor do conteudo do vertice
***********************************************************************/

void * GRA_obterValor( GRA_tppGrafo pGrafo ) {
  LIS_tppLista pVerticeCorr;
  GRA_tpConteudoVert * pConteudo;
  pVerticeCorr = GRA_obterCorrente(pGrafo);
  if (!pVerticeCorr) { return NULL; }

  pConteudo = (GRA_tpConteudoVert *) LIS_ObterValor(pVerticeCorr);

  if (!pConteudo){ return NULL; }

  return pConteudo->pValor;
}

/***********************************************************************
*  $FC Fun��o: GRA - Criar aresta
*  $ED Descri��o da fun��o
***********************************************************************/

GRA_tpCondRet GRA_criarAresta(GRA_tppGrafo pGrafo, void * pValor1, void * pValor2) {
  LIS_tppLista pVertice1, pVertice2;
  GRA_tpConteudoVert *conteudoVert1, *conteudoVert2;

  if (!pGrafo) { return GRA_CondRetGrafoNaoExiste; }
  if (!pValor1 || !pValor2) { return GRA_CondRetValorNulo; }
  
  /* passo1: obter a referencia para os vertices */
  if (GRA_irVertice (pGrafo, pValor1) == GRA_CondRetOK) {
    pVertice1 = GRA_obterCorrente(pGrafo);
  } else { return GRA_CondRetNaoAchou; }
  
  if (GRA_irVertice (pGrafo, pValor2) == GRA_CondRetOK) {
    pVertice2 = GRA_obterCorrente(pGrafo);
  } else { return GRA_CondRetNaoAchou; }

  /*obter o conteudo dos vertices*/
  conteudoVert1 = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice1);
  conteudoVert2 = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice2);
  if(!conteudoVert1 || !conteudoVert2) {
    return GRA_CondRetVerticeNaoExiste;
  }

  /*passo2: verificar se os dois vertices sao iguais -> aresta para si mesmo nao pode */
  if (GRA_compararVertice(pVertice1, pValor2) == 0) { return GRA_CondRetArestaIlegal; }

  /*passo3: verificar se ja existe aresta entre eles*/
  if (LIS_ProcurarPorConteudo(conteudoVert1->pArestas, pValor2) == LIS_CondRetOK) {
    return GRA_CondRetArestaJaExiste;
  }
  
  /*passo4: adicionar vertice2 na lista de arestas do vertice 1
            adicionar vertice1 na lista de arestas do vertice 2 */
  if (LIS_InserirElementoApos(conteudoVert1->pArestas, pVertice2) != LIS_CondRetOK) {
    return GRA_CondRetFaltouMemoria;
  }

  if (LIS_InserirElementoApos(conteudoVert2->pArestas, pVertice1) != LIS_CondRetOK) {
    LIS_ExcluirElemento(conteudoVert1->pArestas);
    return GRA_CondRetFaltouMemoria;
  }

  return GRA_CondRetOK;
}

/***********************************************************************
*  $FC Fun��o: GRA - Destruir V�rtice Corrente
***********************************************************************/

GRA_tpCondRet GRA_destruirVertCorr(GRA_tppGrafo pGrafo) {
  if (!pGrafo) { return GRA_CondRetGrafoNaoExiste; }

  LIS_ExcluirElemento(pGrafo->pVertices);
  pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(pGrafo->pVertices);

  return GRA_CondRetOK;
}






int comparacao(void *pValor1, void *pValor2){
	char *str1, *str2;
	str1 = (char*) pValor1;
	str2 = (char*) pValor2;
	return strcmp(str1, str2);
}

void excluir(void *pValor) {
	free(pValor);
	pValor = NULL;
}



int main () {
	GRA_tppGrafo grafo = NULL;
	GRA_tpCondRet ret;
	char * val;
	grafo = GRA_criarGrafo(excluir,comparacao);
	
	ret = GRA_criarVertice(grafo, "a@a.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria vertice a - condRet: %d vert corrente: %s \n", ret, val);
	
	ret = GRA_criarVertice(grafo, "b@b.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria vertice b - condRet: %d vert corrente: %s \n", ret, val);
	
	ret = GRA_criarVertice(grafo, "c@c.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria vertice c - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarVertice(grafo, "d@d.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria vertice d - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarVertice(grafo, "e@e.com");
	val = (char*) GRA_obterValor(grafo);
	printf("\ncria vertice e - condRet: %d vert corrente: %s \n", ret, val);

	ret = GRA_criarVertice(grafo, "b@b.com");
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

	//val = (char*) GRA_obterValor(grafo);
	//printf("\n val: %s \n", val);


	return 0;
}