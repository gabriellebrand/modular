/***************************************************************************
*  $MCI Módulo de implementação: TESTCON  Teste Controlador
*
*  Arquivo gerado:              TESTCON.c
*  Letras identificadoras:      TCON
*
*
*  Projeto:    Trabalho 2 - Programaçăo Modular
*  Autores:    GB - Gabrielle Brandenburg
*              GC - Gabriel Cantergiani
*              WB - Wellingotn Bezerra
*
*  $HA Histórico de evoluçăo:
*     Versăo      Autor            Data                Observaçőes
*     1.0          GC        02/11/2017       		Criação do módulo
*     2.0          GC        03/12/2017            Modulo finalizado
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

#include    "CONTROLADOR.H"

static const char CRIAR_PERFIL_CMD          [ ] = "=criarperfil"         ;
static const char BUSCAR_PERFIL_CMD         [ ] = "=buscarperfil"        ;
static const char MOSTRAR_PERFIL_CMD        [ ] = "=mostrarperfil"       ;
static const char EXCLUIR_PERFIL_CMD        [ ] = "=excluirperfil"       ;
static const char ALTERAR_NOME_CMD          [ ] = "=alterarnome"         ;
static const char ALTERAR_CIDADE_CMD        [ ] = "=alterarcidade"       ;
static const char ALTERAR_DATANASC_CMD      [ ] = "=alterardatanasc"     ;
static const char ALTERAR_GENERO_CMD        [ ] = "=alterargenero"       ;
static const char CRIAR_AMIZADE_CMD         [ ] = "=criaramizade"        ;
static const char EXCLUIR_AMIZADE_CMD       [ ] = "=excluiramizade"      ;
static const char BUSCAR_AMIZADES_CMD       [ ] = "=buscaramizades"      ;
static const char ENVIAR_MENSAGEM_CMD       [ ] = "=enviarmensagem"      ;
static const char CARREGAR_HISTORICO_CMD    [ ] = "=carregarhistorico"   ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VALOR     110


    /*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************											
*  $FC Função: TCON &Testar Controlador
*
*  $ED Descrição da função
*     Podem ser criados até 10 Perfis, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =criarperfil                  string(nome) string(email) string(cidade) char(genero) string(dataNasc) CondRet
*     =buscarperfil  				   string(email)   CondRet
*     =mostrarperfil  				   string(email)   CondRet
*     =excluirperfil                string(email)   CondRet
*     =alterarnome                  string(email)   string(nome)    CondRet
*     =alterarcidade                string(email)   string(cidade)  CondRet
*     =alterardatanasc              string(email)   string(datanasc)CondRet
*     =alterargenero                string(email)   string(genero)  CondRet
*     =criaramizade                 string(email1)  string(email2)  CondRet
*     =excluiramizade               string(email1)  string(email2)  CondRet
*     =buscarramizades              string(email1)  CondRet
*     =enviarmensagem               string(email1)  string(email2)  string(texto)  CondRet
*     =carregarhistorico            string(email1)  string(email2)  CondRet
*
***********************************************************************/


 TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int  numLidos   = -1;

      char   StringDado1[  DIM_VALOR ] ;
      char   StringDado2[  DIM_VALOR ] ;
      char   StringDado3[  DIM_VALOR ] ;
      char   StringDado4[  DIM_VALOR ] ;
      char   CharDado;

      CON_tpCondRet CondRetEsperada;
      CON_tpCondRet CondRetObtida;

      PER_tppPerfil pPerfil = (PER_tppPerfil) malloc (sizeof(PER_tppPerfil));

      StringDado1[ 0 ] = 0 ;
      StringDado2[ 0 ] = 0 ;
      StringDado3[ 0 ] = 0 ;
      StringDado4[ 0 ] = 0 ;
      CharDado = 0;


         /* Testar CriarPerfil */

         if ( strcmp( ComandoTeste , CRIAR_PERFIL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ssscsi" ,
                       StringDado1, StringDado2, StringDado3, &CharDado, StringDado4, &CondRetEsperada ) ;

            if ( ( numLidos != 6 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            if(strcmp(StringDado1, "")==0 || strcmp(StringDado2, "")==0 || strcmp(StringDado3, "")==0 || strcmp(StringDado4, "")==0)
                  CondRetObtida = CON_CriarPerfil (NULL, StringDado2, StringDado3, CharDado, StringDado4);
            else
                  CondRetObtida = CON_CriarPerfil (StringDado1, StringDado2, StringDado3, CharDado, StringDado4);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao criar perfil."   ) ;

         } /* fim ativa: Testar CriarPerfil */

         /* Testar BuscarPerfil */

         else if ( strcmp( ComandoTeste , BUSCAR_PERFIL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "si" ,
                       StringDado1, &CondRetEsperada ) ;

            if ( ( numLidos != 2 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CON_BuscarPerfil (StringDado1, &pPerfil);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao Buscar perfil."   ) ;

         } /* fim ativa: Testar BuscarPerfil */


          /* Testar MostrarPerfil */

         else if ( strcmp( ComandoTeste , MOSTRAR_PERFIL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "si" ,
                       StringDado1, &CondRetEsperada ) ;

            if ( ( numLidos != 2 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CON_MostrarPerfil (StringDado1);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao Mostrar perfil."   ) ;

         } /* fim ativa: Testar MostrarPerfil */

         /* Testar ExcluirPerfil */

         else if ( strcmp( ComandoTeste , EXCLUIR_PERFIL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "si" ,
                       StringDado1, &CondRetEsperada ) ;

            if ( ( numLidos != 2 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CON_ExcluirPerfil (StringDado1);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao Excluir perfil."   ) ;

         } /* fim ativa: Testar ExcluirPerfil */

         /* Testar Alterar Nome */

         else if ( strcmp( ComandoTeste , ALTERAR_NOME_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ssi" ,
                       StringDado1, StringDado2, &CondRetEsperada ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CON_AlterarPerfilNome (StringDado1, StringDado2);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao Alterar Nome do Perfil."   ) ;

         } /* fim ativa: Testar Alterar Nome */   

         /* Testar Alterar Cidade */

         else if ( strcmp( ComandoTeste , ALTERAR_CIDADE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ssi" ,
                       StringDado1, StringDado2, &CondRetEsperada ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CON_AlterarPerfilCidade (StringDado1, StringDado2);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao Alterar Cidade do Perfil."   ) ;

         } /* fim ativa: Testar Alterar Cidade */

          /* Testar Alterar DataNasc */

         else if ( strcmp( ComandoTeste , ALTERAR_DATANASC_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ssi" ,
                       StringDado1, StringDado2, &CondRetEsperada ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CON_AlterarPerfilNasc (StringDado1, StringDado2);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao Alterar DataNasc do Perfil."   ) ;

         } /* fim ativa: Testar Alterar DataNasc */ 

         /* Testar Alterar Genero */

         else if ( strcmp( ComandoTeste , ALTERAR_GENERO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "sci" ,
                       StringDado1, &CharDado, &CondRetEsperada ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CON_AlterarPerfilGenero (StringDado1, CharDado);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao Alterar Genero do Perfil."   ) ;

         } /* fim ativa: Testar Alterar Genero */ 

          /* Testar CriarAmizade */

         else if ( strcmp( ComandoTeste , CRIAR_AMIZADE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ssi" ,
                       StringDado1, StringDado2, &CondRetEsperada ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CON_CriarAmizade (StringDado1, StringDado2);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao criar Amizade."   ) ;

         } /* fim ativa: Testar CriarAmizade */

         /* Testar ExcluirAmizade */

         else if ( strcmp( ComandoTeste , EXCLUIR_AMIZADE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ssi" ,
                       StringDado1, StringDado2, &CondRetEsperada ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            if(strcmp(StringDado1, "") == 0  ||  strcmp(StringDado2, "") == 0)
                  CondRetObtida = CON_ExcluirAmizade (NULL, StringDado2);
            else
                  CondRetObtida = CON_ExcluirAmizade (StringDado1, StringDado2);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao Excluir Amizade."   ) ;

         } /* fim ativa: Testar ExcluirAmizade */   

         /* Testar BuscarAmizade */

         else if ( strcmp( ComandoTeste , BUSCAR_AMIZADES_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "si" ,
                       StringDado1, &CondRetEsperada ) ;

            if ( ( numLidos != 2 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            if(strcmp(StringDado1, "") == 0)
                  CondRetObtida = CON_BuscarAmizades(NULL);
            else
                  CondRetObtida = CON_BuscarAmizades(StringDado1);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao Buscar Amizade."   ) ;

         } /* fim ativa: Testar BuscarAmizade */

         /* Testar EnviarMensagem*/

         else if ( strcmp( ComandoTeste , ENVIAR_MENSAGEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "sssi" ,
                       StringDado1, StringDado2, StringDado3, &CondRetEsperada ) ;

            if ( ( numLidos != 4 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            if(strcmp(StringDado1, "") == 0 || strcmp(StringDado2, "") == 0 || strcmp(StringDado3, "") == 0)
                  CondRetObtida = CON_EnviarMensagem(NULL, StringDado2, StringDado3);
            else
                  CondRetObtida = CON_EnviarMensagem(StringDado1, StringDado2, StringDado3);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao Buscar Amizade."   ) ;

         } /* fim ativa: Testar EnviarMensagem*/

         /* Testar Carregar Historico*/

         else if ( strcmp( ComandoTeste , CARREGAR_HISTORICO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ssi" ,
                       StringDado1, StringDado2, &CondRetEsperada ) ;

            if ( ( numLidos != 3 ) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtida = CON_CarregarHistorico (StringDado1, StringDado2);

            return TST_CompararInt( CondRetObtida , CondRetEsperada ,
                     "Condicao de retorno errada ao Carregar Historico."   ) ;

         } /* fim ativa: Testar Carregar Historico */

          return TST_CondRetNaoConhec ;

}  /* Fim função: TCON Testar Controlador */