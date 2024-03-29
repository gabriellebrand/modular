/***************************************************************************
*  $MCI M�dulo de implementa��o: ARV  M�dulo �rvore
*
*  Arquivo gerado:              ARVORE.C
*  Letras identificadoras:      ARV
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: C:\AUTOTEST\PROJETOS\INSTRUM.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores: avs
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     4       avs   01/fev/2006 criar linguagem script simb�lica
*     3       avs   08/dez/2004 uniformiza��o dos exemplos
*     2       avs   07/jul/2003 unifica��o de todos os m�dulos em um s� projeto
*     1       avs   16/abr/2003 in�cio desenvolvimento
*
***************************************************************************/

#include   <malloc.h>
#include   <stdio.h>
#include   <memory.h>

#define ARVORE_OWN
#include "ARVORE.H"
#undef ARVORE_OWN

#ifdef _DEBUG
   #include   "Generico.h"
   #include   "Conta.h"
   #include   "cespdin.h"
   #include   "..\\tabelas\\IdTiposEspaco.def"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor do n� da �rvore
*
*
*  $ED Descri��o do tipo
*     Descreve a organiza��o do n�
*
***********************************************************************/

   typedef struct tgNoArvore {

         #ifdef _DEBUG

         struct tgArvore * pCabeca ;
               /* Ponteiro para cabeca
               *
               *$ED Descri��o
               *   Todos os n�s da �rvore devem apontar para a respectiva cabe�a.
               *   Esse ponteiro corresponde a um identificador da �rvore para fins
               *   de verifica��o da integridade. */

         #endif

         struct tgNoArvore * pNoPai ;
               /* Ponteiro para pai
               *
               *$EED Assertivas estruturais
               *   � NULL sse o n� � raiz
               *   Se n�o for raiz, um de pNoEsq ou pNoDir de pNoPai do n�
               *   corrente apontam para o n� corrente */

         struct tgNoArvore * pNoEsq ;
               /* Ponteiro para filho � esquerda
               *
               *$EED Assertivas estruturais
               *   se pNoEsq do n� X != NULL ent�o pNoPai de pNoEsq aponta para o n� X */

         struct tgNoArvore * pNoDir ;
               /* Ponteiro para filho � direita
               *
               *$EED Assertivas estruturais
               *   se pNoDir do n� X != NULL ent�o pNoPai de pNoDir aponta para o n� X */

         char Valor ;
               /* Valor do n� */

   } tpNoArvore ;

/***********************************************************************
*
*  $TC Tipo de dados: ARV Descritor da cabe�a de uma �rvore
*
*
*  $ED Descri��o do tipo
*     A cabe�a da �rvore � o ponto de acesso para uma determinada �rvore.
*     Por interm�dio da refer�ncia para o n� corrente e do ponteiro
*     pai pode-se navegar a �rvore.
*
***********************************************************************/

   typedef struct tgArvore {

         tpNoArvore * pNoRaiz ;
               /* Ponteiro para a raiz da �rvore */

         tpNoArvore * pNoCorr ;
               /* Ponteiro para o n� corrente da �rvore */

   } tpArvore ;

/*****  Dados encapsulados no m�dulo  *****/

      #ifdef _DEBUG

      static char EspacoLixo[ 256 ] =
             "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" ;
            /* Espa�o de dados lixo usado ao testar */

      #endif

/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static tpNoArvore * CriarNo( tpArvore * pArvore , char ValorParm ) ;

   static ARV_tpCondRet CriarNoRaiz( tpArvore * pArvore , char ValorParm ) ;

   static void DestroiArvore( tpNoArvore * pNo ) ;

#ifdef _DEBUG

   static ARV_tpCondRet VerificarNo( tpNoArvore * pNo ) ;

#endif

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***************************************************************************
*
*  Fun��o: ARV  &Criar �rvore
*  ****/

   ARV_tpCondRet ARV_CriarArvore( void ** ppArvoreParm )
   {

      tpArvore * pArvore ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_CriarArvore" ) ;
      #endif

      if ( *ppArvoreParm != NULL )
      {
         ARV_DestruirArvore( ppArvoreParm ) ;
      } /* if */

      pArvore = ( tpArvore * ) malloc( sizeof( tpArvore )) ;
      if ( pArvore == NULL )
      {
         return ARV_CondRetFaltouMemoria ;
      } /* if */

      pArvore->pNoRaiz = NULL ;
      pArvore->pNoCorr = NULL ;

      #ifdef _DEBUG
         CED_DefinirTipoEspaco( pArvore , ARV_TipoEspacoCabeca ) ;
      #endif

      *ppArvoreParm = pArvore ;

      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV  &Criar �rvore */

/***************************************************************************
*
*  Fun��o: ARV  &Destruir �rvore
*  ****/

   void ARV_DestruirArvore( void ** ppArvoreParm )
   {

      tpArvore * pArvore ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_DestruirArvore" ) ;
      #endif

      pArvore = ( tpArvore * )( * ppArvoreParm ) ;
      if ( pArvore != NULL )
      {
         if ( pArvore->pNoRaiz != NULL )
         {
            DestroiArvore( pArvore->pNoRaiz ) ;
         } /* if */
         free( pArvore ) ;
         *ppArvoreParm = NULL ;
      } /* if */

   } /* Fim fun��o: ARV  &Destruir �rvore */

/***************************************************************************
*
*  Fun��o: ARV  &Adicionar filho � esquerda
*  ****/

   ARV_tpCondRet ARV_InserirEsquerda( void * pArvoreParm , char ValorParm )
   {

      tpArvore   * pArvore ;

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_InserirEsquerda" ) ;
      #endif

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * )( pArvoreParm ) ;

      /* Tratar �rvore vazia, esquerda */

         CondRet = CriarNoRaiz( pArvoreParm , ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar n� � esquerda de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoEsq == NULL )
         {
            pNo = CriarNo( pArvore , ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoEsq    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      return ARV_CondRetNaoEhFolha ;

   } /* Fim fun��o: ARV  &Adicionar filho � esquerda */

/***************************************************************************
*
*  Fun��o: ARV  &Adicionar filho � direita
*  ****/

   ARV_tpCondRet ARV_InserirDireita( void * pArvoreParm , char ValorParm )
   {

      tpArvore * pArvore ;

      ARV_tpCondRet CondRet ;

      tpNoArvore * pCorr ;
      tpNoArvore * pNo ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_InserirDireita" ) ;
      #endif

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * )( pArvoreParm ) ;

      /* Tratar �rvore vazia, direita */

         CondRet = CriarNoRaiz( pArvoreParm , ValorParm ) ;
         if ( CondRet != ARV_CondRetNaoCriouRaiz )
         {
            return CondRet ;
         } /* if */

      /* Criar n� � direita de folha */

         pCorr = pArvore->pNoCorr ;
         if ( pCorr == NULL )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( pCorr->pNoDir == NULL )
         {
            pNo = CriarNo( pArvore , ValorParm ) ;
            if ( pNo == NULL )
            {
               return ARV_CondRetFaltouMemoria ;
            } /* if */
            pNo->pNoPai      = pCorr ;
            pCorr->pNoDir    = pNo ;
            pArvore->pNoCorr = pNo ;

            return ARV_CondRetOK ;
         } /* if */

      return ARV_CondRetNaoEhFolha ;

   } /* Fim fun��o: ARV  &Adicionar filho � direita */

/***************************************************************************
*
*  Fun��o: ARV  &Ir para n� pai
*  ****/

   ARV_tpCondRet ARV_IrPai( void * pArvoreParm )
   {

      tpArvore * pArvore ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_IrPai" ) ;
      #endif

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * ) pArvoreParm ;

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoPai != NULL )
      {
         pArvore->pNoCorr = pArvore->pNoCorr->pNoPai ;
         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNohEhRaiz ;

   } /* Fim fun��o: ARV  &Ir para n� pai */

/***************************************************************************
*
*  Fun��o: ARV  &Ir para n� � esquerda
*  ****/

   ARV_tpCondRet ARV_IrNoEsquerda( void * pArvoreParm )
   {

      tpArvore * pArvore ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_IrNoEsquerda" ) ;
      #endif

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * ) pArvoreParm ;

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoEsq == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoEsq ;
      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV  &Ir para n� � esquerda */

/***************************************************************************
*
*  Fun��o: ARV  &Ir para n� � direita
*  ****/

   ARV_tpCondRet ARV_IrNoDireita( void * pArvoreParm )
   {

      tpArvore * pArvore ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_IrNoDireita" ) ;
      #endif

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * ) pArvoreParm ;

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      if ( pArvore->pNoCorr->pNoDir == NULL )
      {
         return ARV_CondRetNaoPossuiFilho ;
      } /* if */

      pArvore->pNoCorr = pArvore->pNoCorr->pNoDir ;
      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV  &Ir para n� � direita */

/***************************************************************************
*
*  Fun��o: ARV  &Obter valor corrente
*  ****/

   ARV_tpCondRet ARV_ObterValorCorr( void * pArvoreParm , char * ValorParm )
   {

      tpArvore * pArvore ;

      #ifdef _DEBUG
         CNT_CONTAR( "ARV_ObterValorCorr" ) ;
      #endif

      if ( pArvoreParm == NULL )
      {
         return ARV_CondRetArvoreNaoExiste ;
      } /* if */

      pArvore = ( tpArvore * ) pArvoreParm ;

      if ( pArvore->pNoCorr == NULL )
      {
         return ARV_CondRetArvoreVazia ;
      } /* if */

      * ValorParm = pArvore->pNoCorr->Valor ;
      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV  &Obter valor corrente */

#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: ARV  &Verificar uma �rvore
*  ****/

   ARV_tpCondRet ARV_VerificarArvore( void * pArvoreParm )
   {

      tpArvore * pArvore = NULL ;

      if ( ARV_VerificarCabeca( pArvoreParm ) != ARV_CondRetOK )
      {
         return ARV_CondRetErroEstrutura ;
      } /* if */

      CED_MarcarEspacoAtivo( pArvoreParm ) ;

      pArvore = ( tpArvore * ) ( pArvoreParm ) ;

      return VerificarNo( pArvore->pNoRaiz ) ;

   } /* Fim fun��o: ARV  &Verificar uma �rvore */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: ARV  &Verificar um n� cabe�a
*  ****/

   ARV_tpCondRet ARV_VerificarCabeca( void * pCabecaParm )
   {

      tpArvore * pArvore = NULL ;

      /* Verifica o tipo do espa�o */

         if ( pCabecaParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar cabe�a inexistente." ) ;
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( ! CED_VerificarEspaco( pCabecaParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espa�o acusou erro." ) ;
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( TST_CompararInt( ARV_TipoEspacoCabeca ,
              CED_ObterTipoEspaco( pCabecaParm ) ,
              "Tipo do espa�o de dados n�o � cabe�a de �rvore." ) != TST_CondRetOK )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         pArvore = ( tpArvore * )( pCabecaParm ) ;

      /* Verifica raiz da �rvore */

         if ( pArvore->pNoRaiz != NULL )
         {
            if ( TST_CompararPonteiro( pCabecaParm , pArvore->pNoRaiz->pCabeca ,
                 "N� raiz n�o aponta para cabe�a." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } else {
            if ( TST_CompararPonteiro( NULL , pArvore->pNoCorr ,
                 "�rvore vazia tem n� corrente n�o NULL." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      /* Verifica corrente */

         if ( pArvore->pNoCorr != NULL )
         {
            if ( TST_CompararPonteiro( pCabecaParm , pArvore->pNoCorr->pCabeca ,
                 "N� corrente n�o aponta para cabe�a." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } else {
            if ( TST_CompararPonteiro( NULL , pArvore->pNoRaiz ,
                 "�rvore n�o vazia tem n� corrente NULL." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      return ARV_CondRetOK ;

   } /* Fim fun��o: ARV  &Verificar um n� cabe�a */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: ARV  &Verificar um n� de estrutura
*  ****/

   ARV_tpCondRet ARV_VerificarNo( void * pNoParm )
   {

      tpNoArvore * pNo     = NULL ;
      tpArvore   * pArvore = NULL ;

      /* Verificar se � n� estrutural */

         if ( pNoParm == NULL )
         {
            TST_NotificarFalha( "Tentou verificar n� inexistente." ) ;
            return ARV_CondRetErroEstrutura ;

         } /* if */

         if ( ! CED_VerificarEspaco( pNoParm , NULL ))
         {
            TST_NotificarFalha( "Controle do espa�o acusou erro." ) ;
            return ARV_CondRetErroEstrutura ;
         } /* if */

         if ( TST_CompararInt( ARV_TipoEspacoNo ,
              CED_ObterTipoEspaco( pNoParm ) ,
              "Tipo do espa�o de dados n�o � n� de �rvore." ) != TST_CondRetOK )
         {
            return ARV_CondRetErroEstrutura ;
         } /* if */

         pNo     = ( tpNoArvore * )( pNoParm ) ;
         pArvore = pNo->pCabeca ;

      /* Verificar cabe�a */

         if ( pArvore->pNoRaiz != NULL  )
         {
            if ( TST_CompararPonteiro( pArvore , pArvore->pNoRaiz->pCabeca ,
                 "N� n�o pertence � �rvore." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } else
         {
            return TST_NotificarFalha( "N� pertence a �rvore vazia." ) ;
         } /* if */

      /* Verificar pai */

         if ( pNo->pNoPai != NULL )
         {
            if ( ( pNo->pNoPai->pNoEsq != pNo )
              && ( pNo->pNoPai->pNoDir != pNo ))
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } else
         {
            if ( TST_CompararPonteiro( pNo , pArvore->pNoRaiz ,
                 "N� raiz n�o � apontado por cabe�a da �rvore." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      /* Verificar filho � esquerda */

         if ( pNo->pNoEsq != NULL )
         {
            if ( TST_CompararPonteiro( pNo , pNo->pNoEsq->pNoPai ,
                 "Pai de filho � esquerda n�o � este n�." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
            if ( TST_CompararPonteiro( pArvore , pNo->pNoEsq->pCabeca ,
                 "Filho � esquerda n�o pertence � mesma �rvore." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } /* if */

      /* Verificar filho � direita */

         if ( pNo->pNoDir != NULL )
         {
            if ( TST_CompararPonteiro( pNo , pNo->pNoDir->pNoPai ,
                 "Pai de filho � direita n�o � este n�." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
            if ( TST_CompararPonteiro( pArvore , pNo->pNoDir->pCabeca ,
                 "Filho � direita n�o pertence � mesma �rvore." ) != TST_CondRetOK )
            {
               return ARV_CondRetErroEstrutura ;
            } /* if */
         } /* if */
      return ARV_CondRetOK ;
   } /* Fim fun��o: ARV  &Verificar um n� de estrutura */

#endif

#ifdef _DEBUG

/***************************************************************************
*
*  Fun��o: ARV  &Deturpar �rvore
*  ****/

   void ARV_Deturpar( void * pArvoreParm ,
                      ARV_tpModosDeturpacao ModoDeturpar )
   {

      tpArvore * pArvore = NULL ;

      if ( pArvoreParm == NULL )
      {
         return ;
      } /* if */

      pArvore = ( tpArvore * )( pArvoreParm ) ;

      switch ( ModoDeturpar ) {

      /* Modifica o tipo da cabe�a */

         case DeturpaTipoCabeca :
         {
            CED_DefinirTipoEspaco( pArvore , CED_ID_TIPO_VALOR_NULO ) ;
            break ;
         } /* fim ativa: Modifica o tipo da cabe�a */

      /* Anula ponteiro raiz */

         case DeturpaRaizNula :
         {
            pArvore->pNoRaiz = NULL ;
            break ;
         } /* fim ativa: Anula ponteiro raiz */

      /* Anula ponteiro corrente */

         case DeturpaCorrenteNulo :
         {
             pArvore->pNoCorr = NULL ;
            break ;
         } /* fim ativa: Anula ponteiro corrente */

      /* Faz raiz apontar para lixo */

         case DeturpaRaizLixo :
         {
            pArvore->pNoRaiz = ( tpNoArvore * )( EspacoLixo ) ;
            break ;
         } /* fim ativa: Faz raiz apontar para lixo */

      /* Faz corrente apontar para lixo */

         case DeturpaCorrenteLixo :
         {
            pArvore->pNoCorr = ( tpNoArvore * )( EspacoLixo ) ;
            break ;
         } /* fim ativa: Faz corrente apontar para lixo */

      /* Deturpar espa�o cabeca */

         case DeturparEspacoCabeca :
         {
            memcpy( (( char * )( pArvore )) - 10 , "????" , 4 ) ;
            break ;
         } /* fim ativa: Deturpar espa�o cabeca */

      /* Deturpa n�o */

         default :

         if ( pArvore->pNoCorr != NULL )
         {
            switch ( ModoDeturpar ) {
            /* Modifica tipo n� corrente */
               case DeturpaTipoNo :
               {
                  CED_DefinirTipoEspaco( pArvore->pNoCorr , CED_ID_TIPO_VALOR_NULO ) ;
                  break ;
               } /* fim ativa: Modifica tipo n� corrente */

            /* Anula ponteiro cabe�a */
               case DeturpaPtCabecaNulo :
               {
                  pArvore->pNoCorr->pCabeca = NULL ;
                  break ;
               } /* fim ativa: Anula ponteiro cabe�a */

            /* Anula ponteiro pai */
               case DeturpaPtPaiNulo :
               {
                  pArvore->pNoCorr->pNoPai = NULL ;
                  break ;
               } /* fim ativa: Anula ponteiro pai */

            /* Anula ponteiro filho esquerda */
               case DeturpaPtEsqNulo :
               {
                  pArvore->pNoCorr->pNoEsq = NULL ;
                  break ;
               } /* fim ativa: Anula ponteiro filho esquerda */

            /* Anula ponteiro filho direita */
               case DeturpaPtDirNulo :
               {
                  pArvore->pNoCorr->pNoDir = NULL ;
                  break ;
               } /* fim ativa: Anula ponteiro filho direita */
                    
            /* Faz ponteiro cabe�a apontar para lixo */
               case DeturpaPtCabecaLixo :
               {
                  pArvore->pNoCorr->pCabeca = ( tpArvore * )( EspacoLixo ) ;
                  break ;
               } /* fim ativa: Faz ponteiro cabe�a apontar para lixo */

            /* Faz ponteiro pai apontar para lixo */
               case DeturpaPtPaiLixo :
               {
                  pArvore->pNoCorr->pNoPai = ( tpNoArvore * )( EspacoLixo ) ;
                  break ;
               } /* fim ativa: Faz ponteiro pai apontar para lixo */

            /* Faz ponteiro filho esquerda apontar para lixo */
               case DeturpaPtEsqLixo :
               {
                  pArvore->pNoCorr->pNoEsq = ( tpNoArvore * )( EspacoLixo ) ;
                  break ;
               } /* fim ativa: Faz ponteiro filho esquerda apontar para lixo */

            /* Faz ponteiro filho direita apontar para lixo */
               case DeturpaPtDirLixo :
               {
                  pArvore->pNoCorr->pNoDir = ( tpNoArvore * )( EspacoLixo ) ;
                  break ;
               } /* fim ativa: Faz ponteiro filho direita apontar para lixo */

            /* Atribui valor fora do dom�nio do espa�o */
               case DeturpaValor :
               {
                  memcpy( &( pArvore->pNoCorr->Valor ) , "<<<<<" , 5 ) ;
                  break ;
               } /* fim ativa: Atribui valor fora do dom�nio do espa�o */

            /* Deturpar espa�o no */
               case DeturparEspacoNo :
               {
                  memcpy( (( char * )( pArvore->pNoCorr )) - 50 , "????????" , 8 ) ;
                  break ;
               } /* fim ativa: Deturpar espa�o no */

            } /* fim seleciona: Deturpa n�o */
            break ;
         } /* fim ativa: Deturpa n�o */
      } /* fim seleciona: Raiz de ARV  &Deturpar �rvore */
   } /* Fim fun��o: ARV  &Deturpar �rvore */

#endif


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: ARV  -Criar n� da �rvore
*
*  $FV Valor retornado
*     Ponteiro para o n� criado.
*     Ser� NULL caso a mem�ria tenha se esgotado.
*     Os ponteiros do n� criado estar�o nulos e o valor � igual ao do
*     par�metro.
*
***********************************************************************/

   tpNoArvore * CriarNo( tpArvore * pArvore , char ValorParm )
   {

      tpNoArvore * pNo ;

      pNo = ( tpNoArvore * ) malloc( sizeof( tpNoArvore )) ;
      if ( pNo == NULL )
      {
         return NULL ;
      } /* if */

      #ifdef _DEBUG
         CED_DefinirTipoEspaco( pNo , ARV_TipoEspacoNo ) ;
         pNo->pCabeca = pArvore ;
      #else
         pArvore = NULL ;
      #endif

      pNo->pNoPai  = NULL ;
      pNo->pNoEsq  = NULL ;
      pNo->pNoDir  = NULL ;
      pNo->Valor   = ValorParm ;

      return pNo ;

   } /* Fim fun��o: ARV  -Criar n� da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV  -Criar n� raiz da �rvore
*
*  $FV Valor retornado
*     ARV_CondRetOK
*     ARV_CondRetFaltouMemoria
*     ARV_CondRetNaoCriouRaiz
*
***********************************************************************/

   ARV_tpCondRet CriarNoRaiz( tpArvore * pArvore , char ValorParm )
   {

      tpNoArvore * pNo ;

      if ( pArvore->pNoRaiz == NULL )
      {
         pNo = CriarNo( pArvore , ValorParm ) ;
         if ( pNo == NULL )
         {
            return ARV_CondRetFaltouMemoria ;
         } /* if */
         pArvore->pNoRaiz = pNo ;
         pArvore->pNoCorr = pNo ;

         return ARV_CondRetOK ;
      } /* if */

      return ARV_CondRetNaoCriouRaiz ;

   } /* Fim fun��o: ARV  -Criar n� raiz da �rvore */


/***********************************************************************
*
*  $FC Fun��o: ARV  -Destruir a estrutura da �rvore
*
*  $EAE Assertivas de entradas esperadas
*     pNoArvore != NULL
*
***********************************************************************/

   void DestroiArvore( tpNoArvore * pNo )
   {

      if ( pNo->pNoEsq != NULL )
      {
         DestroiArvore( pNo->pNoEsq ) ;
      } /* if */

      if ( pNo->pNoDir != NULL )
      {
         DestroiArvore( pNo->pNoDir ) ;
      } /* if */

      free( pNo ) ;

   } /* Fim fun��o: ARV  -Destruir a estrutura da �rvore */

#ifdef _DEBUG


/***********************************************************************
*
*  $FC Fun��o: ARV  -Explorar verificando os n�s de uma �rvore
*
*  $ED Descri��o da fun��o
*     Percorre recursivamente a �rvore verificando os n�s � medida que forem
*     visitados. Caso seja encontrado alguma falha, a verifica��o ser�
*     suspensa. Portanto, no caso de falha, � poss�vel que nem todos
*     os n�s da �rvore sejam visitados.
*
***********************************************************************/

   ARV_tpCondRet VerificarNo( tpNoArvore * pNo )
   {

      ARV_tpCondRet CondErro = ARV_CondRetOK ;

      if ( pNo == NULL )
      {
         return ARV_CondRetOK ;
      } /* if */

      CED_MarcarEspacoAtivo( pNo ) ;

      CondErro = ARV_VerificarNo( pNo ) ;

      if ( CondErro == ARV_CondRetOK )
      {
         CondErro = VerificarNo( pNo->pNoEsq ) ;
      } /* if */

      if ( CondErro == ARV_CondRetOK )
      {
         CondErro = VerificarNo( pNo->pNoDir ) ;
      } /* if */

      return CondErro ;

   } /* Fim fun��o: ARV  -Explorar verificando os n�s de uma �rvore */

#endif

/********** Fim do m�dulo de implementa��o: ARV  M�dulo �rvore **********/

