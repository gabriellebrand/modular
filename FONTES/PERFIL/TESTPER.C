/***************************************************************************
*  $MCI Módulo de implementação: TESTPER Teste PERFIL
*
*  Arquivo gerado:              TESTPER.c
*  Letras identificadoras:      TPER
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

#include    "PERFIL.H"


static const char RESET_PERFIL_CMD         [ ] = "=resetteste"       ;
static const char CRIAR_PERFIL_CMD         [ ] = "=criarperfil"      ;
static const char DESTRUIR_PERFIL_CMD      [ ] = "=destruirperfil"      ;
static const char COMPARAR_PERFIL_CMD      [ ] = "=compararperfil"      ;
static const char MOSTRAR_PERFIL_CMD       [ ] = "=mostrarperfil"      ;
static const char OBTER_EMAIL_CMD          [ ] = "=obteremail"      ;
static const char ALTERAR_NOME_CMD         [ ] = "=alterarnome"      ;
static const char ALTERAR_CIDADE_CMD       [ ] = "=alterarcidade"      ;
static const char ALTERAR_DATANASC_CMD     [ ] = "=alterardatanasc"      ;
static const char ALTERAR_GENERO_CMD       [ ] = "=alterargenero"      ;
static const char ENVIAR_MENSAGEM_CMD      [ ] = "=enviarmensagem"      ;
static const char BUSCAR_MSG_ENV_CMD       [ ] = "=buscarmsgenv"      ;
static const char BUSCAR_MSG_REC_CMD       [ ] = "=buscarmsgrec"      ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_PERFIL   10
#define DIM_VALOR     100

   PER_tppPerfil  vtPerfil[ DIM_VT_PERFIL] ;

   /***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxPerfil( int inxPerfil , int Modo ) ;

   /*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************											
*  $FC Função: TPER &Testar Perfil
*
*  $ED Descrição da função
*     Podem ser criadas até 10 Perfis, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarperfil                  inxPerfil string(nome) string(email) string(cidade) char(genero) string(dataNasc)
*     =destruirperfil  				   inxPerfil
*     =compararperfil               inxPerfil1  string(email)  CondRet
*     =mostrarperfil  				   inxPerfil   CondRet
*     =obteremail   				      inxPerfil   string(email)  CondRet
*	   =alterarnome  				      inxPerfil string(nome)     CondRet
*	   =alterarcidade  				   inxPerfil string(cidade)   CondRet
*	   =alterardatanasc  			   inxPerfil string(dataNasc) CondRet
*	   =alterargenero  				   inxPerfil char(genero)     CondRet
*	   =enviarmensagem  				   inxPerfil1 inxPerfil2      string(texto)  CondRet
*	   =buscarmsgenv  				   inxPerfil  string(email)   CondRet
*	   =buscarmsgrec  				   inxPerfil  string(email)   CondRet
*
***********************************************************************/


TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxPerfil  = -1 ,
          inxPerfil2  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1;

      TST_tpCondRet CondRet ;
      PER_tpCondRet CondRetEsperada;
      PER_tpCondRet CondRetObtida;

      char   StringDado1[  DIM_VALOR ] ;
      char   StringDado2[  DIM_VALOR ] ;
      char   StringDado3[  DIM_VALOR ] ;
      char   StringDado4[  DIM_VALOR ] ;
      char * StringDado5 = (char *) malloc (sizeof(char) * DIM_VALOR ) ;
      char   CharDado;


      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado1[ 0 ] = 0 ;
      StringDado2[ 0 ] = 0 ;
      StringDado3[ 0 ] = 0 ;
      StringDado4[ 0 ] = 0 ;
      StringDado5[ 0 ] = 0 ;
      CharDado = 0;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_PERFIL_CMD ) == 0 )
         {
				for( i = 0 ; i < DIM_VT_PERFIL ; i++ )
            		{
               			vtPerfil[ i ] = NULL ;
            		} /* for */

            	return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de Perfil */


         /* Testar CriarPerfil */

         else if ( strcmp( ComandoTeste , CRIAR_PERFIL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issscs" ,
                       &inxPerfil, StringDado1, StringDado2, StringDado3, &CharDado, StringDado4 ) ;

            if ( ( numLidos != 6 )
              || ( ! ValidarInxPerfil( inxPerfil , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtPerfil[ inxPerfil ] = PER_CriarPerfil (StringDado1, StringDado2, StringDado3, CharDado, StringDado4);

            return TST_CompararPonteiroNulo( 1 , vtPerfil[ inxPerfil ] ,
               "Erro em ponteiro de novo Perfil."  ) ;

         } /* fim ativa: Testar CriarPerfil */


         /* Testar DestruirPerfil */

         else if ( strcmp( ComandoTeste , DESTRUIR_PERFIL_CMD ) == 0 )
         {
            
            numLidos = LER_LerParametros( "i" ,
                       &inxPerfil ) ;
            
            if ( ( numLidos != 1 )
              || ( ! ValidarInxPerfil( inxPerfil , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */
            
            PER_DestruirPerfil ( (void *) vtPerfil[ inxPerfil ]); 
            vtPerfil[ inxPerfil ] = NULL;
            
            return TST_CondRetOK;

         } /* fim ativa: Testar DestruirPerfil */


         /* Testar CompararPerfil */

         else if ( strcmp( ComandoTeste , COMPARAR_PERFIL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxPerfil, StringDado1, &CondRetEsperada ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxPerfil( inxPerfil , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            i = PER_CompararPerfil ( (void *) vtPerfil[ inxPerfil ], (void *) StringDado1);

            if (i == 0)
               CondRetObtida = PER_CondRetOK;
            else
               CondRetObtida = PER_CondRetNaoAchou;

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao comparar perfis."   ) ;

         } /* fim ativa: Testar CompararPerfil */


         /* Testar MostrarPerfil */

         else if ( strcmp( ComandoTeste , MOSTRAR_PERFIL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                       &inxPerfil, &CondRetEsperada ) ;

            if ( ( numLidos != 2 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = PER_MostrarPerfil (vtPerfil[ inxPerfil ]);
            
            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao mostrar perfil."   ) ;

         } /* fim ativa: Testar Mostrar Perfil */


         /* Testar Obter Email */

         else if ( strcmp( ComandoTeste , OBTER_EMAIL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxPerfil, StringDado1, &CondRetEsperada ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxPerfil( inxPerfil , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            StringDado5 = PER_ObterEmail ( vtPerfil[ inxPerfil ] );

            if (strcmp(StringDado1, StringDado5) == 0)
               CondRetObtida = PER_CondRetOK;
            else
               CondRetObtida = PER_CondRetNaoAchou;

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao obter email."   ) ;

         } /* fim ativa: Testar Obter Email */

         /* Testar Alterar Nome */

         else if ( strcmp( ComandoTeste , ALTERAR_NOME_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxPerfil, StringDado1, &CondRetEsperada ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = PER_AlterarNome ( vtPerfil[ inxPerfil ] , StringDado1);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao alterar nome."   ) ;

         } /* fim ativa: Testar Alterar Nome */

         /* Testar Alterar Cidade */

         else if ( strcmp( ComandoTeste , ALTERAR_CIDADE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxPerfil, StringDado1, &CondRetEsperada ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = PER_AlterarCidade ( vtPerfil[ inxPerfil ] , StringDado1);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao alterar Cidade."   ) ;

         } /* fim ativa: Testar Alterar Cidade */

         /* Testar Alterar DataNasc */

         else if ( strcmp( ComandoTeste , ALTERAR_DATANASC_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxPerfil, StringDado1, &CondRetEsperada ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = PER_AlterarDataNasc ( vtPerfil[ inxPerfil ] , StringDado1);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao alterar DataNasc."   ) ;

         } /* fim ativa: Testar Alterar DataNasc */

         /* Testar Alterar Genero */

         else if ( strcmp( ComandoTeste , ALTERAR_GENERO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ici" ,
                       &inxPerfil, &CharDado, &CondRetEsperada ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = PER_AlterarGenero ( vtPerfil[ inxPerfil ] , CharDado);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao alterar Genero."   ) ;

         } /* fim ativa: Testar Alterar Genero */


          return TST_CondRetNaoConhec ;

}	/* Fim função: TPER &Testar Perfil */




/***********************************************************************
*
*  $FC Função: TPER -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      PER_DestruirPerfil ( (PER_tppPerfil) pValor );

   } /* Fim função: TPER -Destruir valor */


/***********************************************************************
*
*  $FC Função: TPER -Validar indice de Perfil
*
***********************************************************************/

   int ValidarInxPerfil( int inxPerfil , int Modo )
   {

      if ( ( inxPerfil <  0 )
        || ( inxPerfil >= DIM_VT_PERFIL ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtPerfil[ inxPerfil ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtPerfil[ inxPerfil ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TPER -Validar indice de Perfil */

