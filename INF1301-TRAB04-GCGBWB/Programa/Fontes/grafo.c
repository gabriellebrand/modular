#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define GRAFO_OWN
#include "grafo.h"
#undef GRAFO_OWN

#ifdef _DEBUG
	#include "CESPDIN.H"
	#include "CONTA.H"
	#include "../Tabelas/IdTiposEspaco.def"
#endif

/***************************************************************************
*
*  $MCD Módulo de implementação: GRA  Grafo Genérico Não-Dirigido
*
*  Arquivo gerado:              GRAFO.h
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 T2
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gba - Gabrielle Brandemburg dos Anjos
*           wbs - Wellington Bezerra da Silva
*           gc  - Gabriel Cantergiani
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       gba   16/10/2017  correções de bugs
*     1       gba   14/10/2017  finalização
*     1       gba   08/10/2017  início desenvolvimento
* ***************************************************************************/

/***********************************************************************
*  $TC Tipo de dados: GRA descritor da cabeça do grafo
* *********************************************************************/

typedef struct GRA_tagGrafo {
  LIS_tppLista pVertices;
    /* ponteiro para a cabeca da lista Vertices */

  LIS_tppLista pVertCorr;
    /* ponteiro para o vertice corrente */

  int (* compara) (void * pDado, void * pChaveID) ;
  /*ponteiro para a funcao que compara o valor armazenado no vertice com a chave identificadora - retorna zero se forem iguais */

  void (* exclui) (void ** pDado) ;
  /*ponteiro para a funcao que compara o valor armazenado no vertice com a chave identificadora - retorna zero se forem iguais */

  #ifdef _DEBUG
    int numElem;
  #endif

} GRA_tpGrafo;

/***********************************************************************
*  $TC Tipo de dados: GRA conteúdo de um vértice
* *********************************************************************/

typedef struct GRA_tagConteudoVert {
  LIS_tppLista pArestas;
    /* ponteiro para a cabeca da lista de arestas do vertice */

  void * pDado;
    /* ponteiro para o valor do vertice */

  int (* compara)(void * pDado, void * pChaveID);

  void (* exclui) (void * pDado) ;

  #ifdef _DEBUG
      GRA_tppGrafo pCabeca ;
      /* Ponteiro para cabeca
      *
      *$ED Descrição
      *   Todos os vértices correntes do grafo devem apontar para a respectiva cabeça.
      *   Esse ponteiro corresponde a um identificador do grafo para fins
      *   de verificação da integridade. */

      int NumArestas;
      /* Número de arestas que um vertice possui. Deve ser igual ao número de elementos da lista pArestas */

  #endif

} GRA_tpConteudoVert;


/*****  Dados encapsulados no módulo  *****/

      #ifdef _DEBUG

      static char EspacoLixo[ 256 ] =
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
            /* Espaço de dados lixo usado ao testar */
      #endif


/***** Protótipos das funções encapsuladas pelo módulo *****/

void GRA_DestruirVertice(void *pDado);
void GRA_DestruirConteudoVert(void * conteudoVertice);
int GRA_CompararVertice(void *pDado, void *pChaveID);
int GRA_CompararConteudoVert(void *pDado, void *pChaveID);
GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo, LIS_tppLista pVertice);
void GRA_DestruirValorListaAresta(void * pDado);
GRA_tpCondRet GRA_DestruirAresta(LIS_tppLista pVertice1 , LIS_tppLista pVertice2);
GRA_tpCondRet GRA_LiberarAresta(LIS_tppLista pVertice1 , LIS_tppLista pVertice2);
LIS_tppLista GRA_ObterCorrente(GRA_tppGrafo pGrafo);
int GRA_VerificaVertice(LIS_tppLista pVertice, GRA_tppGrafo pGrafo);
int GRA_VerificaListaVertices(LIS_tppLista pVertices, GRA_tppGrafo pGrafo);
int GRA_VerificaConteudoVert(GRA_tpConteudoVert * pConteudoVert, GRA_tppGrafo pGrafo);

/********************************************************/

/***************************************************************************
*  Função: GRA  &Criar Grafo
* **************************************************************************/

GRA_tppGrafo GRA_CriarGrafo(void (* ExcluirValor)(void * pDado), int (* CompararValor)(void * pDado, void * pChaveID)) {
  GRA_tpGrafo *pGrafo = NULL;

  pGrafo = (GRA_tpGrafo*)malloc(sizeof(GRA_tpGrafo));
  if (pGrafo == NULL) {
    return NULL;
  } /* if */

  pGrafo->pVertCorr = NULL; /* grafo está vazio, entao nao ha vertice corrente */
  pGrafo->compara = CompararValor;
  pGrafo->exclui = ExcluirValor;

  pGrafo->pVertices = LIS_CriarLista(GRA_DestruirVertice, GRA_CompararVertice);  
  /*cria a lista de vertices vazia passando a funcao que sabe destruir o valor do vertice*/
   
  if (pGrafo->pVertices == NULL) {
    free(pGrafo); /*libera memoria alocada para o grafo*/
    return NULL;
  } /*if */

  #ifdef _DEBUG
       pGrafo->numElem = 0;
       CED_DefinirTipoEspaco( pGrafo , GRA_TipoEspacoCabeca ) ;
  #endif

  return pGrafo;
}/* Fim função: GRA  &Criar Grafo */

 /***********************************************************************
*  $FC Função: GRA - Destruir Vertice
*  $ED Descrição da função
*  Destroi a lista VERTICE
*  Essa funcao deve ser enviada como parametro do campo ExcluirValor da lista VERTICES
***********************************************************************/

 void GRA_DestruirVertice(void *pDado) {
  LIS_tppLista *pVertice;
  
  pVertice = (LIS_tppLista *) pDado;

  LIS_DestruirLista(*pVertice);
  *pVertice = NULL;
 } /* Fim função: GRA  &Destruir Vertice */

/***********************************************************************
*  $FC Função: GRA - Destruir Conteudo do Vertice
*  $ED Descrição da função
*  Dando um free no dado armazenado pelo vertice, e destruindo a lista arestas
*  Essa funcao deve ser enviada como parametro do campo ExcluirValor da lista VERTICE
***********************************************************************/

void GRA_DestruirConteudoVert(void * conteudoVertice) {
  GRA_tpConteudoVert **conteudo;
  void * dado;
  conteudo = (GRA_tpConteudoVert **) conteudoVertice; 
  


  //printf("\nvai entrar na excluir pdado\n");

  dado = (*conteudo)->pDado;
  (*conteudo)->exclui(&dado);
  //printf("\nvoltou excluir pDado\n");
  
  LIS_DestruirLista((*conteudo)->pArestas) ;
 
  free(*conteudo);
  *conteudo = NULL;
} /* Fim função: GRA &Destruir Conteudo Vertice */

/***************************************************************************
*  Função: GRA  &Comparar Vértice
*  $ED Descrição da função
*  Essa funcao deve ser passada para o campo 'compara' da lista VERTICES e da lista ARESTAS
*  **************************************************************************/

int GRA_CompararVertice(void *pDado, void *pChaveID){
  LIS_tppLista pVertice;
  GRA_tpConteudoVert * pValorVert;
  
  /*faz um typecast do pDado (que deve ser uma lista VERTICE)*/
  pVertice = (LIS_tppLista) pDado;

  /*obtem o pDado da lista VERTICE e chama a funcao compara da propria lista vertice como valor de retorno */
  pValorVert = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice);
  return GRA_CompararConteudoVert(pValorVert, pChaveID);
} /* Fim função: GRA  &Comparar Vertice */

/***************************************************************************
*  Função: GRA  &Comparar Conteudo de Vértice
*  $ED Descrição da função
*  Essa funcao deve ser passada para o campo 'compara' da lista VERTICE
* **************************************************************************/

int GRA_CompararConteudoVert(void *pDado, void *pChaveID){
  GRA_tpConteudoVert * pValorVert;
  /*faz um typecast do pDado (que deve ser uma estrutura do tipo tpConteudoVert!)*/
  pValorVert = (GRA_tpConteudoVert *) pDado;

  /*chama a funcao compara do conteudo do vertice como valor de retorno */
  return pValorVert->compara(pValorVert->pDado, pChaveID);
}

/***************************************************************************
*  Função: GRA  &Destruir Grafo
* **************************************************************************/

GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo *pGrafo) {

  if (! (*pGrafo)){
    return GRA_CondRetGrafoNaoExiste ;
  } /*if */

  LIS_DestruirLista((*pGrafo)->pVertices);
  
  free(*pGrafo);
  *pGrafo = NULL;

  return GRA_CondRetOK;
} /* Fim função: GRA  &Destruir Grafo */

/***************************************************************************
*  Função: GRA  &Criar Vertice
* **************************************************************************/

GRA_tpCondRet GRA_CriarVertice(GRA_tppGrafo pGrafo, void *pDado, void *pChaveID) { 

  LIS_tppLista pVertice;
  LIS_tppLista pArestas;
  GRA_tpConteudoVert * pConteudoVert;

  if (!pGrafo) {
    return GRA_CondRetGrafoNaoExiste;
  } /* if */

if(!pDado || !pChaveID) return GRA_CondRetValorNulo;
  /*verifica se já existe um vertice com a chave escolhida*/
  if (GRA_IrVertice(pGrafo, pChaveID) == GRA_CondRetOK) {
    return GRA_CondRetVerticeJaExiste;
  }

  pArestas = LIS_CriarLista(NULL, GRA_CompararVertice);
  /*OBS: a função de destruição de arestas não deve destruir seu pDado, pois ele está referenciado também na lista vérticeS */
  if (!pArestas) {
    return GRA_CondRetFaltouMemoria;
  } /* if */

  /* inicializando a estrutura que armazena o valor do vértice e sua lista de arestas */
  pConteudoVert = (GRA_tpConteudoVert *)malloc(sizeof(GRA_tpConteudoVert));

  if (pConteudoVert == NULL) {
    LIS_DestruirLista(pArestas);
    return GRA_CondRetFaltouMemoria;
  } /* if */

  pConteudoVert->pArestas = pArestas;
  pConteudoVert->pDado = pDado;
  pConteudoVert->compara = pGrafo->compara;
  pConteudoVert->exclui = pGrafo->exclui;
   #ifdef _DEBUG
      pConteudoVert->NumArestas = 0;
      pConteudoVert->pCabeca = pGrafo;
   #endif

  /* cria lista vértice de apenas um nó */
  pVertice = LIS_CriarLista(GRA_DestruirConteudoVert, GRA_CompararConteudoVert);
  if (!pVertice){
    return GRA_CondRetFaltouMemoria;
  }

  LIS_InserirElementoApos(pVertice, pConteudoVert);

  #ifdef _DEBUG
       CED_DefinirTipoEspaco( pConteudoVert , GRA_TipoEspacoVertice ) ;
       pConteudoVert->pCabeca = pGrafo;
       pGrafo->numElem ++;
  #endif

  return GRA_InserirVertice(pGrafo, pVertice);
} /* Fim função: GRA  &Criar Vertice */


/***************************************************************************
*  Função: GRA  &Inserir Vertice
* **************************************************************************/

GRA_tpCondRet GRA_InserirVertice(GRA_tppGrafo pGrafo, LIS_tppLista pVertice) {
  if (!pVertice){
    return GRA_CondRetVerticeNaoExiste;
  } /* if */

  LIS_InserirElementoApos(pGrafo->pVertices, pVertice);
  pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(pGrafo->pVertices);

  return GRA_CondRetOK;
} /* Fim função: GRA  &Inserir Vertice */

/***************************************************************************
*  Função: GRA  &Ir Vertice
*  $ED Descrição da função
*  Percorre a lista de vértices do grafo até encontrar o vertice correspondente à chave passada.
*  Essa funcao recebe um pChaveID que é a chave de busca do grafo.
*  O vertice corrente do grafo passa a ser o vertice buscado, caso seja encontrado.
*  Se não for encontrado, o vertice corrente continua o mesmo.
* **************************************************************************/

GRA_tpCondRet GRA_IrVertice (GRA_tppGrafo pGrafo, void *pChaveID) {

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

  /* procura na lista de vertices o vertice atraves da chave identificadora */
  if (LIS_ProcurarPorConteudo(pVertices , pChaveID) == LIS_CondRetOK) {
    /*achou o vertice, entao vertice corrente passa a ser o vertice buscado*/
    pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(pVertices);
    return GRA_CondRetOK;
  }
  
  return GRA_CondRetVerticeNaoExiste;
} /* Fim função: GRA  &Ir Vertice */

/***************************************************************************
*  Função: GRA  Ir Vizinho
*  $ED Descrição da função
*  Essa funcao recebe um pChaveID que é a chave de busca do grafo.
*  O vertice buscado passa a ser o vertice corrente do grafo , caso seja encontrado.
*  Se não for encontrado, o vertice corrente continua o mesmo.
*  A busca é feita na lista de arestas do vertice corrente.
* **************************************************************************/

GRA_tpCondRet GRA_IrVizinho (GRA_tppGrafo pGrafo, void *pChaveID) {

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

  /* vai para o inicio da lista arestas */
  IrInicioLista(listaArestas);

  /* procura na lista de arestas o vertice atraves da chave identificadora */
  if (LIS_ProcurarPorConteudo(listaArestas , pChaveID) == LIS_CondRetOK) {
    /*achou o vertice, entao vertice corrente passa a ser o vertice buscado*/
    pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(listaArestas);
    return GRA_CondRetOK;
  }
  return GRA_CondRetArestaNaoExiste;
} /* Fim função: GRA  &Ir Vizinho */


/***************************************************************************
*  Função: GRA  Avançar Vizinho
*  $ED Descrição da função
*  Essa funcao avança na lista de arestas do vértice corrente a partir do primeiro elemento.
*  O parametro numElem indica quantos elementos serão pulados, a partir do primeiro.
*  O valor do elemento da aresta é armazenado no vertice corrente.
*  É necessário chamar a funcao ir vertice para atualizar o vertice corrente e buscar na lista de arestas correta.
*  Se numElem = 0, o primeiro elemento da lista de arestas é retornado.
* **************************************************************************/
GRA_tpCondRet GRA_AvancarVizinho (GRA_tppGrafo pGrafo, int numElem) {

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

  /* vai para o inicio da lista arestas */
  IrInicioLista(listaArestas);

  //avança elemento vizinho na lista de arestas
  if (LIS_AvancarElementoCorrente(listaArestas,numElem) == LIS_CondRetOK) {
    //pDado = LIS_ObterValor(listaArestas);
	pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(listaArestas);
    return GRA_CondRetOK;
  }

  return GRA_CondRetFimArestas;

} /* Fim função: GRA  &Avançar Vizinho */

/***********************************************************************
*  $FC Função: GRA - Obter Corrente
*  $ED Descrição da função
*     Obtem a referência para o vertice corrente da lista vertices
*     Se o grafo não existir (ponteiro nulo), ele retorna nulo. 
*     Se o grafo estiver vazio (vertice corrente nulo), tambem é retornado nulo.
***********************************************************************/

LIS_tppLista GRA_ObterCorrente(GRA_tppGrafo pGrafo) {
  if (!pGrafo) { return NULL; /*Grafo nao existe*/ }
  return pGrafo->pVertCorr;
} /* Fim função: GRA  &Obter Corrente */

/***********************************************************************
*  $FC Função: GRA - Obter Valor
*  $ED Descrição da função
*     Obtem a referência do pDado contido dentro do vertice corrente.
*     - retorna NULL, se o grafo não existir (ponteiro nulo), ele retorna nulo. 
*     - retorna NULL, se o grafo estiver vazio (vertice corrente nulo).
*     - retorna NULL, se o conteudo do vertice nao existir.
*     - demais casos, retorna o valor do conteudo do vertice
***********************************************************************/

void * GRA_ObterValor( GRA_tppGrafo pGrafo ) {
  LIS_tppLista pVerticeCorr;
  GRA_tpConteudoVert * pConteudo;
  pVerticeCorr = GRA_ObterCorrente(pGrafo);
  if (!pGrafo) { return NULL; }
  if (!pVerticeCorr) { return NULL; }

  pConteudo = (GRA_tpConteudoVert *) LIS_ObterValor(pVerticeCorr);
  return pConteudo->pDado;
} /* Fim função: GRA  &Obter Valor */

/***********************************************************************
*  $FC Função: GRA - Criar aresta
*  $ED Descrição da função
***********************************************************************/

GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo, void * pChaveID_1, void * pChaveID_2) {
  LIS_tppLista pVertice1, pVertice2;
  GRA_tpConteudoVert *conteudoVert1, *conteudoVert2;

  if (!pGrafo) { return GRA_CondRetGrafoNaoExiste; }
  if (!pChaveID_1 || !pChaveID_2) { return GRA_CondRetValorNulo; }
  
  /* passo1: obter a referencia para os vertices */
  if (GRA_IrVertice (pGrafo, pChaveID_1) == GRA_CondRetOK) {
    pVertice1 = GRA_ObterCorrente(pGrafo);
  } else { return GRA_CondRetVerticeNaoExiste; }
  
  if (GRA_IrVertice (pGrafo, pChaveID_2) == GRA_CondRetOK) {
    pVertice2 = GRA_ObterCorrente(pGrafo);
  } else { return GRA_CondRetVerticeNaoExiste; }

  /*obter o conteudo dos vertices*/
  conteudoVert1 = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice1);
  conteudoVert2 = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice2);

  /*passo2: verificar se os dois vertices sao iguais -> aresta para si mesmo nao pode */
  if (GRA_CompararVertice(pVertice1, pChaveID_2) == 0) { return GRA_CondRetArestaIlegal; }

  /*passo3: verificar se ja existe aresta entre eles*/
  IrInicioLista(conteudoVert1->pArestas);
  if (LIS_ProcurarPorConteudo(conteudoVert1->pArestas, pChaveID_2) == LIS_CondRetOK) {
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

   #ifdef _DEBUG
    conteudoVert1->NumArestas++;
    conteudoVert2->NumArestas++;
   #endif

  return GRA_CondRetOK;
} /* Fim função: GRA  &Criar Aresta */

/***********************************************************************
*  $FC Função: GRA - Excluir aresta
*  $ED Descrição da função
*     Exclui uma aresta entre dois vertices, atraves de suas chaves identificadoras
***********************************************************************/
GRA_tpCondRet GRA_ExcluirAresta(GRA_tppGrafo pGrafo, void *pChaveID_1, void *pChaveID_2) {
  LIS_tppLista pVertice1, pVertice2;

  if (!pGrafo) {
    return GRA_CondRetGrafoNaoExiste;
  }
  if(!pGrafo->pVertCorr){
    return GRA_CondRetGrafoVazio;
  }

  /*procura a referencia para o vertice 1 a partir da chave identificadora*/
  if(GRA_IrVertice(pGrafo, pChaveID_1) != GRA_CondRetOK) {
    return GRA_CondRetVerticeNaoExiste;
  }
  pVertice1 = GRA_ObterCorrente(pGrafo);
  /*procura a referencia para o vertice 2 a partir da chave identificadora*/
  if(GRA_IrVertice(pGrafo, pChaveID_2) != GRA_CondRetOK) {
    return GRA_CondRetVerticeNaoExiste;
  }
  pVertice2 = GRA_ObterCorrente(pGrafo);

  return GRA_DestruirAresta(pVertice1 , pVertice2);
} /* Fim função: GRA  &Excluir Aresta */

/***********************************************************************
*  $FC Função: GRA - Destruir aresta
*  $ED Descrição da função
*     Destroi arestas entre duas listas vertice
***********************************************************************/
GRA_tpCondRet GRA_DestruirAresta(LIS_tppLista pVertice1 , LIS_tppLista pVertice2) {
   #ifdef _DEBUG
   GRA_tpConteudoVert *Vert1, *Vert2;	
   #endif	

  if( !pVertice1 || !pVertice2 )
  {
    GRA_CondRetVerticeNaoExiste;
  } /* if */

  /*primeiro deleta o vertice 2 da lista de arestas do vertice 1*/
  if (GRA_LiberarAresta(pVertice1 ,pVertice2) == GRA_CondRetArestaNaoExiste) {
    return GRA_CondRetArestaNaoExiste;
  }
  /*depois deleta o vertice 1 da lista de arestas do vertice 2*/
  if (GRA_LiberarAresta(pVertice2 ,pVertice1) == GRA_CondRetArestaNaoExiste) {
    return GRA_CondRetArestaNaoExiste;
  }


  #ifdef _DEBUG

    Vert1 = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice1);
    Vert2 = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice2);

    Vert1->NumArestas--;
    Vert2->NumArestas--;
    
   #endif

  return GRA_CondRetOK;
} /* Fim função: GRA  &Destruir Aresta */

/***********************************************************************
*  $FC Função: GRA - Liberar Aresta
*  $ED Descrição da função
*     Libera vertice2 da lista de arestas do vertice1
***********************************************************************/
GRA_tpCondRet GRA_LiberarAresta(LIS_tppLista pVertice1 , LIS_tppLista pVertice2) {
  GRA_tpConteudoVert *conteudo;

  /* acessar aresta do vertice 1*/
  conteudo = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice1);
  IrInicioLista(conteudo->pArestas);
  /* verificar se existe aresta entre os vertices */
  IrInicioLista(conteudo->pArestas);
  if (LIS_ProcurarValor(conteudo->pArestas, pVertice2) != LIS_CondRetOK) {
    return GRA_CondRetArestaNaoExiste;
  }
  /*excluir vertice2 das arestas do vertice 1*/
  LIS_ExcluirElemento(conteudo->pArestas);

  return GRA_CondRetOK;
} /* Fim função: GRA  &Liberar Aresta */

/***********************************************************************
*  $FC Função: GRA - Excluir Vértice Corrente
*  $ED Descrição da função
*     Exclui o vértice corrente do grafo, incluindo suas arestas.
*     Apaga todas as referências do vértice das arestas dos vizinhos.
*     Vertice corrente passa a ser qualquer um.
***********************************************************************/

GRA_tpCondRet GRA_ExcluirVertCorr(GRA_tppGrafo pGrafo) {
  LIS_tppLista pVertCorr, pVizinho;
  GRA_tpConteudoVert * conteudoVertCorr;

  if (!pGrafo) { return GRA_CondRetGrafoNaoExiste; }

  pVertCorr = GRA_ObterCorrente(pGrafo);
  if (!pVertCorr) { return GRA_CondRetGrafoVazio; }

  conteudoVertCorr = (GRA_tpConteudoVert *) LIS_ObterValor(pVertCorr);

  /* Iterando sobre cada
     vertice da sua lista de arestas, para remove-lo da
     lista de arestas dos vértices vizinhos */

  IrInicioLista(conteudoVertCorr->pArestas) ;

  //Obtendo cada vértice pela sua lista de arestas
  while ((pVizinho = (LIS_tppLista) LIS_ObterValor(conteudoVertCorr->pArestas)) != NULL) { 

  /* Exclui conexão */
    GRA_DestruirAresta(pVertCorr, pVizinho);
  /*nao é necessario avancar o elemento corrente pois a aresta é excluida, 
  entao o elemento seguinte passar a ser o vizinho corrente*/
  }
  
  /*após deletar todas as conexoes com os vizinhos, o vertice corrente pode ser excluido*/
  if (LIS_ObterValor(pGrafo->pVertices) == pGrafo->pVertCorr){
  } //??????
  LIS_ExcluirElemento(pGrafo->pVertices);
  pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(pGrafo->pVertices);

  #ifdef _DEBUG
       pGrafo->numElem --;
  #endif

  return GRA_CondRetOK;
} /* Fim função: GRA  &Excluir Vertice Corrente */



   #ifdef _DEBUG

/***************************************************************************
*
*  Função: ARV  &Deturpar Grafo
*  ****/

   void GRA_Deturpar( void * pGrafoParm , int flag ) {

      GRA_tpGrafo * pGrafo = NULL;
      GRA_tpConteudoVert * ConteudoVertice;

      if ( pGrafoParm == NULL )
      {
         return;
      } /* if */

      pGrafo = ( GRA_tpGrafo * )( pGrafoParm );

      switch ( flag ){

      /* 1. Modifica o tipo do grafo */

         case 1:
         {
            CED_DefinirTipoEspaco( pGrafo , CED_ID_TIPO_VALOR_NULO ) ;
            break ;

         } /* fim ativa: Modifica o tipo do grafo */

      /* 2. Modifica o tipo do vertice corrente */

         case 2:
         {
            CED_DefinirTipoEspaco( pGrafo->pVertCorr , CED_ID_TIPO_VALOR_NULO ) ;
            break ;

         } /* fim ativa: Modifica o tipo do vertice corrente */

      /* 3. Modifica o tipo da cabeca da lista de vertices */

         case 3:
         {
            CED_DefinirTipoEspaco( pGrafo->pVertices , CED_ID_TIPO_VALOR_NULO ) ;
            break ;

         } /* fim ativa: Modifica a cabeca da lista vertices */

      /* 4. Anula ponteiro do vertice corrente */

         case 4:
         {
            pGrafo->pVertCorr = NULL ;
            break ;

         } /* fim ativa: Anula ponteiro do vertice corrente */


      /* 5. Anula ponteiro para a cabeça da lista de vertices */

         case 5:
         {
            pGrafo->pVertices = NULL ;
            break ;

         } /* fim ativa: Anula ponteiro para a cabeça de lista de vertices */


      /* 6. Faz vertice corrente apontar para lixo */

         case 6:
         {
            pGrafo->pVertCorr = ( LIS_tppLista )( EspacoLixo ) ;
            break ;

         } /* fim ativa: Faz verticecorrente apontar para lixo */


      /* 7. Faz cabeca da lista de vertices apontar para lixo */

         case 7:
         {
            pGrafo->pVertices = ( LIS_tppLista )( EspacoLixo ) ;
            break ;
         } /* fim ativa:Faz cabeca da lista de vertices apontar para lixo */


      /* Deturpa aresta */

         default :

       //  ConteudoVertice = (GRA_tpConteudoVert *) LIS_ObterValor(pGrafo->pVertCorr);

         if ( /*ConteudoVertice->pArestas != NULL*/ 1 )
         {

            switch ( flag ) {

            /* 9. Anula ponteiro da cabeca da lista de arestas */

               case 9:
               {
                  ConteudoVertice->pArestas = NULL;
                  break ;

               } /* fim ativa: Anula ponteiro da cabeca da lista de arestas */

            /* 10. Faz cabeca da lista de aresta apontar para lixo */

               case 10:
               {
                  ConteudoVertice->pArestas = ( LIS_tppLista )( EspacoLixo ) ;
                  break ;

               } /* fim ativa: Faz cabeca da lista de aresta apontar para lixo */

                               /* 11. Altera quantidade total de vertices */
                case 11:
                {
                  pGrafo->numElem = -1;
                  break;
                }

            /*12. Alterar numero de arestas do vertice */

              case 12:
              {
                ConteudoVertice->NumArestas = -1;
              }

            } /* fim seleciona: Deturpa aresta */

            break ;

         } /* fim ativa: Deturpa aresta */

      } /* fim seleciona: Vertice de GRA &Deturpar Grafo */

   } /* Fim função: GRA  &Deturpar Grafo */

#endif 

#ifdef _DEBUG
/***********************************************************************
*
*  $FC Função: GRA Verificar estrutura
*
***********************************************************************/


int GRA_VerificaEstrutura(GRA_tppGrafo pGrafo) {
  int numErros = 0;
  //GRA_tpConteudoVert * Vertice;
  
  printf("\nGRA_VerificarEstrura\n");
  //1. verifica se o tipo es datrutura é de fato o tipo esperado
  if ( GRA_TipoEspacoCabeca != CED_ObterTipoEspaco(pGrafo)) {
    printf("\nGRA_VerificarEstrura-1\n");
    CNT_CONTAR( "GRA_VerificarEstrura-1" );
    numErros++;
  }

  //2. verifica integridade do tamanho do espaco alocado   
  if ( sizeof(pGrafo) != CED_ObterTamanhoValor(pGrafo)) {
    CNT_CONTAR( "GRA_VerificarEstrura-2" );
    printf("\nGRA_VerificarEstrura-2 GrafoSize = %d, tamValor = %d\n", sizeof(pGrafo), CED_ObterTamanhoValor(pGrafo));
    numErros++;
  }

  if(LIS_AvancarElementoCorrente(pGrafo->pVertices, 0) == LIS_CondRetListaVazia){
    printf("\nGRA_VerificaListaVazia\n");
    printf("\nNUM ERROS =  %d\n", numErros);
    return numErros;

  }

  //3. chama as funcoes verificadoras das demais estruturas do grafo
  numErros += GRA_VerificaListaVertices(pGrafo->pVertices, pGrafo);
  numErros += GRA_VerificaVertice(pGrafo->pVertCorr, pGrafo);

  CNT_CONTAR( "GRA_VerificarEstrura-9" );
  printf("\nGRA_VerificarEstrura-9\n");
  return numErros;

}

int GRA_VerificaListaVertices(LIS_tppLista pVertices, GRA_tppGrafo pGrafo) {
  int numErros = 0;
  int count = 0;
  LIS_tppLista ListaVertice;
  //1. percorre a lista, acessando cada um dos elementos da lista vertices
  IrInicioLista(pVertices);

  printf("\nGRA_VerificarEstrura-1\n");
  if (pVertices == NULL) {
    numErros ++;
    //CNT_CONTAR("Verif");
    printf("\nGRA_VerificarEstrura-17\n");
  }

  CNT_CONTAR( "GRA_VerificarEstrura-4" );
  printf("\nGRA_VerificarEstrura-4\n");
  do {

    ListaVertice = (LIS_tppLista) LIS_ObterValor(pVertices);

    count++;

    numErros += GRA_VerificaVertice(ListaVertice, pGrafo);

    CNT_CONTAR( "GRA_VerificarEstrura-5" );
    printf("\nGRA_VerificarEstrura-5\n");
  } while(LIS_AvancarElementoCorrente(pVertices, 1) == LIS_CondRetOK);

  //2. checa se quantidade de vertices esta correta
  if (count != pGrafo->numElem) {
    numErros++;
    CNT_CONTAR( "GRA_VerificarEstrura-14" );
    printf("\nGRA_VerificarEstrura-14\n");
  }

  return numErros;
}

int GRA_VerificaVertice(LIS_tppLista pVertice, GRA_tppGrafo pGrafo) {
  int numErros = 0;

  printf("\nGRA_VerificarVertice\n");
  if (pVertice == NULL){
    numErros++;
    printf("\nGRA_VerificarVerticeNULL\n");
    return 0;
  }
  
  //1. verifica se o tipo da estrutura é de fato o tipo esperado
  if ( GRA_TipoEspacoVertice != CED_ObterTipoEspaco(pVertice)) {
    numErros++;
    CNT_CONTAR( "GRA_VerificarEstrura-6" );
    printf("\nGRA_VerificarEstrura-6\n");
  }

  //2. verifica integridade do tamanho do espaco alocado
  if (sizeof(pVertice) != CED_ObterTamanhoValor(pVertice)) {
    numErros++;
    CNT_CONTAR( "GRA_VerificarEstrura-7" );
    printf("\nGRA_VerificarEstrura-7\n");
  }

  //3. verifica conteudo do vertice
  numErros += GRA_VerificaConteudoVert((GRA_tpConteudoVert *) LIS_ObterValor(pVertice), pGrafo);

  CNT_CONTAR( "GRA_VerificarEstrura-8" );
  printf("\nGRA_VerificarEstrura-8\n");
  return numErros;
}

int GRA_VerificaConteudoVert(GRA_tpConteudoVert * pConteudoVert, GRA_tppGrafo pGrafo) {
  LIS_tppLista ListaArestas;
  int count, numErros = 0;
 
 printf("\nGRA_VerificarConteudo\n");
 //1. verifica se o tipo da estrutura é de fato o tipo esperado
  if (GRA_TipoPDado != CED_ObterTipoEspaco(pConteudoVert)) {
    numErros++;
    CNT_CONTAR( "GRA_VerificarEstrura-10" );
  }

  //2. verifica integridade do tamanho do espaco alocado
  if (sizeof(pConteudoVert) != CED_ObterTamanhoValor(pConteudoVert)) {
    numErros++;
    CNT_CONTAR( "GRA_VerificarEstrura-11" );
  }

  //3. Verifica numero de arestas
  ListaArestas = pConteudoVert->pArestas;

  if(ListaArestas == NULL)
    numErros++;

  IrInicioLista(ListaArestas);
  count = 0;
  do {
    count++;
    CNT_CONTAR( "GRA_VerificarEstrura-12" );
  } while(LIS_AvancarElementoCorrente(ListaArestas, 1) == LIS_CondRetOK);

  if(count != pConteudoVert->NumArestas){
    numErros++;
    CNT_CONTAR( "GRA_VerificarEstrura-13" );
  }

  //4. verifica ponteiro para a cabeca
   if(pConteudoVert->pCabeca != pGrafo){
      CNT_CONTAR( "GRA_VerificarEstrura-3" );
      printf("\nGRA_VerificarEstrura-3\n");
      numErros++;
   }

  return numErros;
}


#endif

  
