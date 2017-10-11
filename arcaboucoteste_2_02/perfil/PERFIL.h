#if ! defined( PERFIL_ )
#define PERFIL_
/***************************************************************************
*  $MCD Módulo de definição: PER  Módulo Perfil
*
*  Arquivo gerado:              PERFIL.h
*  Letras identificadoras:      PER
*
*  Nome da base de software:    ArcabouÁo para a automaÁ„o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 AutomatizaÁ„o dos testes de mÛdulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores:    GB - Gabrielle Brandenburg
                GC - Gabriel Cantergiani
                WB - Wellingotn Bezerra
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observaçõess
*     1       wbs   02/out/2017 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa o módulo usuário.
*     
***************************************************************************/

#if defined( PERFIL_OWN )
   #define PERFIL_EXT
#else
   #define PERFIL_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um Perfil */

typedef struct PER_tagPerfil * PER_tppPerfil ;


/***********************************************************************
*
*  $TC Tipo de dados: PER Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do modulo Perfil
*
***********************************************************************/

   typedef enum {
	   
 /* 0 */ PER_CondRetOK ,
               /* Concluiu corretamente */

 /* 1 */ PER_CondRetFaltouMemoria ,
               /* Faltou memoria */

 /* 2 */ PER_CondRetPonteiroNulo
   		/* Ponteiro Nulo */

   } PER_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PER  &Criar Perfil
*
*  $ED Descrição da função
*     Cria um Perfil
*
*  $EP Parâmetros
*     pPerfil  - ponteiro para o perfil que será criado
*     pNome - nome do perfil a ser criado
*     pEmail - email do perfil a ser criado
*	  pCidade - cidade do perfil a ser criado 
*	  pIdade - idade do perfil a ser criado
*
*  $FV Valor retornado
*	    PER_CondRetOK  - criou sem problemas
*
***********************************************************************/

PER_tpCondRet  PER_CriarPerfil( PER_tppPerfil* ppPerfil, char *pNome, char *pEmail, char *pCidade, int pIdade );

//void PER_MostrarPerfil(PER_tppPerfil *pPerfil);

PER_tpCondRet PER_destroirPerfil(PER_tppPerfil *pPerfil);

#undef PERFIL_EXT

/********** Fim do módulo de definição: PER  Perfil **********/

#else
#endif
