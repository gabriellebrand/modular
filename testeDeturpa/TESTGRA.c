/***************************************************************************
*  $MCI M�dulo de implementa��o: TGRA Teste do m�dulo Grafo
*
*  Arquivo gerado:              TestGRA.c
*  Letras identificadoras:      TGRA
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: Trabalho 2 - Programa;c�o Modular
*  Gestor:  LES/DI/PUC-Rio
*  Autor:  WB - Wellington Bezerra
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1       WB   09/out/2017 in�cio desenvolvimento
*
***************************************************************************/


#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Grafo.h"
#include    "Lista.h"


static const char CRIAR_GRAFO_CMD            [ ] = "=criargrafo";
static const char CRIAR_VERTICE_CMD          [ ] = "=criarvertice";
static const char IR_VERTICE_CMD             [ ] = "=irvertice";
static const char EXCLUIR_VERTICE_CMD        [ ] = "=excluirvertice";
static const char EXCLUIR_GRAFO_CMD          [ ] = "=excluirgrafo";
static const char CRIAR_ARESTA_CMD           [ ] = "=criararesta";
static const char EXCLUIR_ARESTA_CMD         [ ] = "=excluiraresta";
static const char IR_VIZINHO_CMD             [ ] = "=irvizinho";
static const char OBTER_VALOR_CMD            [ ] = "=obtervalor";
static const char AVANCAR_VIZ_CMD            [ ] = "=avancarvizinho";
static const char CRIAR_GRAFO_RET_CMD        [ ] = "=criargraforet";

#ifdef _DEBUG
static const char DETURPAR_GRAFO_CMD         [ ] = "=deturpar";
static const char VERIFICAR_GRAFO_CMD        [ ] = "=verificar";
#endif


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_GRAFO   10

GRA_tppGrafo   vtGrafos[ DIM_VT_GRAFO ] ;

typedef struct PER_tagPerfil {

    char nome[100];
        /* Nome do perfil */
    
    char email[20];
        /* Email do perfil */
    
    char cidade[20];
        /* Cidade do perfil */
    
    char dataNasc[10];
        /* data de nascimento do perfil */

} PER_tpPerfil ;

typedef struct PER_tagPerfil * PER_tppPerfil ;


/***** Prot�tipos das fun��es encapuladas no m�dulo *****/

   static void DestruirValor( void * pValor ) ;

   static int CompararValor(void * pValor1, void * pValor2) ;

   static int ValidarInxGrafo( int inxGrafo , int Modo ) ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/


/***********************************************************************
*
*  $FC Fun��o: TGRA &Testar Grafo
*
*  $ED Descri��o da fun��o
*     Podem ser criadas at� 10 grafos, identificados pelos �ndices 0 a 9
*
*     Comandos dispon�veis:
*
* =criargrafo            inxGrafo
* =criarvertice          inxGrafo nome email cidade idade CondRetEsperada
* =irvertice             inxGrafo email CondRetEsperada
* =excluirvertice        inxGrafo CondRetEsperada
* =excluirgrafo          inxGrafo CondRetEsperada 
* =criararesta           inxGrafo email email2 CondRetEsperada 
* =excluiraresta         inxGrafo email email2 CondRetEsperada
* =irvizinho             inxGrafo email CondRetEsperada
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ) {

  int numLidos = -1,
      inxGrafo = -1,
      numElem = -1,
      param;

  char nome[100],
       email[100],
       email2[100],
       cidade[100],
       dataNasc[10];

  PER_tppPerfil pPerfil;
  GRA_tpCondRet CondRetObtido;
  GRA_tpCondRet CondRetEsperada;

  /* Testar Criar Grafo */

      if ( strcmp( ComandoTeste , CRIAR_GRAFO_CMD ) == 0 )
      {

        numLidos = LER_LerParametros( "i" ,
         &inxGrafo ) ;

        if ( numLidos != 1  || !ValidarInxGrafo( inxGrafo , VAZIO )) {
          return TST_CondRetParm ;
        } /* if */
        vtGrafos[ inxGrafo ] =
        GRA_CriarGrafo( DestruirValor , CompararValor ) ;



        return TST_CompararPonteiroNulo( 1 , vtGrafos[ inxGrafo ] ,
           "Erro em ponteiro de novo grafo."  ) ;

      } /* fim ativa: Testar Criar Grafo */

          /* Testar Criar Grafo com condicao de retorno esperada */

      else if ( strcmp( ComandoTeste , CRIAR_GRAFO_RET_CMD ) == 0 )
      {

        numLidos = LER_LerParametros( "ii" ,
         &inxGrafo, &CondRetEsperada) ;

        if ( numLidos != 2  || !ValidarInxGrafo( inxGrafo , VAZIO )) {
          return TST_CondRetParm ;
        } /* if */
        vtGrafos[ inxGrafo ] =
        GRA_CriarGrafo( DestruirValor , CompararValor ) ;

        
        return TST_CompararPonteiroNulo( CondRetEsperada , vtGrafos[ inxGrafo ] ,
           "Erro em ponteiro de novo grafo."  ) ;

      } /* fim ativa: Testar Criar Grafo com condicao de retorno esperada */

  /* Testar Criar vertice */

      else if ( strcmp( ComandoTeste , CRIAR_VERTICE_CMD ) == 0 ) {

          numLidos = LER_LerParametros( "issssi" ,
                       &inxGrafo , &nome, &email, &cidade, &dataNasc , &CondRetEsperada ) ;
          if ( numLidos != 6  ) {
            return TST_CondRetParm ;
          } /* if */

          pPerfil = ( PER_tppPerfil ) malloc( sizeof( PER_tpPerfil ));
          if ( pPerfil == NULL ) {
               return TST_CondRetMemoria ;
          } /* if */

          strcpy( pPerfil->nome , nome ) ;
          strcpy( pPerfil->email , email ) ;
          strcpy( pPerfil->cidade , cidade ) ;
          strcpy( pPerfil->dataNasc, dataNasc ) ;

          CondRetObtido = GRA_CriarVertice(vtGrafos[ inxGrafo ], pPerfil, email);

          return TST_CompararInt( CondRetEsperada , CondRetObtido ,
              "Retorno errado criar vertice." );

      } /* fim ativa: Testar Criar vertice */

  /* Testar Ir Vertice */

      else if ( strcmp( ComandoTeste , IR_VERTICE_CMD ) == 0 ) {

          numLidos = LER_LerParametros( "isi" ,
                       &inxGrafo , &email, &CondRetEsperada ) ;
          if ( numLidos != 3 ) {
            return TST_CondRetParm ;
          } /* if */
          
          CondRetObtido = GRA_IrVertice (vtGrafos[ inxGrafo ], email);

          return TST_CompararInt( CondRetEsperada , CondRetObtido ,
              "Retorno errado ao ir no vertice" );

      } /* fim ativa: Ir Vertice */

  /* Testar Excluir Vertice Corrente*/

      else if ( strcmp( ComandoTeste , EXCLUIR_VERTICE_CMD  ) == 0 ) {

          numLidos = LER_LerParametros( "ii" ,
                       &inxGrafo , &CondRetEsperada ) ;
          if ( numLidos != 2 ) {
            return TST_CondRetParm ;
          } /* if */
          
          CondRetObtido = GRA_ExcluirVertCorr(vtGrafos[ inxGrafo ]);

          return TST_CompararInt( CondRetEsperada , CondRetObtido ,
              "Retorno errado ao excluir vertice." );

      } /* fim ativa: Excluir Vertice Corrente*/

  /* Testar Excluir Grafo */

      else if ( strcmp( ComandoTeste , EXCLUIR_GRAFO_CMD ) == 0 )
      {

        numLidos = LER_LerParametros( "ii" ,
         &inxGrafo, &CondRetEsperada ) ;

        if ( numLidos != 2 ) {
          return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = GRA_DestruirGrafo(&vtGrafos[ inxGrafo ]);

        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
              "Retorno errado excluir grafo." );

      } /* fim ativa: Testar Excluir Grafo */

  /* Testar Criar Aresta */

      else if ( strcmp( ComandoTeste , CRIAR_ARESTA_CMD ) == 0 )
      {

        numLidos = LER_LerParametros( "issi" ,
         &inxGrafo, &email, &email2, &CondRetEsperada ) ;

        if ( numLidos != 4 ) {
          return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = GRA_CriarAresta(vtGrafos[ inxGrafo ], email, email2);

        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
              "Retorno errado criar aresta." );

      } /* fim ativa: Testar Criar Aresta */

  /* Testar Excluir Aresta */

      else if ( strcmp( ComandoTeste , EXCLUIR_ARESTA_CMD ) == 0 )
      {

        numLidos = LER_LerParametros( "issi" ,
         &inxGrafo, &email, &email2, &CondRetEsperada ) ;

        if ( numLidos != 4 ) {
          return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = GRA_ExcluirAresta(vtGrafos[ inxGrafo ], email, email2);

        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
              "Retorno errado excluir aresta." );

      } /* fim ativa: Testar Excluir Aresta */

  /* Testar Ir Vizinho */

      else if ( strcmp( ComandoTeste , IR_VIZINHO_CMD ) == 0 )
      {

        numLidos = LER_LerParametros( "isi" ,
         &inxGrafo, &email, &CondRetEsperada ) ;

        if ( numLidos != 3 ) {
          return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = GRA_IrVizinho (vtGrafos[ inxGrafo ], email);

        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
              "Retorno errado ir vizinho." );

      } /* fim ativa: Testar Ir Vizinho */

     /* Testar  Obter Valor */

      else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
      {

        numLidos = LER_LerParametros( "ii" ,
         &inxGrafo, &CondRetEsperada ) ;

        if ( numLidos != 2 ) {
          return TST_CondRetParm ;
        } /* if */


        return TST_CompararPonteiroNulo( CondRetEsperada , GRA_ObterValor( vtGrafos[ inxGrafo ]) ,
           "Erro em ponteiro de OBTER VALOR."  ) ;

      } /* fim ativa: Testar  Obter Valor */

      /* Testar Avancar Vizinho */
      else if ( strcmp( ComandoTeste , AVANCAR_VIZ_CMD ) == 0 )
      {

        numLidos = LER_LerParametros( "iii" ,
         &inxGrafo, &numElem, &CondRetEsperada ) ;

        if ( numLidos != 3 ) {
          return TST_CondRetParm ;
        } /* if */

        CondRetObtido = GRA_AvancarVizinho (vtGrafos[ inxGrafo ], numElem);
        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
              "Retorno errado avancar vizinho." );
#ifdef _DEBUG
    /* Realizar deturpacao */
        else if ( strcmp( ComandoTeste , DETURPAR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ii" , &inxGrafo, &param) ;

            if ( ( numLidos != 2 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */

      return TST_CompararInt( GRA_CondRetOK , GRA_Deturpar(vtGRAFO[ inxGrafo ], param),
                     "Erro ao deturpar."  ) ;

        } /* fim ativa: Realizar deturpacao */

    /* Realizar verificao estrututral */
        else if ( strcmp( ComandoTeste , VERIFICAR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ii" , &inxGrafo, &param) ;

            if ( ( numLidos != 2 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            GRA_VerificarEstrutura( vtGRAFO[ inxGrafo ], &numErros );

            return TST_CompararInt( param , numErros ,
                     "Total de erros errado ao verificar estrutura."  ) ;

        } /* fim ativa: Realizar verificao estrututral */

#endif

      } /* fim ativa: Testar  Obter Valor */


  return TST_CondRetNaoConhec ;

} /* Fim fun��o: TGRA Efetuar opera��es de teste espec�ficas para Grafo */


/*****  C�digo das fun��es encapsuladas no m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TGRA -Validar indice do Grafo
*
***********************************************************************/

   static int ValidarInxGrafo( int inxGrafo , int Modo )
   {

      if ( ( inxGrafo <  0 )
        || ( inxGrafo >= DIM_VT_GRAFO ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtGrafos[ inxGrafo ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtGrafos[ inxGrafo ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim fun��o: TGRA -Validar indice do grafo */

/***********************************************************************
*
*  $FC Fun��o: TGRA -Destruir valor
*
***********************************************************************/

   void DestruirValor( void ** pValor )
   {

      free( pValor ) ;
      pValor = NULL;

   } /* Fim fun��o: TGRA -Destruir valor */

/***********************************************************************
*
*  $FC Fun��o: TGRA - Comparar valor
*
***********************************************************************/

   int CompararValor( void * pValor1, void * pValor2 )
   {

    PER_tppPerfil pPerfil1;
    char *email;
    pPerfil1 = (PER_tppPerfil) pValor1;
    email = (char*) pValor2;

    return strcmp(email,pPerfil1->email);

   } /* Fim fun��o: TGRA - Comparar valor */


/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/