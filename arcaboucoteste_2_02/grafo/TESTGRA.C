/***************************************************************************
*  $MCI Módulo de implementação: TGRA Teste do módulo Grafo
*
*  Arquivo gerado:              TestGRA.c
*  Letras identificadoras:      TGRA
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: Trabalho 2 - Programa;cão Modular
*  Gestor:  LES/DI/PUC-Rio
*  Autor:  WB - Wellington Bezerra
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       WB   09/out/2017 início desenvolvimento
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
static const char IR_VIZINHO_CMD             [ ] = "=irviziho";



#define DIM_VT_GRAFO   10

GRA_tppGrafo   vtGrafos[ DIM_VT_GRAFO ] ;

typedef struct PER_tagPerfil {

    char nome[100];
        /* Nome do perfil */
    
    char email[20];
        /* Email do perfil */
    
    char cidade[20];
        /* Cidade do perfil */
    
    int idade;
        /* Idade do perfil */

} PER_tpPerfil ;

typedef struct PER_tagPerfil * PER_tppPerfil ;


/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int CompararValor(void * pValor1, void * pValor2) ;


/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TGRA Efetuar operações de teste específicas para Grafo
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     Grafo sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ) {

  int numLidos = -1,
      inxGrafo = -1,
      idade = -1 ;
  char nome[100],
       email[100],
       email2[100],
       cidade[100];

  PER_tppPerfil pPerfil;

  GRA_tpCondRet CondRetObtido;
  GRA_tpCondRet CondRetEsperada;

  
  /* Testar Criar Grafo */

      if ( strcmp( ComandoTeste , CRIAR_GRAFO_CMD ) == 0 )
      {

        numLidos = LER_LerParametros( "i" ,
         &inxGrafo ) ;

        if ( numLidos != 1 ) {
          return TST_CondRetParm ;
        } /* if */
        vtGrafos[ inxGrafo ] =
        GRA_criarGrafo( DestruirValor , CompararValor ) ;

        return TST_CompararPonteiroNulo( 1 , vtGrafos[ inxGrafo ] ,
           "Erro em ponteiro de novo grafo."  ) ;

      } /* fim ativa: Testar Criar Grafo */

  /* Testar Criar vertice */

      else if ( strcmp( ComandoTeste , CRIAR_VERTICE_CMD ) == 0 ) {

          numLidos = LER_LerParametros( "isssii" ,
                       &inxGrafo , &nome, &email, &cidade, &idade , &CondRetEsperada ) ;
          if ( numLidos != 6 ) {
            return TST_CondRetParm ;
          } /* if */

          pPerfil = ( PER_tppPerfil ) malloc( sizeof( PER_tpPerfil ));
          if ( pPerfil == NULL ) {
               return TST_CondRetMemoria ;
          } /* if */
          strcpy( pPerfil->nome , nome ) ;
          strcpy( pPerfil->email , email ) ;
          strcpy( pPerfil->cidade , cidade ) ;
          pPerfil->idade = idade ;

          CondRetObtido = GRA_criarVertice(vtGrafos[ inxGrafo ], pPerfil, email);
          

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
          
          CondRetObtido = GRA_irVertice (vtGrafos[ inxGrafo ], email);

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
          
          CondRetObtido = GRA_excluirVertCorr(vtGrafos[ inxGrafo ]);

          return TST_CompararInt( CondRetEsperada , CondRetObtido ,
              "Retorno errado ao excluir vertice." );

      } /* fim ativa: Excluir Vertice Corrente*/

  /* Testar Excluir Grafo */

      if ( strcmp( ComandoTeste , EXCLUIR_GRAFO_CMD ) == 0 )
      {

        numLidos = LER_LerParametros( "ii" ,
         &inxGrafo, &CondRetEsperada ) ;

        if ( numLidos != 2 ) {
          return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = GRA_destruirGrafo(vtGrafos[ inxGrafo ]);

        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
              "Retorno errado excluir grafo." );

      } /* fim ativa: Testar Excluir Grafo */

  /* Testar Criar Aresta */

      if ( strcmp( ComandoTeste , CRIAR_ARESTA_CMD ) == 0 )
      {

        numLidos = LER_LerParametros( "issi" ,
         &inxGrafo, &email, &email2, &CondRetEsperada ) ;

        if ( numLidos != 4 ) {
          return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = GRA_criarAresta(vtGrafos[ inxGrafo ], email, email2);

        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
              "Retorno errado criar aresta." );

      } /* fim ativa: Testar Criar Aresta */

  /* Testar Excluir Aresta */

      if ( strcmp( ComandoTeste , EXCLUIR_ARESTA_CMD ) == 0 )
      {

        numLidos = LER_LerParametros( "issi" ,
         &inxGrafo, &email, &email2, &CondRetEsperada ) ;

        if ( numLidos != 4 ) {
          return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = GRA_excluirAresta(vtGrafos[ inxGrafo ], email, email2);

        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
              "Retorno errado excluir aresta." );

      } /* fim ativa: Testar Excluir Aresta */

  /* Testar Ir Vizinho */

      if ( strcmp( ComandoTeste , IR_VIZINHO_CMD ) == 0 )
      {

        numLidos = LER_LerParametros( "isi" ,
         &inxGrafo, &email, &CondRetEsperada ) ;

        if ( numLidos != 3 ) {
          return TST_CondRetParm ;
        } /* if */
        
        CondRetObtido = GRA_irVizinho (vtGrafos[ inxGrafo ], email);

        return TST_CompararInt( CondRetEsperada , CondRetObtido ,
              "Retorno errado ir vizinho." );

      } /* fim ativa: Testar Ir Vizinho */




        



          //GRA_tpCondRet GRA_criarVertice(GRA_tppGrafo pGrafo, void *pValor) 

  return TST_CondRetNaoConhec ;

} /* Fim função: TGRA Efetuar operações de teste específicas para Grafo */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: TGRA -Destruir valor
*
***********************************************************************/

   void DestruirValor( void * pValor )
   {

      free( pValor ) ;

   } /* Fim função: TGRA -Destruir valor */

/***********************************************************************
*
*  $FC Função: TGRA - Comparar valor
*
***********************************************************************/

   int CompararValor( void * pValor1, void * pValor2 )
   {

    PER_tppPerfil pPerfil1;
    char *email;
    pPerfil1 = (PER_tppPerfil) pValor1;
    email = (char*) pValor2;

    return strcmp(email,pPerfil1->email);

   } /* Fim função: TGRA - Comparar valor */


/********** Fim do módulo de implementação: Módulo de teste específico **********/