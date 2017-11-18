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

#include "PERFIL.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma Mensagem */

typedef struct MEN_tagMensagem * MEN_tppMensagem;


/***********************************************************************
*
*  $FC Função: MEN  &Criar Mensagem
*
*  $ED Descrição da função
*     Cria uma estrutura do tipo Mensagem
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

MEN_tppMensagem MEN_CriarMensagem(PER_tppPerfil remetente, PER_tppPerfil destinatario, char *texto);

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

