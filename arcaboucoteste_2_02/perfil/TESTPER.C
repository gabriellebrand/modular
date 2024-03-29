/***************************************************************************
*  $MCI M�dulo de implementa��o: TPER Teste perfil de s�mbolos
*
*  Arquivo gerado:              TestPER.c
*  Letras identificadoras:      TPER
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores:    GB - Gabrielle Brandenburg
                GC - Gabriel Cantergiani
                WB - Wellington Bezerra
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��es
*     1.0          WB        02/out/2017       Cria��o do m�dulo
*     1.1          WB        14/out/2017       Altera��o do teste criarperfil
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Perfil.h"


static const char CRIAR_PERFIL_CMD            [ ] = "=criarperfil";
static const char DESTRUIR_PERFIL_CMD         [ ] = "=destruirperfil";
static const char COMPARAR_PERFIL_CMD         [ ] = "=compararperfil";
static const char MOSTRAR_PERFIL_CMD          [ ] = "=mostrarperfil";

#define DIM_VT_PERFIL   10

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


PER_tppPerfil   vtPerfil[ DIM_VT_PERFIL ] ;

/*****  C�digo das fun��es exportadas pelo m�dulo  *****/

/***********************************************************************
*
*  $FC Fun��o: TPER Efetuar opera��es de teste espec�ficas para Perfil
*
*  $ED Descri��o da fun��o
*     Efetua os diversos comandos de teste espec�ficos para o m�dulo
*     Perfil sendo testado.
*
*  $EP Par�metros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ) {

  int indexPerfil = -1,
      idade = -1,
      NumLidos = -1,
      indexPerfil1 = -2,
      indexPerfil2 = -2;

  char nome[100],
       email[100],
       cidade[100];

  PER_tpCondRet CondRetObtido;
  PER_tpCondRet CondRetEsperada;

  /* Criar Perfil */

  if ( strcmp( ComandoTeste , CRIAR_PERFIL_CMD ) == 0 )
  {
    
    NumLidos = LER_LerParametros( "isssi" , &indexPerfil, 
                                            &nome,
                                            &email,
                                            &cidade,
                                            &idade) ;
    if ( NumLidos != 5 )
    {
      return TST_CondRetParm ;
    } /* if */

    vtPerfil[ indexPerfil ] = PER_CriarPerfil( nome, email, cidade, idade );
    
    return TST_CompararPonteiroNulo( 1 , vtPerfil[ indexPerfil ] ,
               "Erro em ponteiro de novo Perfil."  ) ;

  } /* fim ativa: Criar Perfil */

  /* Destruir Perfil */

  else if ( strcmp( ComandoTeste , DESTRUIR_PERFIL_CMD ) == 0 )
  {
    NumLidos = LER_LerParametros( "ii" , &indexPerfil,
                                         &CondRetEsperada ); 
                                           
    if ( NumLidos != 2 )
    {
      return TST_CondRetParm ;
    } /* if */

    CondRetObtido = PER_DestruirPerfil(vtPerfil[ indexPerfil ]);
    
    return TST_CompararInt( CondRetEsperada , CondRetObtido ,
      "Retorno errado ao destruir perfil." );

  } /* fim ativa: Destruir Perfil */

    /* Comparar Perfil */

  else if ( strcmp( ComandoTeste , COMPARAR_PERFIL_CMD ) == 0 )
  {
    NumLidos = LER_LerParametros( "iii" , &indexPerfil1,
                                          &indexPerfil2,
                                         &CondRetEsperada ); 
                                           
    if ( NumLidos != 3 )
    {
      return TST_CondRetParm ;
    } /* if */

    CondRetObtido = PER_compararPerfil( vtPerfil[indexPerfil1] , vtPerfil[indexPerfil2]->email );
    
    return TST_CompararInt( CondRetEsperada , CondRetObtido ,
      "Retorno errado ao comparar perfil." );

  } /* fim ativa: Comparar Perfil */ 

    /* Mostrar Perfil */

  else if ( strcmp( ComandoTeste , MOSTRAR_PERFIL_CMD ) == 0 )
  {
    NumLidos = LER_LerParametros( "ii" , &indexPerfil,
                                         &CondRetEsperada ); 
                                           
    if ( NumLidos != 2 )
    {
      return TST_CondRetParm ;
    } /* if */

    CondRetObtido = PER_MostrarPerfil( vtPerfil[ indexPerfil ] );
    
    return TST_CompararInt( CondRetEsperada , CondRetObtido ,
      "Retorno errado ao mostrar perfil." );

  } /* fim ativa: Mostrar Perfil */ 



  return TST_CondRetNaoConhec ;

} /* Fim fun��o: TPER Efetuar opera��es de teste espec�ficas para Perfil */



/********** Fim do m�dulo de implementa��o: M�dulo de teste espec�fico **********/
