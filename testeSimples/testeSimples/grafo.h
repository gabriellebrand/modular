#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: GRA  Grafo Gen�rico N�o-Dirigido
*
*  Arquivo gerado:              GRAFO.h
*  Letras identificadoras:      GRA
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 T2
*  Gestor:  LES/DI/PUC-Rio
*  Autores: gba - Gabrielle Brandemburg dos Anjos
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       gba   14/10/2017 finaliza��o
*     1       gba   08/10/2017 in�cio desenvolvimento
*
*  $ED Descri��o do m�dulo
*     Implementa grafos gen�ricos n�o dirigidos.
*     Podem existir n grafos em opera��o simultaneamente.
*     Os grafos possuem uma cabe�a encapsulando o seu estado.
*     
*     Cada grafo � homog�neo quanto ao tipo dos dados que armazena.
*
*     Os ponteiros para os dados s�o copiados para elementos do v�rtice.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um v�rtice a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*     O controle de busca de um v�rtice 
*
*     Cada grafo referencia uma fun��o que determina como devem ser
*        desalocados os dados nele contidos e uma fun��o que determina 
*        como devem ser identificados os dados nele contidos.
*
*     A fun��o de libera��o dos valores (ExcluirValor) contidos nos v�rtices deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*     A fun��o de compara��o (CompararValor) dos valores contidos nos v�rtices deve ser 
*        capaz de identificar o valor que est� armazenado no v�rtice atrav�s de uma chave
*        identificadora definida pelo cliente. Essa fun��o deve receber dois argumentos
*        no qual um � o dado contido no v�rtice e o outro � a chave identificadora.
*        � obrigat�rio que essa fun��o retorne ZERO caso a chave identificadora corresponda
*        ao dado armazenado. Dessa forma, o identificador do v�rtice � gen�rico e definido pelo
*        cliente, podendo ser uma string, um inteiro, ou qualquer outra estrutura, por exemplo.
*        
*
***************************************************************************/

#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

#include "LISTA.H"

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um grafo */
typedef struct GRA_tagGrafo * GRA_tppGrafo;

/***********************************************************************
*  $TC Tipo de dados: GRA Condi��es de retorno
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do grafo
* *********************************************************************/

 typedef enum {
     
 /* 0 */ GRA_CondRetOK ,
               /* Concluiu corretamente */

 /* 1 */ GRA_CondRetGrafoVazio ,
               /* O grafo n�o cont�m v�rtices */

 /* 2 */ GRA_CondRetFaltouMemoria,
               /* Faltou mem�ria ao tentar criar um v�rtice do grafo */
       
 /* 3 */ GRA_CondRetGrafoNaoExiste,
         /* Grafo n�o existe ao inserir */

 /* 4 */ GRA_CondRetNaoPossuiAresta,
         /* N�o possui aresta para o vertice */

 /* 5 */ GRA_CondRetVerticeNaoExiste,
        /* Vertice nao Existe */
     
 /* 6 */ GRA_CondRetArestaNaoExiste,
        /* N�o possui arestas */

 /* 7 */ GRA_CondRetArestaJaExiste
        /* Ja possui essa aresta */,

 /* 8 */ GRA_CondRetVerticeJaExiste,
        /* Vertice ja Existe */

 /* 9 */ GRA_CondRetArestaIlegal,
        /* Aresta para o proprio v�rtice */

 /* 10 */  GRA_CondRetValorNulo
        /* Ponteiro nulo */

   } GRA_tpCondRet ;

 /***********************************************************************
*  $FC Fun��o: GRA  &Criar grafo
*
*  $ED Descri��o da fun��o
*     Cria um grafo gen�rico n�o dirigido.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     O identificador usado nos v�rtices do grafo � gen�rico e � definido
*       pela fun��o CompararValor passada como argumento na cria��o.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*     CompararValor - ponteiro para a fun��o que compara um dado armazenado
*                     no v�rtice com uma chave identificadora. Deve retornar
*                     zero caso o identificador corresponda ao dado.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o grafo.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem este grafo.
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
***********************************************************************/
GRA_tppGrafo GRA_criarGrafo(void ( * ExcluirValor )( void * pDado ), int (*CompararValor)(void * pDado, void * pChaveID)); 

/***********************************************************************
*
*  $FC Fun��o: GRA  &Destruir Grafo
*
*  $ED Descri��o da fun��o
*     Destr�i o grafo fornecido.
*     O par�metro ponteiro para o grafo n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, o grafo resultar�
*     estruturalmente incorreto.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo
*
*  $FV Valor retornado
*     GRA_CondRetOK                - destruiu sem problemas
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo � nulo
***********************************************************************/
GRA_tpCondRet GRA_destruirGrafo(GRA_tppGrafo *pGrafo);

/***************************************************************************
*  Fun��o: GRA  &Ir Vertice
*  $ED Descri��o da fun��o
*     Anda por todos os v�rtices do grafo at� encontrar o v�rtice
*     correspondente � chave identificadora passada como par�metro.
*     O vertice corrente do grafo passa a ser o vertice buscado, caso seja encontrado.
*     Se n�o for encontrado, o vertice corrente continua o mesmo.
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo
*     pChaveID - ponteiro para a chave identificadora do vertice
*     
*  $FV Valor retornado
*     GRA_CondRetOK                - encontrou o v�rtice e o colocou como corrente
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo � nulo
*     GRA_CondRetGrafoVazio        - caso o grafo esteja vazio (vertice corrente nulo)
*     GRA_CondRetVerticeNaoExiste  - vertice com a chaveID correspondente n�o foi encontrado
* **************************************************************************/
GRA_tpCondRet GRA_irVertice (GRA_tppGrafo pGrafo, void *pChaveID);

/***************************************************************************
*  Fun��o: GRA  &Ir Vizinho
*  $ED Descri��o da fun��o
*     Percore as arestas do v�rtice corrente at� encontrar o v�rtice
*     correspondente � chave identificadora passada como par�metro.
*     O vertice buscado passa a ser o vertice corrente do grafo , caso seja encontrado.
*     Se n�o for encontrado, o vertice corrente continua o mesmo.
*     A busca � feita nas arestas do vertice corrente.
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo
*     pChaveID - ponteiro para a chave identificadora do vertice vizinho
*
*  $FV Valor retornado
*     GRA_CondRetOK                - encontrou o v�rtice e o colocou como corrente
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo � nulo
*     GRA_CondRetGrafoVazio        - caso o grafo esteja vazio (vertice corrente nulo)
*     GRA_CondRetArestaNaoExiste   - vizinho com a chaveID correspondente n�o foi encontrado nas arestas do vertice corrente
*     GRA_CondRetValorNulo         - se o conte�do do v�rtice corrente for nulo
*     GRA_CondRetNaoPossuiAresta   - se o v�rtice corrente n�o possuir nenhuma aresta
* **************************************************************************/
GRA_tpCondRet GRA_irVizinho (GRA_tppGrafo pGrafo, void *pChaveID);

/***********************************************************************
*  $FC Fun��o: GRA &Obter Valor
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia do pDado contido dentro do vertice corrente.
*
*  $EP Par�metros
*     pGrafo - ponteiro para o grafo
*     
*  $FV Valor retornado
*     NULL    - se o grafo n�o existir (ponteiro nulo), ele retorna nulo. 
*     NULL    - se o grafo estiver vazio (vertice corrente nulo).
*     NULL    - se o conteudo do vertice nao existir.
*     !=NULL  - retorna o valor do conteudo do vertice
***********************************************************************/
void * GRA_obterValor( GRA_tppGrafo pGrafo);

/***********************************************************************
*  $FC Fun��o: GRA - Obter Valor
*  $ED Descri��o da fun��o
*     Cria um novo v�rtice e insere ele no grafo.
*     Se inserido corretamente, o novo v�rtice passa a ser o v�rtice corrente.
*     Faz uma busca para verificar se j� existe um v�rtice com a chaveID passada.
*
*  $EP Par�metros
*     pGrafo    - ponteiro para o grafo
*     pDado     - ponteiro para o dado a ser armazenado no v�rtice
*     pChaveID  - chade idenficadora do v�rtice corrente
*                (esta chave deve estar contida dentro da estrutura do pDado, 
*                 pois ela n�o � copiada para o v�rtice separadamente!)
*     
*  $FV Valor retornado
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo � nulo
*     GRA_CondRetVerticeJaExiste   - j� existe um v�rtice com a chaveID correspondente
*     GRA_CondRetFaltouMemoria     - faltou memoria para aloca��o do novo v�rtice
*     GRA_CondRetOK                - v�rtice foi criado e inserido ao grafo corretamente
*     
***********************************************************************/
GRA_tpCondRet GRA_criarVertice(GRA_tppGrafo pGrafo, void *pDado, void *pChaveID);

/***********************************************************************
*  $FC Fun��o: GRA - Excluir V�rtice Corrente
*  $ED Descri��o da fun��o
*     Exclui o v�rtice corrente do grafo, incluindo suas arestas.
*     Apaga todas as refer�ncias do v�rtice das arestas dos vizinhos.
*     Vertice corrente passa a ser qualquer um.
*
*  $EP Par�metros
*     pGrafo    - ponteiro para o grafo
*     
*  $FV Valor retornado
*     GRA_CondRetValorNulo         - se o ponteiro ou a chaveID forem nulas
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo � nulo
*     GRA_CondRetGrafoVazio        - caso o grafo esteja vazio (vertice corrente nulo)
*     GRA_CondRetOK                - v�rtice foi exclu�do
***********************************************************************/
GRA_tpCondRet GRA_excluirVertCorr(GRA_tppGrafo pGrafo);

/***********************************************************************
*  $FC Fun��o: GRA - Criar aresta
*  $ED Descri��o da fun��o
*     Cria uma aresta entre os dois v�rtices correspondentes �s chaveID's passadas.
*
*  $EP Par�metros
*     pGrafo     - ponteiro para o grafo
*     pChaveID_1 - ponteiro para a chave identificadora correspondente ao v�rtice 1
*     pChaveID_2 - ponteiro para a chave identificadora correspondente ao v�rtice 2
*     
*  $FV Valor retornado
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo � nulo
*     GRA_CondRetGrafoVazio        - caso o grafo esteja vazio (vertice corrente nulo)
*     GRA_CondRetVerticeNaoExiste  - n�o encontrou o v�rtice 1 ou 2 no grafo
*     GRA_CondRetArestaIlegal      - tentativa de conectar um grafo a si mesmo
*     GRA_CondRetArestaJaExiste    - os dois v�rtices j� est�o conectados
*     GRA_CondRetFaltouMemoria     - faltou memoria na hora de alocar a aresta entre os vertice
*     GRA_CondRetOK                - vertices foram conectados corretamente
***********************************************************************/
GRA_tpCondRet GRA_criarAresta(GRA_tppGrafo pGrafo, void * pChaveID_1, void * pChaveID_2);

/***********************************************************************
*  $FC Fun��o: GRA - Excluir aresta
*  $ED Descri��o da fun��o
*     Exclui uma aresta entre dois vertices, atraves de suas chaves identificadoras.
*
*  $EP Par�metros
*     pGrafo     - ponteiro para o grafo
*     pChaveID_1 - ponteiro para a chave identificadora correspondente ao v�rtice 1
*     pChaveID_2 - ponteiro para a chave identificadora correspondente ao v�rtice 2
*
*  $FV Valor retornado
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo � nulo
*     GRA_CondRetGrafoVazio        - caso o grafo esteja vazio (vertice corrente nulo)
*     GRA_CondRetVerticeNaoExiste  - n�o encontrou o v�rtice 1 ou 2 no grafo
*     GRA_CondRetArestaNaoExiste   - n�o h� aresta entre os v�rtices
*     GRA_CondRetOK                - excluiu aresta com corretamente
***********************************************************************/
GRA_tpCondRet GRA_excluirAresta(GRA_tppGrafo pGrafo, void *pChaveID_1, void *pChaveID_2);

#undef GRAFO_EXT

/********** Fim do m�dulo de defini��o: GRA  Grafo n�o dirigido **********/

#else
#endif