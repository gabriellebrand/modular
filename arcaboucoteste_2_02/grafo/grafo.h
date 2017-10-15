#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD Módulo de definição: GRA  Grafo Genérico Não-Dirigido
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
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       gba   08/10/2017 finalização
*     1       gba   08/10/2017 início desenvolvimento
*
*  $ED Descrição do módulo
*	  Implementa grafos genéricos não dirigidos.
*     Podem existir n grafos em operação simultaneamente.
*     Os grafos possuem uma cabeça encapsulando o seu estado.
*FINALIZAR DEPOIS
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/

#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */
typedef struct GRA_tagGrafo * GRA_tppGrafo;

/***********************************************************************
*  $TC Tipo de dados: LIS Condições de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
* *********************************************************************/

 typedef enum {
     
 /* 0 */ GRA_CondRetOK ,
               /* Concluiu corretamente */

 /* 1 */ GRA_CondRetGrafoVazio ,
               /* O grafo não contém vértices */

 /* 2 */ GRA_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

 /* 3 */ GRA_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um vértice do grafo */
       
 /* 4 */ GRA_CondRetGrafoNaoExiste,
         /* Grafo não existe ao inserir */

 /* 5 */ GRA_CondRetNaoPossuiAresta,
         /* Não possui aresta para o vertice */

 /* 6 */ GRA_CondRetVerticeNaoExiste,
        /* Vertice nao Existe */
     
 /* 7 */ GRA_CondRetArestaNaoExiste,
        /* Não possui arestas */

 /* 8 */ GRA_CondRetArestaJaExiste
        /* Ja possui essa aresta */,

 /* 9 */ GRA_CondRetVerticeJaExiste,
        /* Vertice ja Existe */

 /* 10 */ GRA_CondRetArestaIlegal,
        /* Aresta para o proprio vértice */

 /* 11 */  GRA_CondRetValorNulo
        /* Ponteiro nulo */

   } GRA_tpCondRet ;

 /***********************************************************************
*
*  $FC Função: GRA  &Criar grafo
*
*  $ED Descrição da função
*     Cria um grafo genérica não dirigido.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
***********************************************************************/
GRA_tppGrafo GRA_criarGrafo(void ( * ExcluirValor )( void * pValor ), int (*CompararValor)(void * pValor1, void * pValor2)); 

/***************************************************************************
*  Função: GRA  &Destruir Grafo
* **************************************************************************/
GRA_tpCondRet GRA_destruirGrafo(GRA_tppGrafo pGrafo);

/***************************************************************************
*  Função: GRA  Ir Vertice
*  $ED Descrição da função
*  		Essa funcao recebe um pValor que é a chave de busca do grafo.
*  		O vertice corrente do grafo passa a ser o vertice buscado, caso seja encontrado.
*  		Se não for encontrado, o vertice corrente continua o mesmo.
* **************************************************************************/
GRA_tpCondRet GRA_irVertice (GRA_tppGrafo pGrafo, void *pValor);

/***************************************************************************
*  Função: GRA  Ir Vizinho
*  $ED Descrição da função
*  Essa funcao recebe um pValor que é a chave de busca do grafo.
*  O vertice buscado passa a ser o vertice corrente do grafo , caso seja encontrado.
*  Se não for encontrado, o vertice corrente continua o mesmo.
*  A busca é feita na lista de arestas do vertice corrente.
* **************************************************************************/
GRA_tpCondRet GRA_irVizinho (GRA_tppGrafo pGrafo, void *pValor);

/***********************************************************************
*  $FC Função: GRA - Obter Valor
*  $ED Descrição da função
*     Obtem a referência do pValor contido dentro do vertice corrente.
*     - retorna NULL, se o grafo não existir (ponteiro nulo), ele retorna nulo. 
*     - retorna NULL, se o grafo estiver vazio (vertice corrente nulo).
*     - retorna NULL, se o conteudo do vertice nao existir.
*     - demais casos, retorna o valor do conteudo do vertice
***********************************************************************/
void * GRA_obterValor( GRA_tppGrafo pGrafo);

/***************************************************************************
*  Função: GRA  &Criar Vertice
* **************************************************************************/
GRA_tpCondRet GRA_criarVertice(GRA_tppGrafo pGrafo, void *pValor);

/***********************************************************************
*  $FC Função: GRA - Excluir Vértice Corrente
***********************************************************************/
GRA_tpCondRet GRA_excluirVertCorr(GRA_tppGrafo pGrafo);

/***********************************************************************
*  $FC Função: GRA - Criar aresta
*  $ED Descrição da função
***********************************************************************/
GRA_tpCondRet GRA_criarAresta(GRA_tppGrafo pGrafo, void * pValor1, void * pValor2);

/***********************************************************************
*  $FC Função: GRA - Excluir aresta
*  $ED Descrição da função
*     Exclui uma aresta entre dois vertices, atraves de suas chaves identificadoras
***********************************************************************/
GRA_tpCondRet GRA_excluirAresta(GRA_tppGrafo pGrafo, void *pValor1, void *pValor2);

#undef GRAFO_EXT

/********** Fim do módulo de definição: GRA  Grafo não dirigido **********/

#else
#endif

