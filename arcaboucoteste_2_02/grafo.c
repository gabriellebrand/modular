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
#include <LISTA.c>

#define GRAFO_OWN // MARK: pra que serve isso??
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
} GRA_tpGrafo

/***** Protótipos das funções encapuladas no módulo *****/

  GRA_tpCondRet GRA_criarGrafo(GRA_tppGrafo pGrafo, void   ( * ExcluirValor ) ( void * pValor ));
  void * GRA_destruirGrafo(GRA_tppGrafo pGrafo);
  GRA_tpCondRet GRA_irVertice (GRA_tppGrafo pGrafo, void *pValor, int (*compara)(void * pValor1, void * pValor2));
  void * GRA_obterCorrente (GRA_tppGrafo pGrafo, void *pValor);
  GRA_tpCondRet GRA_criarVertice(GRA_tppGrafo pGrafo, void *pValor);
  GRA_tpCondRet GRA_destruirVertCorr(GRA_tppGrafo pGrafo);
  GRA_tpCondRet GRA_criarAresta(GRA_tppGrafo pGrafo)
/********************************************************/


/***************************************************************************
*
*  Função: LIS  &Criar lista
*
* **************************************************************************/

GRA_tpCondRet GRA_criarGrafo(GRA_tpGrafo * pGrafo, void   ( * ExcluirValor ) ( void * pValor )) {
  if (pGrafo){
    //TODO: o grafo já foi alocado! necessário destruir
  }

  pGrafo = (GRA_tpGrafo*)malloc(sizeof(GRA_tpGrafo));
  if (pGrafo == NULL){
    return GRA_CondRetFaltouMemoria;
  } /* if */

    pGrafo->pVertCorr = NULL; /* grafo está vazio, entao nao ha vertice corrente (NULL) */
    
    pGrafo->pVertices = LIS_criarLista(ExcluirValor);  /*cria a lista de vertices vazia passando a funcao que sabe destruir o valor do vertice*/
   
    if (pGrafo->pVertices == NULL){
       free(pGrafo); /*libera memoria alocada para o grafo*/
       return GRA_CondRetFaltouMemoria;
     }

    return GRA_CondRetOK;
}






   typedef enum {
     
 /* 0 */ GRF_CondRetOK ,
               /* Concluiu corretamente */

 /* 1 */ GRF_CondRetGrafoVazio ,
               /* O grafo não contém vértices */

 /* 2 */ GRF_CondRetFimDoGrafo ,
               /* Foi atingido o fim do grafo */

 /* 3 */ GRF_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

 /* 4 */ GRF_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um vértice do grafo */
       
 /* 5 */ GRF_CondRetGrafoNaoExiste,
         /* Grafo não existe ao inserir */

 /* 6 */ GRF_CondRetNaoCriouOrigem,
         /* Não criou vertice origem */
     
 /* 7 */ GRF_CondRetNaoPossuiAresta,
         /* Não possui aresta para o vertice */

 /* 8 */ GRF_CondRetVerticeNaoExiste,
        /* Vertice nao Existe */
     
 /* 9 */ GRF_CondRetArestaNaoExiste,
        /* Não possui arestas */

 /* 10 */ GRF_CondRetArestaJaExiste
        /* Ja possui essa aresta */,

 /* 11 */ GRF_CondRetVerticeJaExiste,
        /* Vertice nao Existe */

 /* 12 */ GRF_CondRetArestaIlegal
        /* Aresta para o proprio vértice */

   } GRF_tpCondRet ;