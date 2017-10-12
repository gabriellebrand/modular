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

  int ( * Compara ) ( void * pValor, void * valorChave ) ;
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

} GRA_tpConteudoVert;

/***** Protótipos das funções exportadas pelo módulo *****/

  GRA_tpCondRet GRA_criarGrafo(GRA_tppGrafo pGrafo, void   ( * ExcluirValor ) ( void * pValor ));
  void * GRA_destruirGrafo(GRA_tppGrafo pGrafo);
  GRA_tpCondRet GRA_irVertice (GRA_tppGrafo pGrafo, void *pValor);
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

GRA_tpCondRet GRA_criarGrafo(GRA_tpGrafo * pGrafo, void ( * ExcluirValor )( void * pValor ), int (*CompararValor)(void * pValor1, void * pValor2)) {
  if (pGrafo){
    //TODO: o grafo já foi alocado! necessário destruir (chamar funcao destruirGrafo)
  }

  pGrafo = (GRA_tpGrafo*)malloc(sizeof(GRA_tpGrafo));
  if (pGrafo == NULL) {
    return GRA_CondRetFaltouMemoria;
  } /* if */

  pGrafo->pVertCorr = NULL; /* grafo está vazio, entao nao ha vertice corrente (NULL) */
  pGrafo->Compara = CompararValor

  pGrafo->pVertices = LIS_criarLista(ExcluirValor, CompararValor);  
  /*cria a lista de vertices vazia passando a funcao que sabe destruir o valor da lista VERTICES*/
   
  if (pGrafo->pVertices == NULL) {
    free(pGrafo); /*libera memoria alocada para o grafo*/
    return GRA_CondRetFaltouMemoria;
  }

    return GRA_CondRetOK;
}/* Fim função: GRA  &Criar Grafo */

/***************************************************************************
*
*  Função: GRA  &Destruir Grafo
*  ****/

void GRA_destruirGrafo(GRA_tppGrafo pGrafo) {

  if (!pGrafo){
    return GRA_CondRetGrafoNaoExiste ;
  }
  GRA_esvaziarGrafo(pGrafo);
  free(pGrafo);
  pGrafo = NULL;
} /* Fim função: GRA  &Destruir Grafo */

/***************************************************************************
*
*  Função: GRA  &Esvaziar Grafo
*  ****/
void GRA_esvaziarGrafo(GRA_tppGrafo pGrafo) {
  LIS_DestruirLista(pGrafo->pVertices);
  LIS_DestruirLista(pGrafo->pVertCorr);
} /* Fim função: GRA  &Esvaziar Grafo */

/***************************************************************************
*
*  Função: GRA  &Criar Vertice
*  ****/

GRA_tpCondRet GRA_criarVertice(GRA_tppGrafo pGrafo, void *pValor) {

}

/***************************************************************************
*
*  Função: GRA  &Construir Vertice
*  ****/

GRA_tpCondRet GRA_construirVertice(LIS_tppLista pVertice, void *pValor) {
  LIS_tppLista pArestas;
  pArestas = LIS_CriarLista(GRA_destruirValorListaArestas);
  /*OBS: a função de destruição de arestas não deve destruir seu pValor, pois ele está referenciado também na lista verticeS */
  
  if (!pArestas) {
    returnGRA_CondRetFaltouMemoria;
  }

  pConteudoVert = (GRA_tpConteudoVert *)malloc(sizeof(GRA_tpConteudoVert));

  if (!pConteudoVert) {
    LIS_DestruirLista(pArestas);
    return GRA_CondRetFaltouMemoria
  }

  pConteudoVert->pArestas = pArestas;
  pConteudoVert->pValor = pValor;

  pVertice = LIS_CriarLista(GRA_destruirConteudoVertice);

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

void GRA_destruirValorListaArestas(void * pValor) {}

/***********************************************************************
*
*  $FC Função: GRA - Destruir Conteudo do Vertice
*  $ED Descrição da função
*  Dando um free no dado armazenado
*  pelo vertice, e destruindo a lista 
*  arestas
*
***********************************************************************/

void 
  pVertice = LIS_CriarLista(GRA_destruirConteudoVertice(void * conteudoVertice) {
  GRA_tpConteudoVert *conteudo;
  conteudo = (GRA_tpConteudoVert *) conteudoVertice; //GABRIELLE: não sei se estou fazendo esse typecast corretamente!!!

  free(conteudo->pValor) ;

  LIS_DestruirLista(conteudo->pArestas) ;

  free(conteudo);
  free(conteudoVertice); //precisa disso??

  conteudoVertice = NULL;
} /* Fim função: GRA - Destruir Conteudo Vertice */

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