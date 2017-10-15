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
        /* Vertice ja Existe */

 /* 12 */ GRA_CondRetArestaIlegal,
        /* Aresta para o proprio vértice */

 /* 13 */  GRA_CondRetValorNulo
        /* Ponteiro nulo */

   } GRA_tpCondRet ;

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

//MARK: TYPEDEF DEFINIDO AQUI PROVISORIAMENTE (até criar o .h)
typedef struct GRA_tagGrafo * GRA_tppGrafo ;

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

  void (* exclui) (void * pValor) ;

} GRA_tpConteudoVert;

/***** Protótipos das funções exportadas pelo módulo *****/

GRA_tppGrafo GRA_criarGrafo(void ( * ExcluirValor )( void * pValor ), int (*CompararValor)(void * pValor1, void * pValor2)); //done  
GRA_tpCondRet GRA_destruirGrafo(GRA_tppGrafo pGrafo); //done
GRA_tpCondRet GRA_irVertice (GRA_tppGrafo pGrafo, void *pValor); //done
GRA_tpCondRet GRA_irVizinho (GRA_tppGrafo pGrafo, void *pValor); //done
void * GRA_obterValor( GRA_tppGrafo pGrafo); //done
GRA_tpCondRet GRA_criarVertice(GRA_tppGrafo pGrafo, void *pValor); //done
GRA_tpCondRet GRA_excluirVertCorr(GRA_tppGrafo pGrafo); //done
GRA_tpCondRet GRA_criarAresta(GRA_tppGrafo pGrafo, void * pValor1, void * pValor2); //done
GRA_tpCondRet GRA_excluirAresta(GRA_tppGrafo pGrafo, void *pValor1, void *pValor2); //done
/********************************************************/

/***** Protótipos das funções encapsuladas pelo módulo *****/
void GRA_destruirVertice(void *pValor);
void GRA_destruirConteudoVert(void * conteudoVertice);
int GRA_compararVertice(void *pValor1, void *pValor2);
int GRA_compararConteudoVert(void *pValor1, void *pValor2);
GRA_tpCondRet GRA_inserirVertice(GRA_tppGrafo pGrafo, LIS_tppLista pVertice);
void GRA_destruirValorListaAresta(void * pValor);
GRA_tpCondRet GRA_destruirAresta(LIS_tppLista pVertice1 , LIS_tppLista pVertice2);
GRA_tpCondRet GRA_liberarAresta(LIS_tppLista pVertice1 , LIS_tppLista pVertice2);
LIS_tppLista GRA_obterCorrente(GRA_tppGrafo pGrafo); //done
/********************************************************/

/***************************************************************************
*  Função: GRA  &Criar Grafo
* **************************************************************************/

GRA_tppGrafo GRA_criarGrafo(void (* ExcluirValor)(void * pValor), int (* CompararValor)(void * pValor1, void * pValor2)) {
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

void GRA_destruirConteudoVert(void * conteudoVertice) {
  GRA_tpConteudoVert *conteudo;
  conteudo = (GRA_tpConteudoVert *) conteudoVertice; 

  conteudo->exclui(conteudo->pValor);
  LIS_DestruirLista(conteudo->pArestas) ;

  free(conteudoVertice);
  conteudoVertice = NULL;
} /* Fim função: GRA - Destruir Conteudo Vertice */

/***************************************************************************
*  Função: GRA  &Comparar Vértice
*  $ED Descrição da função
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
*  Função: GRA  &Comparar Conteudo de Vértice
*  $ED Descrição da função
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
*  Função: GRA  &Destruir Grafo
* **************************************************************************/

GRA_tpCondRet GRA_destruirGrafo(GRA_tppGrafo pGrafo) {

  if (!pGrafo){
    return GRA_CondRetGrafoNaoExiste ;
  } /*if */

  LIS_DestruirLista(pGrafo->pVertices);
  
  free(pGrafo);
  pGrafo = NULL;

  return GRA_CondRetOK;
} /* Fim função: GRA  &Destruir Grafo */

/***************************************************************************
*
*  Função: GRA  &Criar Vertice
* **************************************************************************/

GRA_tpCondRet GRA_criarVertice(GRA_tppGrafo pGrafo, void *pValor) {
  //TODO: VERIFICAR SE JÁ EXISTE UM VERTICE COM O PVALOR ESCOLHIDO
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
  /*OBS: a função de destruição de arestas não deve destruir seu pValor, pois ele está referenciado também na lista vérticeS */
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
  pConteudoVert->pValor = pValor;
  pConteudoVert->compara = pGrafo->compara;
  pConteudoVert->exclui = pGrafo->exclui;

  /* cria lista vértice de apenas um nó */
  pVertice = LIS_CriarLista(GRA_destruirConteudoVert, GRA_compararConteudoVert);
  if (!pVertice){
    return GRA_CondRetFaltouMemoria;
  }

  LIS_InserirElementoApos(pVertice, pConteudoVert);

  return GRA_inserirVertice(pGrafo, pVertice);
}

/***************************************************************************
*
*  Função: GRA  &Inserir Vertice
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
*  Função: GRA  Ir Vertice
*  $ED Descrição da função
*  Essa funcao recebe um pValor que é a chave de busca do grafo.
*  O vertice corrente do grafo passa a ser o vertice buscado, caso seja encontrado.
*  Se não for encontrado, o vertice corrente continua o mesmo.
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
*  Função: GRA  Ir Vizinho
*  $ED Descrição da função
*  Essa funcao recebe um pValor que é a chave de busca do grafo.
*  O vertice buscado passa a ser o vertice corrente do grafo , caso seja encontrado.
*  Se não for encontrado, o vertice corrente continua o mesmo.
*  A busca é feita na lista de arestas do vertice corrente.
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
*  $FC Função: GRA - Destruir Aresta
*  $ED Descrição da função
*    Ele nao faz nada com o valor1(vertice). Pois se voce matasse
*    esse valor, voce estaria matando o vértice em si.
*    Como não queremos isso, só ira ser apagada a referencia 
*    para tal valor.
***********************************************************************/

void GRA_destruirValorListaAresta(void * pValor) {}

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
}

/***********************************************************************
*  $FC Função: GRA - Obter Valor
*  $ED Descrição da função
*     Obtem a referência do pValor contido dentro do vertice corrente.
*     - retorna NULL, se o grafo não existir (ponteiro nulo), ele retorna nulo. 
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
*  $FC Função: GRA - Criar aresta
*  $ED Descrição da função
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
*  $FC Função: GRA - Excluir aresta
*  $ED Descrição da função
*     Exclui uma aresta entre dois vertices, atraves de suas chaves identificadoras
***********************************************************************/
GRA_tpCondRet GRA_excluirAresta(GRA_tppGrafo pGrafo, void *pValor1, void *pValor2) {
  LIS_tppLista pVertice1, pVertice2;

  if (!pGrafo) {
    return GRA_CondRetGrafoNaoExiste;
  }
  if(!pGrafo->pVertCorr){
    return GRA_CondRetGrafoVazio;
  }

  /*procura a referencia para o vertice 1 a partir da chave identificadora*/
  if(GRA_irVertice(pGrafo, pValor1) != GRA_CondRetOK) {
    return GRA_CondRetVerticeNaoExiste;
  }
  pVertice1 = GRA_obterCorrente(pGrafo);
  /*procura a referencia para o vertice 2 a partir da chave identificadora*/
  if(GRA_irVertice(pGrafo, pValor2) != GRA_CondRetOK) {
    return GRA_CondRetVerticeNaoExiste;
  }
  pVertice2 = GRA_obterCorrente(pGrafo);

  return GRA_destruirAresta(pVertice1 , pVertice2);
}

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
}

/***********************************************************************
*  $FC Função: GRA - Liberar Aresta
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
}

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
}