/***************************************************************************
*  $MCI Módulo de implementação: TPER Teste perfil de símbolos
*
*  Arquivo gerado:              TestPER.c
*  Letras identificadoras:      TPER
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatização dos testes de módulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores:    GB - Gabrielle Brandenburg
                GC - Gabriel Cantergiani
                WB - Wellington Bezerra
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*     1       WB   08/out/2017 início desenvolvimento
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Perfil.h"


static const char CRIAR_PERFIL_CMD         [ ] = "=criarperfil"     ;

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



/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TPER Efetuar operações de teste específicas para Perfil
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     Perfil sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

TST_tpCondRet TST_EfetuarComando( char * ComandoTeste ) {

  int indexPerfil = -1,
      idade = -1,
      NumLidos = -1;

  char nome[100],
       email[100],
       cidade[100];

  PER_tpCondRet CondRetObtido   = PER_CondRetOK ;
  PER_tpCondRet CondRetEsperada = PER_CondRetOK ;

  PER_tppPerfil* pPerfil = NULL;

  
  //* Testar PER Criar Perfil */

  if ( strcmp( ComandoTeste , CRIAR_PERFIL_CMD ) == 0 )
  {
    pPerfil = ( PER_tppPerfil * ) malloc( sizeof( PER_tpPerfil ) ) ;
    NumLidos = LER_LerParametros( "isssi" , &indexPerfil, 
                                            &nome,
                                            &email,
                                            &cidade,
                                            &idade) ;
    if ( NumLidos != 5 )
    {
      return TST_CondRetParm ;
    } /* if */

    CondRetObtido = PER_CriarPerfil( pPerfil, nome, email, cidade, idade );
    
    return TST_CompararInt( CondRetEsperada , CondRetObtido ,
      "Retorno errado ao criar perfil." );

  } 

  return TST_CondRetNaoConhec ;

} /* Fim função: TRD Efetuar operações de teste específicas para Perfil */



/********** Fim do módulo de implementação: Módulo de teste específico **********/