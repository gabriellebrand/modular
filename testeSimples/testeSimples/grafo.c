#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define GRAFO_OWN
#include "grafo.h"
#undef GRAFO_OWN

 /***********************************************************************
*  $TC Tipo de dados: GRA descritor da cabe�a do grafo
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
*  $TC Tipo de dados: GRA conte�do de um v�rtice
* *********************************************************************/

typedef struct GRA_tagConteudoVert {
  LIS_tppLista pArestas;
    /* ponteiro para a cabeca da lista de arestas do vertice */

  void * pDado;
    /* ponteiro para o valor do vertice */

  int (* compara)(void * pDado, void * pChaveID);

  void (* exclui) (void * pDado) ;

} GRA_tpConteudoVert;

/***** Prot�tipos das fun��es encapsuladas pelo m�dulo *****/

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
*  Fun��o: GRA  &Criar Grafo
* **************************************************************************/

GRA_tppGrafo GRA_criarGrafo(void (* ExcluirValor)(void * pDado), int (* CompararValor)(void * pDado, void * pChaveID)) {
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

 void GRA_destruirVertice(void *pDado) {
  LIS_tppLista pVertice;
  
  pVertice = (LIS_tppLista) pDado;

  LIS_DestruirLista(pVertice);
  pVertice = NULL;
 } /* Fim fun��o: GRA  &Destruir Vertice */

/***********************************************************************
*  $FC Fun��o: GRA - Destruir Conteudo do Vertice
*  $ED Descri��o da fun��o
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
} /* Fim fun��o: GRA &Destruir Conteudo Vertice */

/***************************************************************************
*  Fun��o: GRA  &Comparar V�rtice
*  $ED Descri��o da fun��o
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
} /* Fim fun��o: GRA  &Comparar Vertice */

/***************************************************************************
*  Fun��o: GRA  &Comparar Conteudo de V�rtice
*  $ED Descri��o da fun��o
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
*  Fun��o: GRA  &Destruir Grafo
* **************************************************************************/

GRA_tpCondRet GRA_destruirGrafo(GRA_tppGrafo *pGrafo) {

  if (!(*pGrafo)){
    return GRA_CondRetGrafoNaoExiste ;
  } /*if */

  LIS_DestruirLista((*pGrafo)->pVertices);
  
  free(*pGrafo);
  *pGrafo = NULL;

  return GRA_CondRetOK;
} /* Fim fun��o: GRA  &Destruir Grafo */

/***************************************************************************
*  Fun��o: GRA  &Criar Vertice
* **************************************************************************/

GRA_tpCondRet GRA_criarVertice(GRA_tppGrafo pGrafo, void *pDado, void *pChaveID) { 

  LIS_tppLista pVertice;
  LIS_tppLista pArestas;
  GRA_tpConteudoVert * pConteudoVert;

  if (!pGrafo) {
    return GRA_CondRetGrafoNaoExiste;
  } /* if */

  if(!pDado || !pChaveID) return GRA_CondRetValorNulo;
  
  /*verifica se j� existe um vertice com a chave escolhida*/
  if (GRA_irVertice(pGrafo, pChaveID) == GRA_CondRetOK) {
    return GRA_CondRetVerticeJaExiste;
  }

  pArestas = LIS_CriarLista(NULL, GRA_compararVertice);
  /*OBS: a fun��o de destrui��o de arestas n�o deve destruir seu pDado, pois ele est� referenciado tamb�m na lista v�rticeS */
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
  pConteudoVert->pDado = pDado;
  pConteudoVert->compara = pGrafo->compara;
  pConteudoVert->exclui = pGrafo->exclui;

  /* cria lista v�rtice de apenas um n� */
  pVertice = LIS_CriarLista(GRA_destruirConteudoVert, GRA_compararConteudoVert);
  if (!pVertice){
    return GRA_CondRetFaltouMemoria;
  }

  LIS_InserirElementoApos(pVertice, pConteudoVert);

  return GRA_inserirVertice(pGrafo, pVertice);
} /* Fim fun��o: GRA  &Criar Vertice */


/***************************************************************************
*  Fun��o: GRA  &Inserir Vertice
* **************************************************************************/

GRA_tpCondRet GRA_inserirVertice(GRA_tppGrafo pGrafo, LIS_tppLista pVertice) {
  if (!pVertice){
    return GRA_CondRetVerticeNaoExiste;
  } /* if */

  LIS_InserirElementoApos(pGrafo->pVertices, pVertice);
  pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(pGrafo->pVertices);
  return GRA_CondRetOK;
} /* Fim fun��o: GRA  &Inserir Vertice */

/***************************************************************************
*  Fun��o: GRA  &Ir Vertice
*  $ED Descri��o da fun��o
*  Percorre a lista de v�rtices do grafo at� encontrar o vertice correspondente � chave passada.
*  Essa funcao recebe um pChaveID que � a chave de busca do grafo.
*  O vertice corrente do grafo passa a ser o vertice buscado, caso seja encontrado.
*  Se n�o for encontrado, o vertice corrente continua o mesmo.
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
  return GRA_CondRetVerticeNaoExiste;
} /* Fim fun��o: GRA  &Ir Vertice */

/***************************************************************************
*  Fun��o: GRA  Ir Vizinho
*  $ED Descri��o da fun��o
*  Essa funcao recebe um pChaveID que � a chave de busca do grafo.
*  O vertice buscado passa a ser o vertice corrente do grafo , caso seja encontrado.
*  Se n�o for encontrado, o vertice corrente continua o mesmo.
*  A busca � feita na lista de arestas do vertice corrente.
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
} /* Fim fun��o: GRA  &Ir Vizinho */

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
} /* Fim fun��o: GRA  &Obter Corrente */

/***********************************************************************
*  $FC Fun��o: GRA - Obter Valor
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia do pDado contido dentro do vertice corrente.
*     - retorna NULL, se o grafo n�o existir (ponteiro nulo), ele retorna nulo. 
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
  return pConteudo->pDado;
} /* Fim fun��o: GRA  &Obter Valor */

/***********************************************************************
*  $FC Fun��o: GRA - Criar aresta
*  $ED Descri��o da fun��o
***********************************************************************/

GRA_tpCondRet GRA_criarAresta(GRA_tppGrafo pGrafo, void * pChaveID_1, void * pChaveID_2) {
  LIS_tppLista pVertice1, pVertice2;
  GRA_tpConteudoVert *conteudoVert1, *conteudoVert2;

  if (!pGrafo) { return GRA_CondRetGrafoNaoExiste; }
  if (!pChaveID_1 || !pChaveID_2) { return GRA_CondRetValorNulo; }
  
  /* passo1: obter a referencia para os vertices */
  if (GRA_irVertice (pGrafo, pChaveID_1) == GRA_CondRetOK) {
    pVertice1 = GRA_obterCorrente(pGrafo);
  } else { return GRA_CondRetVerticeNaoExiste; }
  
  if (GRA_irVertice (pGrafo, pChaveID_2) == GRA_CondRetOK) {
    pVertice2 = GRA_obterCorrente(pGrafo);
  } else { return GRA_CondRetVerticeNaoExiste; }

  /*obter o conteudo dos vertices*/
  conteudoVert1 = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice1);
  conteudoVert2 = (GRA_tpConteudoVert *) LIS_ObterValor(pVertice2);

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
} /* Fim fun��o: GRA  &Criar Aresta */

/***********************************************************************
*  $FC Fun��o: GRA - Excluir aresta
*  $ED Descri��o da fun��o
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
} /* Fim fun��o: GRA  &Excluir Aresta */

/***********************************************************************
*  $FC Fun��o: GRA - Destruir aresta
*  $ED Descri��o da fun��o
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
} /* Fim fun��o: GRA  &Destruir Aresta */

/***********************************************************************
*  $FC Fun��o: GRA - Liberar Aresta
*  $ED Descri��o da fun��o
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
} /* Fim fun��o: GRA  &Liberar Aresta */

/***********************************************************************
*  $FC Fun��o: GRA - Excluir V�rtice Corrente
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
     lista de arestas dos v�rtices vizinhos */

  IrInicioLista(conteudoVertCorr->pArestas) ;

  //Obtendo cada v�rtice pela sua lista de arestas
  while ((pVizinho = (LIS_tppLista) LIS_ObterValor(conteudoVertCorr->pArestas)) != NULL) { 

  /* Exclui conex�o */
    GRA_destruirAresta(pVertCorr, pVizinho);
  /* acho que nao � necessario avancar o elemento corrente pois a aresta � excluida, 
  entao o elemento seguinte passar a ser o vizinho corrente*/
  } //while (LIS_AvancarElementoCorrente(conteudoVertCorr->pArestas, 1) != LIS_CondRetFimLista);
  
  /*ap�s deletar todas as conexoes com os vizinhos, o vertice corrente pode ser excluido*/
  if (LIS_ObterValor(pGrafo->pVertices) == pGrafo->pVertCorr){
  }
  LIS_ExcluirElemento(pGrafo->pVertices);
  pGrafo->pVertCorr = (LIS_tppLista) LIS_ObterValor(pGrafo->pVertices);

  return GRA_CondRetOK;
} /* Fim fun��o: GRA  &Excluir Vertice Corrente */