/***************************************************************************
*  $MCI Módulo de implementação: TLIS Teste lista de símbolos
*
*  Arquivo gerado:              TestLIS.c
*  Letras identificadoras:      TLIS
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  5       gbc   10/out/2017 Adicionar comando de Procurar Valor
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
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

#include    "Lista.h"


static const char RESET_LISTA_CMD         [ ] = "=resetteste"       ;
static const char CRIAR_LISTA_CMD         [ ] = "=criarlista"       ;
static const char DESTRUIR_LISTA_CMD      [ ] = "=destruirlista"    ;
static const char ESVAZIAR_LISTA_CMD      [ ] = "=esvaziarlista"    ;
static const char INS_ELEM_ANTES_CMD      [ ] = "=inselemantes"     ;
static const char INS_ELEM_APOS_CMD       [ ] = "=inselemapos"      ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalorelem"   ;
static const char EXC_ELEM_CMD            [ ] = "=excluirelem"      ;
static const char IR_INICIO_CMD           [ ] = "=irinicio"         ;
static const char IR_FIM_CMD              [ ] = "=irfinal"          ;
static const char AVANCAR_ELEM_CMD        [ ] = "=avancarelem"      ;
static const char PROCURAR_CONTEUDO_CMD   [ ] = "=procurarconteudo" ;
static const char PROCURAR_VALOR_CMD	  [ ] = "=procurarvalor"    ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_LISTA   10
#define DIM_VT_PERFIL   10
#define DIM_VALOR     100

/***********************************************************************
 *
 *  $TC Tipo de dados: PER Perfil
 *
 *
 ***********************************************************************/

typedef struct PER_tagPerfil {

    char nome[100];
        /* Nome do perfil */
    
    char email[20];
        /* Email do perfil */
    
    char cidade[20];
        /* Cidade do perfil */
    
    char dataNasc[10];
        /* Data de Nascimento do perfil */

} PER_tpPerfil ;

typedef struct PER_tagPerfil * PER_tppPerfil ;

typedef enum {
     
 /* 0 */ PER_CondRetOK ,
               /* Concluiu corretamente */

 /* 1 */ PER_CondRetFaltouMemoria ,
               /* Faltou memoria */

 /* 2 */ PER_CondRetPonteiroNulo
      /* Ponteiro Nulo */

   } PER_tpCondRet ;

LIS_tppLista   vtListas[ DIM_VT_LISTA ] ;
PER_tppPerfil  vtPerfis[ DIM_VT_PERFIL] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxLista( int inxLista , int Modo ) ;

   PER_tppPerfil  PER_CriarPerfil( char *pNome, char *pEmail, char *pCidade, char *pDataNasc );

   PER_tpCondRet PER_DestruirPerfil(PER_tppPerfil pPerfil);

   int PER_compararPerfil(void * pValor1, void * pValor2);

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar lista
*
*  $ED Descrição da função
*     Podem ser criadas até 10 listas, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de listas. Provoca vazamento de memória
*     =criarlista                   inxLista
*     =destruirlista                inxLista
*     =esvaziarlista                inxLista
*     =inselemantes                 inxLista  string(nome) string(email) string(cidade) string(dataNasc)  CondRetEsp
*     =inselemapos                  inxLista  string(nome) string(email) string(cidade) string(dataNasc)  CondRetEsp
*     =obtervalorelem               inxLista  string(email)  CondretPonteiro
*     =excluirelem                  inxLista  CondRetEsp
*     =irinicio                     inxLista
*     =irfinal                      inxLista
*     =avancarelem                  inxLista  numElem CondRetEsp
*	    =procurarvalor				        inxLista  string(email)  CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxLista  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ,
          inxPerfil = -1 ;

      TST_tpCondRet CondRet ;
      PER_tpCondRet CondRetPerfil;

      char   StringDado[  DIM_VALOR ] ;
      char   StringDado2[  DIM_VALOR ] ;
      char   StringDado3[  DIM_VALOR ] ;
      char   StringDado4[  DIM_VALOR ] ;
      char * pDado ;
      PER_tppPerfil	  perfil;

      int ValEsp = -1 ;

      int i ;

      int numElem = -1 ;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de lista */

         if ( strcmp( ComandoTeste , RESET_LISTA_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_LISTA ; i++ )
            {
               vtListas[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de lista */

      /* Testar CriarLista */

         else if ( strcmp( ComandoTeste , CRIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            vtListas[ inxLista ] =
                 LIS_CriarLista( DestruirValor, PER_compararPerfil ) ;

            return TST_CompararPonteiroNulo( 1 , vtListas[ inxLista ] ,
               "Erro em ponteiro de nova lista."  ) ;

         } /* fim ativa: Testar CriarLista */

      /* Testar Esvaziar lista lista */

         else if ( strcmp( ComandoTeste , ESVAZIAR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_EsvaziarLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar lista lista */

      /* Testar Destruir lista */

         else if ( strcmp( ComandoTeste , DESTRUIR_LISTA_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            LIS_DestruirLista( vtListas[ inxLista ] ) ;
            vtListas[ inxLista ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir lista */

      /* Testar inserir elemento antes */

         else if ( strcmp( ComandoTeste , INS_ELEM_ANTES_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issssii" ,
                       &inxLista , StringDado, StringDado2, StringDado3, StringDado4 , &inxPerfil, &CondRetEsp ) ;

            if ( ( numLidos != 7 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */


            vtPerfis [ inxPerfil ] = PER_CriarPerfil(StringDado, StringDado2, StringDado3,  StringDado4);

            if (vtPerfis [ inxPerfil ]==NULL)
            	return TST_CondRetNaoConhec;

            CondRet = LIS_InserirElementoAntes( vtListas[ inxLista ] , vtPerfis [ inxPerfil ] ) ;

            if ( CondRet != LIS_CondRetOK )
            {
               PER_DestruirPerfil( vtPerfis [ inxPerfil ] );
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir antes."                   ) ;

         } /* fim ativa: Testar inserir elemento antes */

      /* Testar inserir elemento apos */

         else if ( strcmp( ComandoTeste , INS_ELEM_APOS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "issssii" ,
                       &inxLista , StringDado , StringDado2, StringDado3, StringDado4, &inxPerfil, &CondRetEsp ) ;

            if ( ( numLidos != 7 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

             vtPerfis [ inxPerfil ] = PER_CriarPerfil(StringDado, StringDado2, StringDado3,  StringDado4);

            if (vtPerfis [ inxPerfil ]==NULL)
            	return TST_CondRetNaoConhec;

            CondRet = LIS_InserirElementoApos( vtListas[ inxLista ] , vtPerfis [ inxPerfil ] ) ;

            if ( CondRet != LIS_CondRetOK )
            {
               PER_DestruirPerfil ( vtPerfis [ inxPerfil ] );
            } /* if */

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir apos."                   ) ;

         } /* fim ativa: Testar inserir elemento apos */

      /* Testar excluir simbolo */

         else if ( strcmp( ComandoTeste , EXC_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                  &inxLista , &CondRetEsp ) ;

            if ( ( numLidos != 2 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_ExcluirElemento( vtListas[ inxLista ] ) ,
                     "Condição de retorno errada ao excluir."   ) ;

         } /* fim ativa: Testar excluir simbolo */

      /* Testar obter valor do elemento corrente */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado , &ValEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            vtPerfis [ inxPerfil ] =  (PER_tppPerfil) LIS_ObterValor( vtListas[ inxLista ] ) ;

            if ( ValEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , vtPerfis [ inxPerfil ] ,
                         "Valor não deveria existir." ) ;
            } /* if */

			else
            {
               return TST_CompararPonteiroNulo( 1 , vtPerfis [ inxPerfil ] ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

         } /* fim ativa: Testar obter valor do elemento corrente */

      /* Testar ir para o elemento inicial */

         else if ( strcmp( ComandoTeste , IR_INICIO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrInicioLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar ir para o elemento inicial */

      /* LIS  &Ir para o elemento final */

         else if ( strcmp( ComandoTeste , IR_FIM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" , &inxLista ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            IrFinalLista( vtListas[ inxLista ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: LIS  &Ir para o elemento final */

      /* LIS  &Avançar elemento */

         else if ( strcmp( ComandoTeste , AVANCAR_ELEM_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" , &inxLista , &numElem ,
                                &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            return TST_CompararInt( CondRetEsp ,
                      LIS_AvancarElementoCorrente( vtListas[ inxLista ] , numElem ) ,
                      "Condicao de retorno errada ao avancar" ) ;

         } /* fim ativa: LIS  &Avançar elemento */

      /* Testar procurar valor na lista   */

        else if ( strcmp( ComandoTeste , PROCURAR_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                       &inxLista , &inxPerfil, &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
            
            CondRet = LIS_ProcurarValor( vtListas[ inxLista ] , vtPerfis[inxPerfil]);
             

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao procurar valor."   ) ;

         } /* fim ativa: Testar */

		  /* Testar procurar valor por conteudo na lista */

         else if ( strcmp( ComandoTeste , PROCURAR_CONTEUDO_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxLista , StringDado, &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxLista( inxLista , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */
				
            CondRet = LIS_ProcurarPorConteudo( vtListas[ inxLista ] , StringDado ) ;

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao procurar valor."   ) ;

         } /* fim ativa: Testar procurar valor em lista */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar lista */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      PER_DestruirPerfil ( (PER_tppPerfil) pValor );

   } /* Fim função: TLIS -Destruir valor */


/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de lista
*
***********************************************************************/

   int ValidarInxLista( int inxLista , int Modo )
   {

      if ( ( inxLista <  0 )
        || ( inxLista >= DIM_VT_LISTA ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtListas[ inxLista ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtListas[ inxLista ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de lista */


  /************************* Funções de manipulação de perfil **********************************/


/***************************************************************************
 *
 *  Função: PER &Criar Perfil
 *****/

PER_tppPerfil  PER_CriarPerfil( char *pNome, char *pEmail, char *pCidade, char *pDataNasc ) {
    
  PER_tppPerfil pPerfil = ( PER_tppPerfil ) malloc( sizeof( PER_tpPerfil ));
  if( pPerfil == NULL ) {
    return pPerfil ;
  } /* if */
    
  strcpy(pPerfil->nome, pNome);
  strcpy(pPerfil->email, pEmail);
  strcpy(pPerfil->cidade, pCidade);
  strcpy(pPerfil->dataNasc, pDataNasc);
  

  return pPerfil ;
    
} /* Fim função: PER  &Criar Perfil */

/***************************************************************************
 *
 *  Função: PER &Destruir Perfil
 *****/

PER_tpCondRet PER_DestruirPerfil(PER_tppPerfil pPerfil) {

    if(pPerfil == NULL) {
        return PER_CondRetPonteiroNulo;
    } /* if */

    free(pPerfil);

    return PER_CondRetOK;

} /* Fim função: PER  &Destruir Perfil */


/***************************************************************************
 *
 *  Função: PER Compara Perfil
 *****/

int PER_compararPerfil(void * pValor1, void * pValor2) {
    PER_tppPerfil pPerfil;
    char *email;
    pPerfil = (PER_tppPerfil) pValor1;
    email = (char*) pValor2;

    return strcmp(email,pPerfil->email);

} /* Fim função: PER  Comparar Perfil */  


/********** Fim do módulo de implementação: TLIS Teste lista de símbolos **********/

