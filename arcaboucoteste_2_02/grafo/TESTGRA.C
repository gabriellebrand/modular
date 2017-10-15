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
*  Autores:    GB - Gabrielle Brandenburg
                GC - Gabriel Cantergiani
                WB - Wellington Bezerra
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       WB   12/out/2017 início desenvolvimento
*
***************************************************************************/


#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Grafo.h"


static const char CRIAR_GRAFO_CMD            [ ] = "=criargrafo";
static const char CRIAR_VERTICE_CMD          [ ] = "=criarvertice";


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
      inxGrafo = -1 ;

  LIS_tppLista pVertice;

  //GRA_tpCondRet CondRetObtido;
  //GRA_tpCondRet CondRetEsperada;

  
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

  /* Testar GRF Adicionar vertice */




        

  /* fim ativa: Testar GRF Adicionar vertice */

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

    PER_tppPerfil pPerfil;
    char *email;
    pPerfil = (PER_tppPerfil) pValor1;
    email = (char*) pValor2;

    return strcmp(email,pPerfil->email);

   } /* Fim função: TGRA - Comparar valor */


/********** Fim do módulo de implementação: Módulo de teste específico **********/