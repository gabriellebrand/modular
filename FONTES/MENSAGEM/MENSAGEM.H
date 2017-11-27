#if ! defined( MENSAGEM_ )
#define MENSAGEM_
/***************************************************************************
 *  $MCI Módulo de implementaçăo: MEN  Mensagem
 *
 *  Arquivo gerado:              MENSAGEM.c
 *  Letras identificadoras:      MEN
 *
 *  Nome da base de software:    Arcabouço para a automaçăo de testes de programas redigidos em C
 *
 *  Projeto:    Trabalho 2 - Programaçăo Modular
 *  Autores:    GB - Gabrielle Brandenburg
                GC - Gabriel Cantergiani
                WB - Wellingotn Bezerra
 *
 *  $HA Histórico de evoluçăo:
 *     Versăo      Autor         Data                Observaçőes
 *     1.0          GB        15/11/2017       Criação do módulo
 *
 ***************************************************************************/

#if defined( MENSAGEM_OWN )
   #define MENSAGEM_EXT
#else
   #define MENSAGEM_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma Mensagem */

typedef struct MEN_tagMensagem * MEN_tppMensagem;

/***********************************************************************
*
*  $TC Tipo de dados: MENCondições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do modulo Perfil
*
***********************************************************************/

typedef enum {
	   
 /* 0 */ MEN_CondRetOK ,
               /* Concluiu corretamente */

 /* 1 */ MEN_CondRetValorNulo,


 /* 2 */ MEN_CondRetPonteiroNulo,
   		/* Ponteiro Nulo */

 /* 3 */ MEN_CondRetNaoAchou

   } MEN_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MEN  &Criar Mensagem
*
*  $ED Descrição da função
*     Cria uma estrutura do tipo Mensagem. O tipo do remetente/destinatário não precisa ser conhecido pela mensagem.
*
*  $EP Parâmetros
*     remetente  - ponteiro para o perfil do remetente da mensagem
*     destinatario - ponteiro para o perfil do destinatário da mensagem
*     texto - texto da mensagem
*
*  $FV Valor retornado
*		- Se executou corretamente, retorna o ponteiro para uma Mensagem.
*		- Se ocorreu algum erro, por exemplo falta de memoria ou dados errados,
*		a funcao retorna NULL.
*
***********************************************************************/
MEN_tppMensagem MEN_CriarMensagem(void * remetente, void * destinatario, char *texto);

/***********************************************************************
*
*  $FC Função: MEN  &Obter texto
*
*  $ED Descrição da função
*     Retorna o texto armazenado na mensagem
*
*  $EP Parâmetros
*     mensagem  - ponteiro para a mensagem
*
*  $FV Valor retornado
*		- Se executou corretamente, retorna o texto da mensagem.
*		- Se a mensagem enviada como parâmetro não existe, retorna NULL.
*
***********************************************************************/
char * MEN_ObterTexto(MEN_tppMensagem mensagem);

/***********************************************************************
*
*  $FC Função: MEN  &Obter ID
*
*  $ED Descrição da função
*     Retorna o número identificador da mensagem
*
*  $EP Parâmetros
*     mensagem  - ponteiro para a mensagem
*
*  $FV Valor retornado
*		- Se executou corretamente, retorna o identificador da mensagem.
*		- Se a mensagem enviada como parâmetro não existe, retorna -1.
*
***********************************************************************/
int MEN_ObterID(MEN_tppMensagem mensagem);

/***********************************************************************
*
*  $FC Função: MEN  &Obter remetente
*
*  $ED Descrição da função
*     Retorna o ponteiro para o remetente armazenado na mensagem.
*	  É necessário fazer o typecast do remetente para o tipo conhecido pelo cliente.
*
*  $EP Parâmetros
*     mensagem  - ponteiro para a mensagem
*
*  $FV Valor retornado
*		- Se executou corretamente, retorna o remetente.
*		- Se a mensagem enviada como parâmetro não existe, retorna NULL.
*
***********************************************************************/
void * MEN_ObterRemetente(MEN_tppMensagem mensagem);

/***********************************************************************
*
*  $FC Função: MEN  &Obter destinatário
*
*  $ED Descrição da função
*     Retorna o ponteiro para o destinatário armazenado na mensagem.
*	  É necessário fazer o typecast do destinatário para o tipo conhecido pelo cliente.
*
*  $EP Parâmetros
*     mensagem  - ponteiro para a mensagem
*
*  $FV Valor retornado
*		- Se executou corretamente, retorna o destinatário.
*		- Se a mensagem enviada como parâmetro não existe, retorna NULL.
*
***********************************************************************/
void * MEN_ObterDestinatario(MEN_tppMensagem mensagem);

/***********************************************************************
*
*  $FC Função: MEN  &Comparar mensagem
*
*  $ED Descrição da função
*     Essa funcao recebe dois ponteiros para o tipo mensagem e compara seus IDs.
*
*  $EP Parâmetros
*     pValor1  - ponteiro para a mensagem 1
*     pValor2  - ponteiro para a mensagem 2
*
*  $FV Valor retornado
*		- 0, caso o número identificador das duas mensagens seja igual
*		- 1, caso o número identificador da mensagem 1 seja maior que o da mensagem 2
*		- (-1), caso o número identificador da mensagem 1 seja menor que o da mensagem 2
*		- (-2), caso algum dos parametros seja nulo
*
***********************************************************************/
int MEN_CompararMensagem(void * pValor1, void * pValor2);

/***********************************************************************
*
*  $FC Função: MEN  &Desativar remetente
*
*  $ED Descrição da função
*     Essa função deve ser chamada quando o perfil remetente for excluído.
*	  Desativa o campo remetente da estrutura mensagem. 
*	  O campo remetente passa a apontar para NULL. Caso o campo
*	  destinatário também tenha valor NULL, a mensagem será excluída (free).
*
*  $EP Parâmetros
*     mensagem  - ponteiro para a mensagem
*
*  $FV Valor retornado
*		- CondRetOK, se executou corretamente
*		- CondRetValorNulo, se o parametro da mensagem for nulo
*
***********************************************************************/
MEN_tpCondRet MEN_DesativarRemetente(MEN_tppMensagem mensagem);

/***********************************************************************
*
*  $FC Função: MEN  &Desativar destinatário
*
*  $ED Descrição da função
*     Essa função deve ser chamada quando o perfil destinatário for excluído.
*	  Desativa o campo remetente da estrutura mensagem. 
*	  O campo remetente passa a apontar para NULL. Caso o campo
*	  remetente também tenha valor NULL, a mensagem será excluída (free).
*
*  $EP Parâmetros
*     mensagem  - ponteiro para a mensagem
*
*  $FV Valor retornado
*		- CondRetOK, se executou corretamente
*		- CondRetValorNulo, se o parametro da mensagem for nulo
*
***********************************************************************/
MEN_tpCondRet MEN_DesativarDestinatario(MEN_tppMensagem mensagem);

#else
#endif
