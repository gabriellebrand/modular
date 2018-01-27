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
*           wbs - Wellington Bezerra da Silva
*           gc  - Gabriel Cantergiani
*
*  $HA Histórico de evolução:
*     Versão  Autor             Data      Observações
*     1       gba, wbs, gc   14/10/2017   finalização
*     1       gba, wbs, gc   08/10/2017   início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa grafos genéricos não dirigidos.
*     Podem existir n grafos em operação simultaneamente.
*     Os grafos possuem uma cabeça encapsulando o seu estado.
*     
*     Cada grafo é homogêneo quanto ao tipo dos dados que armazena.
*
*     Os ponteiros para os dados são copiados para elementos do vértice.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um vértice a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*     O controle de busca de um vértice 
*
*     Cada grafo referencia uma função que determina como devem ser
*        desalocados os dados nele contidos e uma função que determina 
*        como devem ser identificados os dados nele contidos.
*
*     A função de liberação dos valores (ExcluirValor) contidos nos vértices deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*     A função de comparação (CompararValor) dos valores contidos nos vértices deve ser 
*        capaz de identificar o valor que está armazenado no vértice através de uma chave
*        identificadora definida pelo cliente. Essa função deve receber dois argumentos
*        no qual um é o dado contido no vértice e o outro é a chave identificadora.
*        É obrigatório que essa função retorne ZERO caso a chave identificadora corresponda
*        ao dado armazenado. Dessa forma, o identificador do vértice é genérico e definido pelo
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

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um grafo */
typedef struct GRA_tagGrafo * GRA_tppGrafo;

/***********************************************************************
*  $TC Tipo de dados: GRA Condições de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do grafo
* *********************************************************************/

 typedef enum {
     
 /* 0 */ GRA_CondRetOK ,
               /* Concluiu corretamente */

 /* 1 */ GRA_CondRetGrafoVazio ,
               /* O grafo não contém vértices */

 /* 2 */ GRA_CondRetFaltouMemoria,
               /* Faltou memória ao tentar criar um vértice do grafo */
       
 /* 3 */ GRA_CondRetGrafoNaoExiste,
         /* Grafo não existe ao inserir */

 /* 4 */ GRA_CondRetNaoPossuiAresta,
         /* Não possui aresta para o vertice */

 /* 5 */ GRA_CondRetVerticeNaoExiste,
        /* Vertice nao Existe */
     
 /* 6 */ GRA_CondRetArestaNaoExiste,
        /* Não possui arestas */

 /* 7 */ GRA_CondRetArestaJaExiste
        /* Ja possui essa aresta */,

 /* 8 */ GRA_CondRetVerticeJaExiste,
        /* Vertice ja Existe */

 /* 9 */ GRA_CondRetArestaIlegal,
        /* Aresta para o proprio vértice */

 /* 10 */  GRA_CondRetValorNulo
        /* Ponteiro nulo */

   } GRA_tpCondRet ;


/***********************************************************************
*
*  $TC Tipo de dados: ARV Modos de deturpar
*
*
***********************************************************************/

#ifdef _DEBUG

   typedef enum {

         DeturpaTipoGrafo                 =  1 ,
               /* Modifica o tipo do grafo */

         DeturpaTipoVerticeCorrente       =  2 ,
               /* Modifica o tipo do vertice corrente */

         DeturpaTipoCabecaVertices        =  3 ,
               /* Modifica o tipo da cabeca da lista de vertices */

         DeturpaVerticeCorrenteNulo       =  4 ,
               /* Anula ponteiro do vertice corrente */

         DeturpaCabecaVerticesNulo        =  5 ,
               /* Anula ponteiro para a cabeça da lista de vertices */

         DeturpaVerticeCorrenteLixo       =  6 ,
               /* Faz vertice corrente apontar para lixo */

         DeturpaCabecaVerticesLixo        =  7 ,
               /* Faz cabeca da lista de vertices apontar para lixo */

         DeturpaTipoAresta                =  8 ,
               /* Modifica tipo da aresta */

         DeturpaCabecaArestasNulo         =  9 ,
               /* Anula ponteiro da cabeca da lista de arestas */

         DeturpaCabecaArestasLixo         = 10 ,
               /* Faz cabeca da lista de aresta apontar para lixo */

   } ARV_tpModosDeturpacao ;

#endif


 /***********************************************************************
*  $FC Função: GRA  &Criar grafo
*
*  $ED Descrição da função
*     Cria um grafo genérico não dirigido.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     O identificador usado nos vértices do grafo é genérico e é definido
*       pela função CompararValor passada como argumento na criação.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído. Pode ser NULL se não precisar 
*                     liberar o dado alocado.
*                     Ver descrição do módulo.
*     CompararValor - ponteiro para a função que compara um dado armazenado
*                     no vértice com uma chave identificadora. Deve retornar
*                     zero caso o identificador corresponda ao dado.
*                     Ver descrição do módulo. 
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para o grafo.
*     Este ponteiro será utilizado pelas funções que manipulem este grafo.
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
***********************************************************************/
GRA_tppGrafo GRA_CriarGrafo(void ( * ExcluirValor )( void * pDado ), int (*CompararValor)(void * pDado, void * pChaveID)); 

/***********************************************************************
*
*  $FC Função: GRA  &Destruir Grafo
*
*  $ED Descrição da função
*     Destrói o grafo fornecido.
*     O parâmetro ponteiro para o grafo não é modificado.
*     Se ocorrer algum erro durante a destruição, o grafo resultará
*     estruturalmente incorreto.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo
*
*  $FV Valor retornado
*     GRA_CondRetOK                - destruiu sem problemas
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo é nulo
***********************************************************************/
GRA_tpCondRet GRA_DestruirGrafo(GRA_tppGrafo *pGrafo);

/***************************************************************************
*  Função: GRA  &Ir Vertice
*  $ED Descrição da função
*     Anda por todos os vértices do grafo até encontrar o vértice
*     correspondente à chave identificadora passada como parâmetro.
*     O vertice corrente do grafo passa a ser o vertice buscado, caso seja encontrado.
*     Se não for encontrado, o vertice corrente continua o mesmo.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo
*     pChaveID - ponteiro para a chave identificadora do vertice
*     
*  $FV Valor retornado
*     GRA_CondRetOK                - encontrou o vértice e o colocou como corrente
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo é nulo
*     GRA_CondRetGrafoVazio        - caso o grafo esteja vazio (vertice corrente nulo)
*     GRA_CondRetVerticeNaoExiste  - vertice com a chaveID correspondente não foi encontrado
* **************************************************************************/
GRA_tpCondRet GRA_IrVertice (GRA_tppGrafo pGrafo, void *pChaveID);

/***************************************************************************
*  Função: GRA  &Ir Vizinho
*  $ED Descrição da função
*     Percore as arestas do vértice corrente até encontrar o vértice
*     correspondente à chave identificadora passada como parâmetro.
*     O vertice buscado passa a ser o vertice corrente do grafo , caso seja encontrado.
*     Se não for encontrado, o vertice corrente continua o mesmo.
*     A busca é feita nas arestas do vertice corrente.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo
*     pChaveID - ponteiro para a chave identificadora do vertice vizinho
*
*  $FV Valor retornado
*     GRA_CondRetOK                - encontrou o vértice e o colocou como corrente
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo é nulo
*     GRA_CondRetGrafoVazio        - caso o grafo esteja vazio (vertice corrente nulo)
*     GRA_CondRetArestaNaoExiste   - vizinho com a chaveID correspondente não foi encontrado nas arestas do vertice corrente
*     GRA_CondRetValorNulo         - se o conteúdo do vértice corrente for nulo
*     GRA_CondRetNaoPossuiAresta   - se o vértice corrente não possuir nenhuma aresta
* **************************************************************************/
GRA_tpCondRet GRA_IrVizinho (GRA_tppGrafo pGrafo, void *pChaveID);

/***********************************************************************
*  $FC Função: GRA &Obter Valor
*  $ED Descrição da função
*     Obtem a referência do pDado contido dentro do vertice corrente.
*
*  $EP Parâmetros
*     pGrafo - ponteiro para o grafo
*     
*  $FV Valor retornado
*     NULL    - se o grafo não existir (ponteiro nulo), ele retorna nulo. 
*     NULL    - se o grafo estiver vazio (vertice corrente nulo).
*     NULL    - se o conteudo do vertice nao existir.
*     !=NULL  - retorna o valor do conteudo do vertice
***********************************************************************/
void * GRA_ObterValor( GRA_tppGrafo pGrafo);

/***********************************************************************
*  $FC Função: GRA - Obter Valor
*  $ED Descrição da função
*     Cria um novo vértice e insere ele no grafo.
*     Se inserido corretamente, o novo vértice passa a ser o vértice corrente.
*     Faz uma busca para verificar se já existe um vértice com a chaveID passada.
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para o grafo
*     pDado     - ponteiro para o dado a ser armazenado no vértice
*     pChaveID  - chade idenficadora do vértice corrente
*                (esta chave deve estar contida dentro da estrutura do pDado, 
*                 pois ela não é copiada para o vértice separadamente!)
*     
*  $FV Valor retornado
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo é nulo
*     GRA_CondRetVerticeJaExiste   - já existe um vértice com a chaveID correspondente
*     GRA_CondRetFaltouMemoria     - faltou memoria para alocação do novo vértice
*     GRA_CondRetOK                - vértice foi criado e inserido ao grafo corretamente
*     
***********************************************************************/
GRA_tpCondRet GRA_CriarVertice(GRA_tppGrafo pGrafo, void *pDado, void *pChaveID);

/***********************************************************************
*  $FC Função: GRA - Excluir Vértice Corrente
*  $ED Descrição da função
*     Exclui o vértice corrente do grafo, incluindo suas arestas.
*     Apaga todas as referências do vértice das arestas dos vizinhos.
*     Vertice corrente passa a ser qualquer um.
*
*  $EP Parâmetros
*     pGrafo    - ponteiro para o grafo
*     
*  $FV Valor retornado
*     GRA_CondRetValorNulo         - se o ponteiro ou a chaveID forem nulas
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo é nulo
*     GRA_CondRetGrafoVazio        - caso o grafo esteja vazio (vertice corrente nulo)
*     GRA_CondRetOK                - vértice foi excluído
***********************************************************************/
GRA_tpCondRet GRA_ExcluirVertCorr(GRA_tppGrafo pGrafo);

/***********************************************************************
*  $FC Função: GRA - Criar aresta
*  $ED Descrição da função
*     Cria uma aresta entre os dois vértices correspondentes às chaveID's passadas.
*
*  $EP Parâmetros
*     pGrafo     - ponteiro para o grafo
*     pChaveID_1 - ponteiro para a chave identificadora correspondente ao vértice 1
*     pChaveID_2 - ponteiro para a chave identificadora correspondente ao vértice 2
*     
*  $FV Valor retornado
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo é nulo
*     GRA_CondRetGrafoVazio        - caso o grafo esteja vazio (vertice corrente nulo)
*     GRA_CondRetVerticeNaoExiste  - não encontrou o vértice 1 ou 2 no grafo
*     GRA_CondRetArestaIlegal      - tentativa de conectar um grafo a si mesmo
*     GRA_CondRetArestaJaExiste    - os dois vértices já estão conectados
*     GRA_CondRetFaltouMemoria     - faltou memoria na hora de alocar a aresta entre os vertice
*     GRA_CondRetOK                - vertices foram conectados corretamente
***********************************************************************/
GRA_tpCondRet GRA_CriarAresta(GRA_tppGrafo pGrafo, void * pChaveID_1, void * pChaveID_2);

/***********************************************************************
*  $FC Função: GRA - Excluir aresta
*  $ED Descrição da função
*     Exclui uma aresta entre dois vertices, atraves de suas chaves identificadoras.
*
*  $EP Parâmetros
*     pGrafo     - ponteiro para o grafo
*     pChaveID_1 - ponteiro para a chave identificadora correspondente ao vértice 1
*     pChaveID_2 - ponteiro para a chave identificadora correspondente ao vértice 2
*
*  $FV Valor retornado
*     GRA_CondRetGrafoNaoExiste    - ponteiro para o grafo é nulo
*     GRA_CondRetGrafoVazio        - caso o grafo esteja vazio (vertice corrente nulo)
*     GRA_CondRetVerticeNaoExiste  - não encontrou o vértice 1 ou 2 no grafo
*     GRA_CondRetArestaNaoExiste   - não há aresta entre os vértices
*     GRA_CondRetOK                - excluiu aresta com corretamente
***********************************************************************/
GRA_tpCondRet GRA_ExcluirAresta(GRA_tppGrafo pGrafo, void *pChaveID_1, void *pChaveID_2);

#undef GRAFO_EXT

/********** Fim do módulo de definição: GRA  Grafo não dirigido **********/

#else
#endif