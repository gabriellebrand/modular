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
***************************************************************************/
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
***********************************************************************/

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
  GRA_tpCondRet GRA_criarAresta(GRA_tppGrafo pGrafo, )







