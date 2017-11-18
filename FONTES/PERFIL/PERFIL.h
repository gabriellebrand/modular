#if ! defined( PERFIL_ )
#define PERFIL_
/***************************************************************************
*  $MCD M�dulo de defini��o: PER  M�dulo Perfil
*
*  Arquivo gerado:              PERFIL.h
*  Letras identificadoras:      PER
*
*  Nome da base de software:    Arcabou�o para a automa��o de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\LISTA.BSW
*
*  Projeto: INF 1301 / 1628 Automatiza��o dos testes de m�dulos C
*  Gestor:  LES/DI/PUC-Rio
*  Autores:    GB - Gabrielle Brandenburg
                GC - Gabriel Cantergiani
                WB - Wellingotn Bezerra
*
*  $HA Hist�rico de evolu��o:
*     Vers�o  Autor    Data     Observa��ess
*     1.0       WB        02/out/2017       Cria��o do m�dulo
*     1.1       WB        14/out/2017       Altera��o da fun��o criarPerfil
*
*  $ED Descri��o do m�dulo
*     Implementa o m�dulo usu�rio.
*     
***************************************************************************/

#if defined( PERFIL_OWN )
   #define PERFIL_EXT
#else
   #define PERFIL_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um Perfil */

typedef struct PER_tagPerfil * PER_tppPerfil ;


/***********************************************************************
*
*  $TC Tipo de dados: PER Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es do modulo Perfil
*
***********************************************************************/

   typedef enum {
	   
 /* 0 */ PER_CondRetOK ,
               /* Concluiu corretamente */

 /* 1 */ PER_CondRetFaltouMemoria ,
               /* Faltou memoria */

 /* 2 */ PER_CondRetPonteiroNulo ,
   		/* Ponteiro Nulo */

 /* 3 */ PER_CondRetStringVazia ,
      /* Ponteiro Nulo */

 /* 4 */ PER_CondRetValorInvalido
      /* Ponteiro Nulo */
   } PER_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: PER  &Criar Perfil
*
*  $ED Descri��o da fun��o
*     Cria um Perfil
*
*  $EP Par�metros
*     pPerfil  - ponteiro para o perfil que ser� criado
*     pNome - nome do perfil a ser criado
*     pEmail - email do perfil a ser criado
*	  pCidade - cidade do perfil a ser criado 
*	  pIdade - idade do perfil a ser criado
*
*  $FV Valor retornado
*		Se executou corretamente retorna o ponteiro para um Perfil.
*
*		Se ocorreu algum erro, por exemplo falta de memoria ou dados errados,
*		a funcao retorna NULL.
*
***********************************************************************/

    PER_tppPerfil  PER_CriarPerfil( char *pNome, char *pEmail, char *pCidade, int pIdade );

/***********************************************************************
 *
 *  $FC Fun��o: PER  &Destruir Perfil
 *
 *  $ED Descri��o da fun��o
 *     Destroi um Perfil
 *
 *  $EP Par�metros
 *     pPerfil  - ponteiro do o perfil que ser� destruido
 *
 *  $FV Valor retornado
 *	    PER_CondRetOK  - destruicao do perfil com sucesso
 *      PER_CondRetPonteiroNulo - se o valor do perfil for NULL
 *
 ***********************************************************************/

    void PER_DestruirPerfil(void * pPerfil);

/***********************************************************************
 *
 *  $FC Fun��o: PER  &Comparar  Perfil
 *
 *  $ED Descri��o da fun��o
 *     Compara dois perfis
 *
 *  $EP Par�metros
 *     pValor1  - ponteiro do o perfil 1
 *     pValor2  - ponteiro do o perfil 2
 *
 *  $FV Valor retornado
 *	    igual a 0  - dois perfis s�o iguais
 *      diferente de 0 - dois perfis s�o diferentes
 *
 ***********************************************************************/

    int PER_compararPerfil(void * pValor1, void * pValor2);

/***********************************************************************
 *
 *  $FC Fun��o: PER  &Mostrar  Perfil
 *
 *  $ED Descri��o da fun��o
 *     Mostra as informa��es de um perfil
 *
 *  $EP Par�metros
 *     pPerfil  - ponteiro de um Perfil
 *
 *  $FV Valor retornado
 *      PER_CondRetOK  - insforma��es do perfil mostradas com sucesso
 *      PER_CondRetPonteiroNulo - valor do perfil � igual a NULL e nao mostra as inf do Perfil
 *
 ***********************************************************************/

PER_tpCondRet PER_MostrarPerfil(PER_tppPerfil pPerfil);

char * PER_recuperaEmail(PER_tppPerfil pPerfil);

#undef PERFIL_EXT

/********** Fim do m�dulo de defini��o: PER  Perfil **********/

#else
#endif
