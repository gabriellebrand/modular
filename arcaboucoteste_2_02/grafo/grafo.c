#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define GRAFO_OWN
#include "grafo.h"
#undef GRAFO_OWN

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

  void (* exclui) (void * pDado) ;
  /*ponteiro para a funcao que compara o valor armazenado no vertice com a chave identificadora - retorna zero se forem iguais */

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

} GRA_tpConteudoVert;

/***** Protótipos das funções encapsuladas pelo módulo *****/

void GRA_destruirVertice(void *pDado);
void GRA_destruirConteudoVert(void * conteudoVertice);
int GRA_compararVertice(void *pDado, void *pChaveID);
int GRA_compararConteudoVert(void *pDado, void *pChaveID);
GRA_tpCondRet GRA_inserirVertice(GRA_tppGrafo pGrafo, LIS_tppLista pVertice);
void GRA_destruirValorListaAresta(void * pDado);
GRA_tpCondRet GRA_destruirAresta(LIS_tppLista pVertice1 , LIS_tppLista pVertice2);
GRA_tpCondRet GRA_liberarAresta(LIS_tppLista pVertice1 , LIS_tppLista pVertice2);
LIS_tppLista GRA_obterCorrente(GRA_tppGrafo pGrafo); //done

/********************************************************/

/***************************************************************************
*  Função: GRA  &Criar Grafo
* **************************************************************************/

GRA_tppGrafo GRA_criarGrafo(void (* ExcluirValor)(void * pDado), int (* CompararValor)(void * pDado, void * pChaveID)) {
  GRA_tpGrafo *pGrafo = NULL;

  pGrafo = (GRA_tpGrafo*)malloc(sizeof(GRA_tpGrafo));
  if (pGrafo == NULL) {
    return NULL;
  } /* if */

  pGrafo->pVertCorr = NULL; /* grafo está vazio, entao nao ha vertice corrente */
  pGrafo->compara = CompararValor;
  pGrafo->exclui = ExcluirValor;

  pGrafo->pVertices = LIS_CriarLista(GRA_destruirVertice, GRA_compararVertice);  
  /*cria a lista de vertices vazia passando a funcao que sabe destruir o valor do vertice*/
   
  if (pGrafo->pVertices == NULL) {
    free(pGrafo); /*libera memoria alocada para o grafo*/
    return NULL;
  } /*if */

  return pGrafo;
}/* Fim função: GRA  &Criar Grafo */

 /***********************************************************************
*  $FC Função: GRA - Destruir Vertice
*  $ED Descrição da função
*  Destroi a lista VERTICE
*  Essa funcao deve ser enviada como parametro do campo ExcluirValor da lista VERTICES
***********************************************************************/

 void GRA_destruirVertice(void *pDado) {
  LIS_tppLista pVertice;
  
  pVertice = (LIS_tppLista) pDado;

  LIS_DestruirLista(pVertice);
  pVertice = NULL;
 } /* Fim função: GRA  &Destruir Vertice */

/***********************************************************************
*  $FC Função: GRA - Destruir Conteudo do Vertice
*  $ED Descrição da função
*  Dando um free no dado armazenado pelo vertice, e destruindo a lista arestas
*  Essa funcao deve ser enviada como parametro do campo ExcluirValor da lista VERTICE
***********************************************************************/

void GRA_destruirConteudoVert(void * conteudoVertice) {
  GRA_tpConteudoVert *conteudo;
  conteudo = (GRA_tpConteudoVert *) conteudoVertice; 

  conteudo->exclui(conteudo->pDado);
  LIS_DestruirLista(conteudo->pArestas) ;

  free(conteudoVertice);
  conteudoVertice = NULL;
} /* Fim função: GRA &Destruir Conteudo Vertice */

/***************************************************************************
*  Função: GRA  &Comparar Vértice
*  $ED Descrição da função
*  Essa funcao deve ser passada para o campo 'compara' da lista VERTICES e da lista ARESTAS
*  **************************************************************************/

int GRA_compararVertice(void *pDado, void *pChaveID){
  LIS_tppLista pVertice;
  GRA_tpConteudoVert * pValorVert;
  
  /*faz um typecast do pDado (que deve ser uma lista VERTICE)*/
  pVertice = (LIS_tppLista) pDado;

  /*obtem o pDado da lista VERTICE e chama a funcao compara da propria lista vertice como valor de retorno */
  pValorVert = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice);
  return GRA_compararConteudoVert(pValorVert, pChaveID);
} /* Fim função: GRA  &Comparar Vertice */

/***************************************************************************
*  Função: GRA  &Comparar Conteudo de Vértice
*  $ED Descrição da função
*  Essa funcao deve ser passada para o campo 'compara' da lista VERTICE
* **************************************************************************/

int GRA_compararConteudoVert(void *pDado, void *pChaveID){
  GRA_tpConteudoVert * pValorVert;
  /*faz um typecast do pDado (que deve ser uma estrutura do tipo tpConteudoVert!)*/
  pValorVert = (GRA_tpConteudoVert *) pDado;

  /*chama a funcao compara do conteudo do vertice como valor de retorno */
  return pValorVert->compara(pValorVert->pDado, pChaveID);
}

/***************************************************************************
*  Função: GRA  &Destruir Grafo
* **************************************************************************/

GRA_tpCondRet GRA_destruirGrafo(GRA_tppGrafo *pGrafo) {

  if (!pGrafo){
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

GRA_tpCondRet GRA_criarVertice(GRA_tppGrafo pGrafo, void *pDado, void *pChaveID) { 

  LIS_tppLista pVertice;
  LIS_tppLista pArestas;
  GRA_tpConteudoVert * pConteudoVert;

  if (!pGrafo) {
    return GRA_CondRetGrafoNaoExiste;
  } /* if */

  /*verifica se já existe um vertice com a chave escolhida*/
  if (GRA_irVertice(pGrafo, pChaveID) == GRA_CondRetOK) {
    return GRA_CondRetVerticeJaExiste;
  }

  pArestas = LIS_CriarLista(NULL, GRA_compararVertice);
  /*OBS: a função de destruição de arestas não deve destruir seu pDado, pois ele está referenciado também na lista vérticeS */
  if (!pArestas) {
    return GRA_CondRetFaltouMemoria;
  } /* if */

  /* inicializando a estrutura que armazena o valor do vértice e sua lista de arestas */
  pConteudoVert = (GRA_tpConteudoVert *)malloc(sizeof(GRA_tpConteudoVert));

  if (!pConteudoVert) {
    LIS_DestruirLista(pArestas);
    return GRA_CondRetFaltouMemoria;
  } /* if */

  pConteudoVert->pArestas = pArestas;
  pConteudoVert->pDado = pDado;
  pConteudoVert->compara = pGrafo->compara;
  pConteudoVert->exclui = pGrafo->exclui;

  /* cria lista vértice de apenas um nó */
  pVertice = LIS_CriarLista(GRA_destruirConteudoVert, GRA_compararConteudoVert);
  if (!pVertice){
    return GRA_CondRetFaltouMemoria;
  }

  LIS_InserirElementoApos(pVertice, pConteudoVert);

  return GRA_inserirVertice(pGrafo, pVertice);
} /* Fim função: GRA  &Criar Vertice */


/***************************************************************************
*  Função: GRA  &Inserir Vertice
* **************************************************************************/

GRA_tpCondRet GRA_inserirVertice(GRA_tppGrafo pGrafo, LIS_tppLista pVertice) {
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

GRA_tpCondRet GRA_irVertice (GRA_tppGrafo pGrafo, void *pChaveID) {

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
  if (LIS_ProcurarPorConteudo(pGrafo->pVertices , pChaveID) == LIS_CondRetOK) {
    /*achou o vertice, entao vertice corrente passa a ser o vertice buscado*/
    pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(pVertices);
    return GRA_CondRetOK;
  }
  return GRA_CondRetNaoAchou;
} /* Fim função: GRA  &Ir Vertice */

/***************************************************************************
*  Função: GRA  Ir Vizinho
*  $ED Descrição da função
*  Essa funcao recebe um pChaveID que é a chave de busca do grafo.
*  O vertice buscado passa a ser o vertice corrente do grafo , caso seja encontrado.
*  Se não for encontrado, o vertice corrente continua o mesmo.
*  A busca é feita na lista de arestas do vertice corrente.
* **************************************************************************/

GRA_tpCondRet GRA_irVizinho (GRA_tppGrafo pGrafo, void *pChaveID) {

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
  if (LIS_ProcurarPorConteudo(listaArestas , pChaveID) == LIS_CondRetOK) {
    /*achou o vertice, entao vertice corrente passa a ser o vertice buscado*/
    pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(listaArestas);
    return GRA_CondRetOK;
  }
  return GRA_CondRetArestaNaoExiste;
} /* Fim função: GRA  &Ir Vizinho */

/***********************************************************************
*  $FC Função: GRA - Obter Corrente
*  $ED Descrição da função
*     Obtem a referência para o vertice corrente da lista vertices
*     Se o grafo não existir (ponteiro nulo), ele retorna nulo. 
*     Se o grafo estiver vazio (vertice corrente nulo), tambem é retornado nulo.
***********************************************************************/

LIS_tppLista GRA_obterCorrente(GRA_tppGrafo pGrafo) {
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

void * GRA_obterValor( GRA_tppGrafo pGrafo ) {
  LIS_tppLista pVerticeCorr;
  GRA_tpConteudoVert * pConteudo;
  pVerticeCorr = GRA_obterCorrente(pGrafo);
  if (!pGrafo) { return NULL; }
  if (!pVerticeCorr) { return NULL; }

  pConteudo = (GRA_tpConteudoVert *) LIS_ObterValor(pVerticeCorr);

  if (!pConteudo){ return NULL; }

  return pConteudo->pDado;
} /* Fim função: GRA  &Obter Valor */

/***********************************************************************
*  $FC Função: GRA - Criar aresta
*  $ED Descrição da função
***********************************************************************/

GRA_tpCondRet GRA_criarAresta(GRA_tppGrafo pGrafo, void * pChaveID_1, void * pChaveID_2) {
  LIS_tppLista pVertice1, pVertice2;
  GRA_tpConteudoVert *conteudoVert1, *conteudoVert2;

  if (!pGrafo) { return GRA_CondRetGrafoNaoExiste; }
  if (!pChaveID_1 || !pChaveID_2) { return GRA_CondRetValorNulo; }
  
  /* passo1: obter a referencia para os vertices */
  if (GRA_irVertice (pGrafo, pChaveID_1) == GRA_CondRetOK) {
    pVertice1 = GRA_obterCorrente(pGrafo);
  } else { return GRA_CondRetNaoAchou; }
  
  if (GRA_irVertice (pGrafo, pChaveID_2) == GRA_CondRetOK) {
    pVertice2 = GRA_obterCorrente(pGrafo);
  } else { return GRA_CondRetNaoAchou; }

  /*obter o conteudo dos vertices*/
  conteudoVert1 = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice1);
  conteudoVert2 = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice2);
  if(!conteudoVert1 || !conteudoVert2) {
    return GRA_CondRetVerticeNaoExiste;
  }

  /*passo2: verificar se os dois vertices sao iguais -> aresta para si mesmo nao pode */
  if (GRA_compararVertice(pVertice1, pChaveID_2) == 0) { return GRA_CondRetArestaIlegal; }

  /*passo3: verificar se ja existe aresta entre eles*/
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

  return GRA_CondRetOK;
} /* Fim função: GRA  &Criar Aresta */

/***********************************************************************
*  $FC Função: GRA - Excluir aresta
*  $ED Descrição da função
*     Exclui uma aresta entre dois vertices, atraves de suas chaves identificadoras
***********************************************************************/
GRA_tpCondRet GRA_excluirAresta(GRA_tppGrafo pGrafo, void *pChaveID_1, void *pChaveID_2) {
  LIS_tppLista pVertice1, pVertice2;

  if (!pGrafo) {
    return GRA_CondRetGrafoNaoExiste;
  }
  if(!pGrafo->pVertCorr){
    return GRA_CondRetGrafoVazio;
  }

  /*procura a referencia para o vertice 1 a partir da chave identificadora*/
  if(GRA_irVertice(pGrafo, pChaveID_1) != GRA_CondRetOK) {
    return GRA_CondRetVerticeNaoExiste;
  }
  pVertice1 = GRA_obterCorrente(pGrafo);
  /*procura a referencia para o vertice 2 a partir da chave identificadora*/
  if(GRA_irVertice(pGrafo, pChaveID_2) != GRA_CondRetOK) {
    return GRA_CondRetVerticeNaoExiste;
  }
  pVertice2 = GRA_obterCorrente(pGrafo);

  return GRA_destruirAresta(pVertice1 , pVertice2);
} /* Fim função: GRA  &Excluir Aresta */

/***********************************************************************
*  $FC Função: GRA - Destruir aresta
*  $ED Descrição da função
*  Destroi arestas entre duas listas vertice
***********************************************************************/
GRA_tpCondRet GRA_destruirAresta(LIS_tppLista pVertice1 , LIS_tppLista pVertice2) {

  if( !pVertice1 || !pVertice2 )
  {
    GRA_CondRetVerticeNaoExiste;
  } /* if */

  /*primeiro deleta o vertice 2 da lista de arestas do vertice 1*/
  if (GRA_liberarAresta(pVertice1 ,pVertice2) == GRA_CondRetArestaNaoExiste) {
    return GRA_CondRetArestaNaoExiste;
  }
  /*depois deleta o vertice 1 da lista de arestas do vertice 2*/
  if (GRA_liberarAresta(pVertice2 ,pVertice1) == GRA_CondRetArestaNaoExiste) {
    return GRA_CondRetArestaNaoExiste;
  }

  return GRA_CondRetOK;
} /* Fim função: GRA  &Destruir Aresta */

/***********************************************************************
*  $FC Função: GRA - Liberar Aresta
*  $ED Descrição da função
*     Libera vertice2 da lista de arestas do vertice1
***********************************************************************/
GRA_tpCondRet GRA_liberarAresta(LIS_tppLista pVertice1 , LIS_tppLista pVertice2) {
  GRA_tpConteudoVert *conteudo;

  /* acessar aresta do vertice 1*/
  conteudo = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice1);
  IrInicioLista(conteudo->pArestas);
  /* verificar se existe aresta entre os vertices */
  if (LIS_ProcurarValor(conteudo->pArestas, pVertice2) != LIS_CondRetOK) {
    return GRA_CondRetArestaNaoExiste;
  }
  /*excluir vertice2 das arestas do vertice 1*/
  LIS_ExcluirElemento(conteudo->pArestas);

  return GRA_CondRetOK;
} /* Fim função: GRA  &Liberar Aresta */

/***********************************************************************
*  $FC Função: GRA - Excluir Vértice Corrente
***********************************************************************/

GRA_tpCondRet GRA_excluirVertCorr(GRA_tppGrafo pGrafo) {
  LIS_tppLista pVertCorr, pVizinho;
  GRA_tpConteudoVert * conteudoVertCorr;

  if (!pGrafo) { return GRA_CondRetGrafoNaoExiste; }

  pVertCorr = GRA_obterCorrente(pGrafo);
  if (!pVertCorr) { return GRA_CondRetGrafoVazio; }

  conteudoVertCorr = (GRA_tpConteudoVert *) LIS_ObterValor(pVertCorr);

  /* Iterando sobre cada
     vertice da sua lista de arestas, para remove-lo da
     lista de arestas dos vértices vizinhos */

  IrInicioLista(conteudoVertCorr->pArestas) ;

  //Obtendo cada vértice pela sua lista de arestas
  while ((pVizinho = (LIS_tppLista) LIS_ObterValor(conteudoVertCorr->pArestas)) != NULL) { 

  /* Exclui conexão */
    GRA_destruirAresta(pVertCorr, pVizinho);
  /* acho que nao é necessario avancar o elemento corrente pois a aresta é excluida, 
  entao o elemento seguinte passar a ser o vizinho corrente*/
  } //while (LIS_AvancarElementoCorrente(conteudoVertCorr->pArestas, 1) != LIS_CondRetFimLista);
  
  /*após deletar todas as conexoes com os vizinhos, o vertice corrente pode ser excluido*/
  if (LIS_ObterValor(pGrafo->pVertices) == pGrafo->pVertCorr){
  }
  LIS_ExcluirElemento(pGrafo->pVertices);
  pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(pGrafo->pVertices);

  return GRA_CondRetOK;
} /* Fim função: GRA  &Excluir Vertice Corrente */