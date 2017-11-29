#if ! defined( PERFIL_ )
#define PERFIL_
/***************************************************************************
*  $MCD Módulo de definição: PER  Módulo Perfil
*
*  Arquivo gerado:              PERFIL.h
*  Letras identificadoras:      PER
*
*  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 AutomatizaÁ„o dos testes de mÛdulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores:    GB - Gabrielle Brandenburg
                GC - Gabriel Cantergiani
                WB - Wellingotn Bezerra
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observaçõess
*     1.0       WB        02/out/2017       Criação do módulo
*     1.1       WB        14/out/2017       Alteração da função criarPerfil
*
*  $ED Descrição do módulo
*     Implementa o módulo usuário.
*     
***************************************************************************/

#if defined( PERFIL_OWN )
   #define PERFIL_EXT
#else
   #define PERFIL_EXT extern
#endif

#include "LISTA.H"
#include "MENSAGEM.H"


/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um Perfil */

typedef struct PER_tagPerfil * PER_tppPerfil;


/***********************************************************************
*
*  $TC Tipo de dados: PER Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do modulo Perfil
*
***********************************************************************/

   typedef enum {
     
 /* 0 */ PER_CondRetOK,
               /* Concluiu corretamente */

 /* 1 */ PER_CondRetFaltouMemoria,
               /* Faltou memoria */

 /* 2 */ PER_CondRetPonteiroNulo,
      /* Ponteiro Nulo */

 /* 3 */ PER_CondRetStringVazia,
      /* String vazia */

 /* 4 */ PER_CondRetValorInvalido,
      /* Valor de input invalido */

/* 5 */  PER_CondRetNaoAchou
      /* Nao encontrou mensagem para o perfil solicitado */    
   } PER_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PER  &Criar Perfil
*
*  $ED Descrição da função
*     Cria um Perfil
*
*  $EP Parâmetros
*     pNome - nome do perfil a ser criado
*     pEmail - email do perfil a ser criado
*     pCidade - cidade do perfil a ser criado
*     genero  - genero do perfil a ser criado
*     pDataNasc - Data de Nascimento do perfil a ser criado
*
*  $FV Valor retornado
*   Se executou corretamente retorna o ponteiro para um Perfil.
*
*   Se ocorreu algum erro, por exemplo falta de memoria ou dados errados,
*   a funcao retorna NULL.
*
***********************************************************************/

   PER_tppPerfil PER_CriarPerfil( char *pNome, char *pEmail, char *pCidade, char genero, char *pDataNasc );

/***********************************************************************
 *
 *  $FC Função: PER  &Destruir Perfil
 *
 *  $ED Descrição da função
 *     Destroi um Perfil
 *
 *  $EP Parâmetros
 *     pPerfil  - ponteiro do o perfil que será destruido
 *
 *  $FV Valor retornado
 *      PER_CondRetOK  - destruicao do perfil com sucesso
 *      PER_CondRetPonteiroNulo - se o valor do perfil for NULL
 *
 ***********************************************************************/

    void PER_DestruirPerfil(void * pPerfil);

/***********************************************************************
 *
 *  $FC Função: PER  &Comparar  Perfil
 *
 *  $ED Descrição da função
 *     Compara dois perfis
 *
 *  $EP Parâmetros
 *     pValor1  - ponteiro do o perfil 1
 *     pValor2  - ponteiro do o perfil 2
 *
 *  $FV Valor retornado
 *      igual a 0  - dois perfis são iguais
 *      diferente de 0 - dois perfis são diferentes
 *
 ***********************************************************************/

    int PER_CompararPerfil(void * pValor1, void * pValor2);

/***********************************************************************
 *
 *  $FC Função: PER  &Mostrar  Perfil
 *
 *  $ED Descrição da função
 *     Mostra as informações de um perfil
 *
 *  $EP Parâmetros
 *     pPerfil  - ponteiro de um Perfil
 *
 *  $FV Valor retornado
 *      PER_CondRetOK  - insformações do perfil mostradas com sucesso
 *      PER_CondRetPonteiroNulo - valor do perfil é igual a NULL e nao mostra as inf do Perfil
 *
 ***********************************************************************/

PER_tpCondRet PER_MostrarPerfil(PER_tppPerfil pPerfil);

/***********************************************************************
 *
 *  $FC Função: PER  &Obter  Email
 *
 *  $ED Descrição da função
 *     Recebe um perfil e obtem o email cadastrado neste perfil.
 *
 *  $EP Parâmetros
 *     pPerfil  - ponteiro de um Perfil
 *
 *  $FV Valor retornado
 *      Cadeia de caracteres, caso o ponteiro para o perfil seja valido.
 *      NULL, caso o ponteiro seja nulo.
 *
 ***********************************************************************/
char * PER_ObterEmail(PER_tppPerfil pPerfil);

/***********************************************************************
 *
 *  $FC Função: PER  &Obter  Nome
 *
 *  $ED Descrição da função
 *     Recebe um perfil e obtem o nome cadastrado neste perfil.
 *
 *  $EP Parâmetros
 *     pPerfil  - ponteiro de um Perfil
 *
 *  $FV Valor retornado
 *      Cadeia de caracteres - caso o ponteiro para o perfil seja valido.
 *      NULL - caso o ponteiro seja nulo.
 *
 ***********************************************************************/
char * PER_ObterNome(PER_tppPerfil pPerfil);

/***********************************************************************
 *
 *  $FC Função: PER  &Obter  Cidade
 *
 *  $ED Descrição da função
 *     Recebe um perfil e obtem a cidade cadastrada neste perfil.
 *
 *  $EP Parâmetros
 *     pPerfil  - ponteiro de um Perfil
 *
 *  $FV Valor retornado
 *      Cadeia de caracteres - caso o ponteiro para o perfil seja valido.
 *      NULL - caso o ponteiro seja nulo.
 *
 ***********************************************************************/
char * PER_ObterCidade(PER_tppPerfil pPerfil);

/***********************************************************************
 *
 *  $FC Função: PER  &Obter  Data de nascimento
 *
 *  $ED Descrição da função
 *     Recebe um perfil e obtem a data de nascimento deste perfil.
 *
 *  $EP Parâmetros
 *     pPerfil  - ponteiro de um Perfil
 *
 *  $FV Valor retornado
 *      Cadeia de caracteres - caso o ponteiro para o perfil seja valido.
 *      NULL - caso o ponteiro seja nulo.
 *
 ***********************************************************************/
char * PER_ObterNascimento(PER_tppPerfil pPerfil);

/***********************************************************************
 *
 *  $FC Função: PER  &Obter  Data de nascimento
 *
 *  $ED Descrição da função
 *     Recebe um perfil o genero deste perfil.
 *
 *  $EP Parâmetros
 *     pPerfil  - ponteiro de um Perfil
 *
 *  $FV Valor retornado
 *      Caractere - caso o ponteiro para o perfil seja valido.
 *      NULL - caso o ponteiro seja nulo.
 *
 ***********************************************************************/
char PER_ObterGenero(PER_tppPerfil pPerfil);

/***********************************************************************
 *
 *  $FC Função: PER  &Alterar Nome
 *
 *  $ED Descrição da função
 *     Recebe um perfil e altera o nome desse perfil.
 *
 *  $EP Parâmetros
 *     pPerfil  - ponteiro de um Perfil
 *     nome - novo valor que irá substituir o nome do perfil.
 *
 *  $FV Valor retornado
 *      PER_CondRetPonteiroNulo, caso o ponteiro para o perfil ou para a string pNome sejam nulos.
 *      PER_CondRetStringVazia, caso a string pNome esteja vazia.
 *      PER_CondRetOk, caso a alteração seja feita corretamente.
 *
 ***********************************************************************/
PER_tpCondRet PER_AlterarNome(PER_tppPerfil pPerfil, char *nome);

/***********************************************************************
 *
 *  $FC Função: PER  &Alterar Cidade
 *
 *  $ED Descrição da função
 *     Recebe um perfil e altera a cidade desse perfil.
 *
 *  $EP Parâmetros
 *     pPerfil  - ponteiro de um Perfil
 *     cidade - novo valor que irá substituir a cidade do perfil.
 *
 *  $FV Valor retornado
 *      PER_CondRetPonteiroNulo, caso o ponteiro para o perfil ou para a string pCidade sejam nulos.
 *      PER_CondRetStringVazia, caso a string pCidade esteja vazia.
 *      PER_CondRetOk, caso a alteração seja feita corretamente.
 *
 ***********************************************************************/
PER_tpCondRet PER_AlterarCidade(PER_tppPerfil pPerfil, char *cidade);

/***********************************************************************
 *
 *  $FC Função: PER  &Alterar data de nascimento
 *
 *  $ED Descrição da função
 *     Recebe um perfil e altera a data de nascimento desse perfil.
 *
 *  $EP Parâmetros
 *     pPerfil  - ponteiro de um Perfil
 *     dataNasc - novo valor que irá substituir a data de nascimento do perfil.
 *
 *  $FV Valor retornado
 *      PER_CondRetPonteiroNulo - caso o ponteiro para o perfil seja nulo
 *      PER_CondRetValorInvalido - caso a string da data de nascimento não tenha o tamanho correto de 10 caracteres "XX/XX/XXXX".
 *      PER_CondRetOk - caso a alteração seja feita corretamente.
 *
 ***********************************************************************/
PER_tpCondRet PER_AlterarDataNasc(PER_tppPerfil pPerfil, char * dataNasc);

/***********************************************************************
 *
 *  $FC Função: PER  &Alterar Genero
 *
 *  $ED Descrição da função
 *     Recebe um perfil e altera a idade desse perfil.
 *
 *  $EP Parâmetros
 *     pPerfil  - ponteiro de um Perfil
 *     genero - caractere com os possíveis valores: 'M' - masculino, 'F' - feminino, 'O' - outro
 *
 *  $FV Valor retornado
 *      PER_CondRetPonteiroNulo - caso o ponteiro para o perfil seja nulo
 *      PER_CondRetValorInvalido - caso o valor do parametro genero seja diferente de "M', 'F' ou 'O'
 *      PER_CondRetOk - caso a alteração seja feita corretamente.
 *
 ***********************************************************************/
PER_tpCondRet PER_AlterarGenero(PER_tppPerfil pPerfil, char genero);

/***********************************************************************
 *
 *  $FC Função: PER  &Enviar Mensagem
 *
 *  $ED Descrição da função
 *     Envia uma mensagem do perfil remetente para o perfil destinatário.
 *     Armazena a mensagem na lista de mensagens enviadas do remetente e
 *     na lista de mensagens recebidas do destinatario.
 *
 *  $EP Parâmetros
 *     remetente  - ponteiro do tipo Perfil do remetente
 *     destinatario  - ponteiro do tipo Perfil do destinatario
 *
 *  $FV Valor retornado
 *      PER_CondRetPonteiroNulo - caso algum dos parametros seja nulo
 *      PER_CondRetFaltouMemoria - caso não consiga adicionar a mensagem na lista
 *      PER_CondRetOk - caso a alteração seja feita corretamente.
 *
 ***********************************************************************/
PER_tpCondRet PER_EnviarMensagem(PER_tppPerfil remetente, char * texto, PER_tppPerfil destinatario);

/***********************************************************************
*
*  $FC Função: PER  &Buscar Mensagem Enviada
*
*  $ED Descrição da função
*      Busca uma mensagem na lista de mensagens enviadas por um perfil para um outro perfil em específico.
*      Por exemplo: buscar as mensagens que o perfil A enviou para o perfil B: o primeiro parâmetro é o perfil A,
*      o segundo parâmetro é o e-mail do perfil B.
*      Funciona como um iterador através do parâmetro inicio. Se inicio = 0, o elemento corrente da lista
*      de mensagens vai para o primeiro elemento da lista. O texto da mensagem e o identificador da mensagem
*      são retornados por referência. Se inicio > 0, o elemento corrente vai avançando até retornar todas as
*      mensagens encontradas.
*
*  $EP Parâmetros
*     pPerfil  - Perfil onde será buscada a mensagem de outro perfil em específico.
*     pEmail  - email do perfil que será buscado na lista de mensagens
*     inicio - colocar 0 na primeira iteração (vai para o inicio da lista) e > 0 nas proximas iterações
*     textoMsg - parametro pelo qual o texto da mensagem encontrada será retornado
*     idMsg - parametro pelo qual o identificado da mensagem encontrada será retornado
*
*  $FV Valor retornado
*     PER_CondRetPonteiroNulo - caso o parametro pPerfil, parametro pEmail, mensagem encontrada ou remetente encontrado sejam NULL (erro)
*     
*
***********************************************************************/
PER_tpCondRet PER_BuscarMsgEnviada(PER_tppPerfil pPerfil, char * pEmail, int inicio, char * textoMsg, int * idMsg);

/***********************************************************************
*
*  $FC Função: PER  &Buscar Mensagem Recebida
*
***********************************************************************/
PER_tpCondRet PER_BuscarMsgRecebida(PER_tppPerfil pPerfil, char * pEmail, int inicio, char * textoMsg, int * idMsg);


#undef PERFIL_EXT

/********** Fim do módulo de definição: PER  Perfil **********/

#else
#endif