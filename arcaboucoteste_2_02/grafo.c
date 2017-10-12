/***************************************************************************
*  $MCI Módulo de implementação: GRA  Grafo Não-dirigido
*
*  Arquivo gerado:              GRAFO.c
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores:    gba - Gabrielle Brandemburg dos Anjos
*			   
*
*  $HA Histórico de evolução:
*     Versão  Autor      Data     Observações
*     1       afs,cbs 20/sep/2010 Início desenvolvimento
*
* *************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <LISTA.h>

#define GRAFO_OWN
#include "GRAFO.h"
#undef GRAFO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: GRA descritor da cabeça do grafo
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

/***********************************************************************
*
*  $TC Tipo de dados: GRA conteúdo de um vértice
*
* *********************************************************************/

typedef struct GRA_tagConteudoVert {
  LIS_tppLista pArestas;
    /* ponteiro para a cabeca da lista de arestas do vertice */

  void * pValor;
    /* ponteiro para o valor do vertice */

  int (* compara)(void * pValor1, void * pValor2);

} GRA_tpConteudoVert;

/***** Protótipos das funções exportadas pelo módulo *****/

  GRA_tpCondRet GRA_criarGrafo(GRA_tpGrafo * pGrafo, void ( * ExcluirValor )( void * pValor ), int (*CompararValor)(void * pValor1, void * pValor2));
  void * GRA_destruirGrafo(GRA_tppGrafo pGrafo);
  GRA_tpCondRet GRA_irVertice (GRA_tppGrafo pGrafo, void *pValor);
  void * GRA_obterCorrente (GRA_tppGrafo pGrafo);
  GRA_tpCondRet GRA_criarVertice(GRA_tppGrafo pGrafo, void *pValor);
  GRA_tpCondRet GRA_destruirVertCorr(GRA_tppGrafo pGrafo);
  GRA_tpCondRet GRA_criarAresta(GRA_tppGrafo pGrafo)
/********************************************************/


/***************************************************************************
*  Função: GRA  &Criar Grafo
* **************************************************************************/

GRA_tpCondRet GRA_criarGrafo(GRA_tpGrafo * pGrafo, void (* ExcluirValor)(void * pValor), int (* CompararValor)(void * pValor1, void * pValor2)) {
  if (pGrafo){
    //TODO: o grafo já foi alocado! necessário destruir
  }

  pGrafo = (GRA_tpGrafo*)malloc(sizeof(GRA_tpGrafo));
  if (pGrafo == NULL) {
    return GRA_CondRetFaltouMemoria;
  } /* if */

  pGrafo->pVertCorr = NULL; /* grafo está vazio, entao nao ha vertice corrente */
  pGrafo->compara = CompararValor;
  pGrafo->exclui = ExcluirValor;

  pGrafo->pVertices = LIS_criarLista(GRA_destruirVertice, GRA_compararVertice);  
  /*cria a lista de vertices vazia passando a funcao que sabe destruir o valor do vertice*/
   
  if (pGrafo->pVertices == NULL) {
    free(pGrafo); /*libera memoria alocada para o grafo*/
    return GRA_CondRetFaltouMemoria;
  } /*if */

  return GRA_CondRetOK;
}/* Fim função: GRA  &Criar Grafo */

 /***********************************************************************
*  $FC Função: GRA - Destruir Vertice
*  $ED Descrição da função
*  Dando um free no dado armazenado pelo vertice, e destruindo a lista arestas
*  Essa funcao deve ser enviada como parametro do campor ExcluirValor da lista VERTICE
***********************************************************************/

 void GRA_destruirVertice(void *pValor) {
  LIS_tppLista pVertice;

  pVertice = (LIS_tppLista) pValor;

  LIS_DestruirLista(pVertice);
  pVertice = NULL;
 } 

 /***********************************************************************
*  $FC Função: GRA - Destruir Conteudo do Vertice
*  $ED Descrição da função
*  Dando um free no dado armazenado pelo vertice, e destruindo a lista arestas
*  Essa funcao deve ser enviada como parametro do campo ExcluirValor da lista VERTICE
***********************************************************************/

void GRA_destruirConteudoVertice(void * conteudoVertice) {
  GRA_tpConteudoVert *conteudo;
  conteudo = (GRA_tpConteudoVert *) conteudoVertice; //GABRIELLE: não sei se estou fazendo esse typecast corretamente!!!

  free(conteudo->pValor) ;

  LIS_DestruirLista(conteudo->pArestas) ;

  free(conteudoVertice);
  conteudoVertice = NULL;
} /* Fim função: GRA - Destruir Conteudo Vertice */

/***************************************************************************
*  Função: GRA  &Comparar Vértice
*  Descrição: Essa funcao deve ser passada para o campo 'compara' da lista VERTICES
*  **************************************************************************/

int GRA_compararVertice(void *pValor1, void *pValor2){
  LIS_tppLista pVertice;
  GRA_tpConteudoVert * pValorVert;
  
  /*faz um typecast do valor1 (que deve ser uma lista VERTICE)*/
  pVertice = (LIS_tppLista) pValor1;

  /*obtem o pValor da lista VERTICE e chama a funcao compara da propria lista vertice como valor de retorno */
  pValorVert = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice);
  return pVertice->CompararValor(pValorVert, pValor2);
}

/***************************************************************************
*  Função: GRA  &Comparar Conteudo de Vértice
*  Descrição: Essa funcao deve ser passada para o campo 'compara' da lista VERTICE
* **************************************************************************/

int GRA_compararConteudoVert(void *pValor1, void *pValor2){
  GRA_tpConteudoVert * pValorVert;
  /*faz um typecast do valor1 (que deve ser uma estrutura do tipo tpConteudoVert!)*/
  pValorVert = (GRA_tpConteudoVert *) pValor1;

  /*chama a funcao compara do conteudo do vertice como valor de retorno */
  return pValorVert->compara(pValorVert->pValor, pValor2);
}

/***************************************************************************
*  Função: GRA  &Destruir Grafo
* **************************************************************************/

void GRA_destruirGrafo(GRA_tppGrafo pGrafo) {

  if (!pGrafo){
    return GRA_CondRetGrafoNaoExiste ;
  } /*if */

  GRA_esvaziarGrafo(pGrafo);
  free(pGrafo);
  pGrafo = NULL;
} /* Fim função: GRA  &Destruir Grafo */

/***************************************************************************
*  Função: GRA  &Esvaziar Grafo
* **************************************************************************/
void GRA_esvaziarGrafo(GRA_tppGrafo pGrafo) {
  LIS_DestruirLista(pGrafo->pVertices);
  LIS_DestruirLista(pGrafo->pVertCorr);
} /* Fim função: GRA  &Esvaziar Grafo */

/***************************************************************************
*
*  Função: GRA  &Criar Vertice
*  ****/

GRA_tpCondRet GRA_criarVertice(GRA_tppGrafo pGrafo, void *pValor) {
  
  LIS_tppLista pVertice;
  LIS_tppLista pArestas;
  GRA_tpConteudoVert * pConteudoVert;

  if (!pGrafo) {
    return GRA_CondRetGrafoNaoExiste;
  } /* if */

  pArestas = LIS_CriarLista(GRA_destruirValorListaAresta);
  /*OBS: a função de destruição de arestas não deve destruir seu pValor, pois ele está referenciado também na lista vérticeS */
  if (!pArestas) {
    returnGRA_CondRetFaltouMemoria;
  } /* if */

  /* inicializando a estrutura que armazena o valor do vértice e sua lista de arestas */
  pConteudoVert = (GRA_tpConteudoVert *)malloc(sizeof(GRA_tpConteudoVert));

  if (!pConteudoVert) {
    LIS_DestruirLista(pArestas);
    return GRA_CondRetFaltouMemoria
  } /* if */

  pConteudoVert->pArestas = pArestas;
  pConteudoVert->pValor = pValor;
  pConteudoVert->compara = pGrafo->compara;

  /* cria lista vértice de apenas um nó */
  pVertice = LIS_CriarLista(GRA_destruirConteudoVert, GRA_compararConteudoVert);
  LIS_InserirElementoApos(pVertice, pConteudoVert);

  GRA_inserirVertice(pGrafo, pVertice);

  return GRA_CondRetOK;

}

/***************************************************************************
*
*  Função: GRA  &Inserir Vertice
*  ****/

GRA_tpCondRet GRA_inserirVertice(GRA_tppGrafo pGrafo, LIS_tppLista pVertice) {
  if (!pVertice){
    return GRA_CondRetVerticeNaoExiste;
  } /* if */

  LIS_InserirElementoApos(pGrafo->pVertices, pVertice);
}

/***************************************************************************
*
*  Função: GRA  &Ir Vertice
*  ****/

GRA_tpCondRet GRA_irVertice (GRA_tppGrafo pGrafo, void *pValor) {

}

/***********************************************************************
*
*  $FC Função: GRA - Destruir Aresta
*  $ED Descrição da função
*    Ele nao faz nada com o valor1(vertice). Pois se voce matasse
*    esse valor, voce estaria matando o vértice em si.
*    Como não queremos isso, só ira ser apagada a referencia 
*    para tal valor.
*
***********************************************************************/

void DestruirValorListaAresta(void * pValor) {}








   typedef enum {
     
 /* 0 */ GRA_CondRetOK ,
               /* Concluiu corretamente */

 /* 1 */ GRA_CondRetGrafoVazio ,
               /* O grafo não contém vértices */

 /* 2 */ GRA_CondRetFimDoGrafo ,
               /* Foi atingido o fim do grafo */

 /* 3 */ GRA_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

 /* 4 */ GRA_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um vértice do grafo */
       
 /* 5 */ GRA_CondRetGrafoNaoExiste,
         /* Grafo não existe ao inserir */

 /* 6 */ GRA_CondRetNaoCriouOrigem,
         /* Não criou vertice origem */
     
 /* 7 */ GRA_CondRetNaoPossuiAresta,
         /* Não possui aresta para o vertice */

 /* 8 */ GRA_CondRetVerticeNaoExiste,
        /* Vertice nao Existe */
     
 /* 9 */ GRA_CondRetArestaNaoExiste,
        /* Não possui arestas */

 /* 10 */ GRA_CondRetArestaJaExiste
        /* Ja possui essa aresta */,

 /* 11 */ GRA_CondRetVerticeJaExiste,
        /* Vertice nao Existe */

 /* 12 */ GRA_CondRetArestaIlegal
        /* Aresta para o proprio vértice */

   } GRA_tpCondRet ;