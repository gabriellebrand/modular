/***************************************************************************
*  $MCI Módulo de implementação: TESTMEN Teste MENSAGEM
*
*  Arquivo gerado:              TESTMEN.c
*  Letras identificadoras:      TMEN
*
*
*  Projeto:    Trabalho 2 - Programaçăo Modular
*  Autores:    GB - Gabrielle Brandenburg
*              GC - Gabriel Cantergiani
*              WB - Wellingotn Bezerra
*
*  $HA Histórico de evoluçăo:
*     Versăo      Autor            Data                Observaçőes
*     1.0          GC        24/11/2017       		Criação do módulo
*
***************************************************************************/

#include    <stdlib.h>
#include    <memory.h>
#include    <assert.h>

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "MENSAGEM.H"


static const char RESET_MENSAGEM_CMD          [ ] = "=resetteste"                 ;
static const char CRIAR_MENSAGEM_CMD          [ ] = "=criarmensagem"              ;
static const char OBTER_TEXTO_CMD             [ ] = "=obtertexto"                 ;
static const char OBTER_ID_CMD                [ ] = "=obterid"                    ;
static const char OBTER_REMETENTE_CMD         [ ] = "=obterremetente"             ;
static const char OBTER_DESTINATARIO_CMD      [ ] = "=obterdestinatario"          ;
static const char COMPARAR_MENSAGEM_CMD       [ ] = "=compararmensagem"           ;
static const char DESATIVAR_REMETENTE_CMD     [ ] = "=desativarremetente"         ;
static const char DESATIVAR_DESTINATARIO_CMD  [ ] = "=desativardestinatario"      ;
static const char CRIAR_PERFIL_CMD            [ ] = "=criarperfil"                ;



#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_MENSAGEM   100
#define DIM_VT_PERFIL     10
#define DIM_VALOR     100

MEN_tppMensagem   vtMensagem[ DIM_VT_MENSAGEM ] ;


typedef struct PER_tagPerfil {

    char nome[100];
        /* Nome do perfil */

} PER_tpPerfil ;

typedef struct PER_tagPerfil * PER_tppPerfil ;

PER_tppPerfil     vtPerfil [ DIM_VT_PERFIL    ] ;
PER_tppPerfil     vtPerfil [ DIM_VT_PERFIL    ] ;

   /***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxMensagem( int inxMensagem , int Modo ) ;

   PER_tppPerfil PER_CriarPerfil (char * nome);

   /*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TPER &Testar MENSAGEM
*
*  $ED Descrição da função
*     Podem ser criadas até 100 Mensagens, identificadas pelos índices 0 a 100
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de Mensagens e o de Perfil. Provoca vazamento de memória
*     =criarmensagem          inxMensagem   inxPerfil1                  inxPerfil2   string(texto)
*     =obtertexto             inxMensagem   string(texto)               CondRet
*     =obterid                inxMensagem   idMen (indice + 1)          CondRet
*     =obterremetente         inxMensagem   inxPerfil1                  CondRet
*     =obterdestinatario      inxMensagem   inxPerfil2                  CondRet
*     =compararmensagem       inxMensagem1  inxMensagem2                CondRet
*     =desativarremetente     inxMensagem   CondRet
*     =desativardestinatario  inxMensagem   CondRet
*     =criarperfil            inxPerfil     string(nome)
*     
*
***********************************************************************/


TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxMensagem  = -1 ,
          inxMensagem2  = -1 ,
          inxPerfil  = -1 ,
          inxPerfil2  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1;

      TST_tpCondRet CondRet ;
      MEN_tpCondRet CondRetEsperada;
      MEN_tpCondRet CondRetObtida;
      PER_tppPerfil perfil;

      char   StringDado1[  DIM_VALOR ] ;
      char   StringDado2[  DIM_VALOR ] ;
      char   StringDado3[  DIM_VALOR ] ;
	   char  *StringDado4;
      int    intDado = -1;


      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado1[ 0 ] = 0 ;
      StringDado2[ 0 ] = 0 ;
      StringDado3[ 0 ] = 0 ;

      /* Efetuar reset de teste de mensagem */

         if ( strcmp( ComandoTeste , RESET_MENSAGEM_CMD ) == 0 )
         {
				for( i = 0 ; i < DIM_VT_MENSAGEM ; i++ )
            		{
               			vtMensagem[ i ] = NULL ;
            		} /* for */

            for( i = 0; i < DIM_VT_PERFIL ; i++ ){

            	  vtPerfil [ i ] = NULL;
            }

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de Mensagem */


         /* Cria Perfil para testes */

         else if ( strcmp( ComandoTeste , CRIAR_PERFIL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "is" ,
                       &inxPerfil, StringDado1 ) ;

            if (  numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            vtPerfil[ inxPerfil ] = PER_CriarPerfil (StringDado1);

            return TST_CompararPonteiroNulo( 1 , vtPerfil[ inxPerfil ] ,
               "Erro em ponteiro de novo Perfil."  ) ;

         } /* fim ativa: Cria Perfil */

         /* Testar CriarMensagem */

         else if ( strcmp( ComandoTeste , CRIAR_MENSAGEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iiis" ,
                       &inxMensagem, &inxPerfil, &inxPerfil2, StringDado1 ) ;

            if ( ( numLidos != 4 )
              || ( ! ValidarInxMensagem( inxMensagem , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtMensagem[ inxMensagem ] = MEN_CriarMensagem ( vtPerfil [ inxPerfil ], vtPerfil [ inxPerfil2 ], StringDado1);

            return TST_CompararPonteiroNulo( 1 , vtMensagem[ inxMensagem ] ,
               "Erro em ponteiro de nova Mensagem."  ) ;

         } /* fim ativa: Testar CriarMensagem */


         /* Testar Obter Texto */

         else if ( strcmp( ComandoTeste , OBTER_TEXTO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxMensagem, StringDado1, &CondRetEsperada ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxMensagem( inxMensagem , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            StringDado4 = MEN_ObterTexto (vtMensagem[ inxMensagem ]);

            if (strcmp(StringDado1, StringDado4) == 0)
                  CondRetObtida = MEN_CondRetOK;
            else 
                  CondRetObtida = MEN_CondRetNaoAchou;

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao obter texto."   ) ;

         } /* fim ativa: Testar Obter Texto */

         /* Testar Obter ID */

         else if ( strcmp( ComandoTeste , OBTER_ID_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxMensagem, &intDado, &CondRetEsperada ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxMensagem( inxMensagem , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

           i = MEN_ObterID ( vtMensagem[ inxMensagem ] );

            if (i == intDado)
                  CondRetObtida = MEN_CondRetOK;
            else 
                  CondRetObtida = MEN_CondRetNaoAchou;

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao obter ID."   ) ;

         } /* fim ativa: Testar Obter ID */


         /* Testar Obter Remetente */

         else if ( strcmp( ComandoTeste , OBTER_REMETENTE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxMensagem, StringDado1, &CondRetEsperada ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxMensagem( inxMensagem , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            perfil = (PER_tppPerfil) MEN_ObterRemetente ( vtMensagem[ inxMensagem ] );

            if ( perfil == NULL)
                  CondRetObtida = MEN_CondRetValorNulo;
            else if (strcmp(StringDado1, perfil->nome) == 0)
                  CondRetObtida = MEN_CondRetOK;
            else
                  CondRetObtida = MEN_CondRetNaoAchou;

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao obter remetente."   ) ;

         } /* fim ativa: Testar Obter Remetente */

         /* Testar Obter Destinatario */

         else if ( strcmp( ComandoTeste , OBTER_DESTINATARIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxMensagem, StringDado1, &CondRetEsperada ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxMensagem( inxMensagem , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            perfil = (PER_tppPerfil) MEN_ObterDestinatario ( vtMensagem[ inxMensagem ] );

            if ( perfil == NULL)
                  CondRetObtida = MEN_CondRetValorNulo;
            else if (strcmp(StringDado1, perfil->nome) == 0)
                  CondRetObtida = MEN_CondRetOK;
            else
                  CondRetObtida = MEN_CondRetNaoAchou;

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao obter Destinatario."   ) ;

         } /* fim ativa: Testar Obter Destinatario */

         /* Testar Comparar Mensagem */

         else if ( strcmp( ComandoTeste , COMPARAR_MENSAGEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxMensagem, &inxMensagem2, &CondRetEsperada ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxMensagem( inxMensagem , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            i = MEN_CompararMensagem (vtMensagem[ inxMensagem ], vtMensagem[ inxMensagem2 ]);

            if ( i == 0)
                  CondRetObtida = MEN_CondRetOK;
            else if ( i == -2)
                  CondRetObtida = MEN_CondRetValorNulo;
            else
                  CondRetObtida = MEN_CondRetNaoAchou;

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao comparar mensagens"   ) ;

         } /* fim ativa: Testar Comparar Mensagens */


         /* Testar Desativar Remetente */

         else if ( strcmp( ComandoTeste , DESATIVAR_REMETENTE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxMensagem, &CondRetEsperada ) ;

            if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = MEN_DesativarRemetente ( vtMensagem [ inxMensagem ]);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao desativar remetente."   ) ;

         } /* fim ativa: Testar Desativar Remetente */
          

         /* Testar Desativar Destinatario */

         else if ( strcmp( ComandoTeste , DESATIVAR_DESTINATARIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxMensagem, &CondRetEsperada ) ;

            if ( ( numLidos != 2 ))
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = MEN_DesativarDestinatario ( vtMensagem [ inxMensagem ]);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao desativar Destinatario."   ) ;

         } /* fim ativa: Testar Desativar Destinatario */


          return TST_CondRetNaoConhec ;

}	/* Fim função: TMEN &Testar Mensagem */




/***********************************************************************
*
*  $FC Função: TMEN -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      MEN_DesativarRemetente ( (MEN_tppMensagem ) pValor);
      MEN_DesativarDestinatario ( (MEN_tppMensagem ) pValor);

   } /* Fim função: TMEN -Destruir valor */


/***********************************************************************
*
*  $FC Função: TMEN -Validar indice de Mensagem
*
***********************************************************************/

   int ValidarInxMensagem( int inxMensagem , int Modo )
   {

      if ( ( inxMensagem <  0 )
        || ( inxMensagem >= DIM_VT_MENSAGEM ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtMensagem[ inxMensagem ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtMensagem[ inxMensagem ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TMEN -Validar indice de Mensagem */


/***********************************************************************
*
*  $FC Função: TMEN -Criar Perfil
*
***********************************************************************/

PER_tppPerfil PER_CriarPerfil (char * nome) {

   PER_tppPerfil perfil = (PER_tppPerfil) malloc(sizeof(PER_tppPerfil));

   if (nome == NULL)
      return NULL;

   strcpy(perfil->nome, nome);

   return perfil;
}