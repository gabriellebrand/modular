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
*     1.0       WB        02/out/2017       Criação do módulo
*     1.1       WB        14/out/2017       Alteração da função criarPerfil
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

 /* 2 */ PER_CondRetPonteiroNulo ,
   		/* Ponteiro Nulo */

 /* 3 */ PER_CondRetStringVazia ,
      /* Ponteiro Nulo */

 /* 4 */ PER_CondRetValorInvalido
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
*		Se executou corretamente retorna o ponteiro para um Perfil.
*
*		Se ocorreu algum erro, por exemplo falta de memoria ou dados errados,
*		a funcao retorna NULL.
*
***********************************************************************/

    PER_tppPerfil  PER_CriarPerfil( char *pNome, char *pEmail, char *pCidade, int pIdade );

/***********************************************************************
 *
 *  $FC Função: PER  &Destruir Perfil
 *
 *  $ED Descrição da função
 *     Destroi um Perfil
 *
 *  $EP Parâmetros
 *     pPerfil  - ponteiro do o perfil que será destruido
 *
 *  $FV Valor retornado
 *	    PER_CondRetOK  - destruicao do perfil com sucesso
 *      PER_CondRetPonteiroNulo - se o valor do perfil for NULL
 *
 ***********************************************************************/

    void PER_DestruirPerfil(void * pPerfil);

/***********************************************************************
 *
 *  $FC Função: PER  &Comparar  Perfil
 *
 *  $ED Descrição da função
 *     Compara dois perfis
 *
 *  $EP Parâmetros
 *     pValor1  - ponteiro do o perfil 1
 *     pValor2  - ponteiro do o perfil 2
 *
 *  $FV Valor retornado
 *	    igual a 0  - dois perfis são iguais
 *      diferente de 0 - dois perfis são diferentes
 *
 ***********************************************************************/

    int PER_compararPerfil(void * pValor1, void * pValor2);

/***********************************************************************
 *
 *  $FC Função: PER  &Mostrar  Perfil
 *
 *  $ED Descrição da função
 *     Mostra as informações de um perfil
 *
 *  $EP Parâmetros
 *     pPerfil  - ponteiro de um Perfil
 *
 *  $FV Valor retornado
 *      PER_CondRetOK  - insformações do perfil mostradas com sucesso
 *      PER_CondRetPonteiroNulo - valor do perfil é igual a NULL e nao mostra as inf do Perfil
 *
 ***********************************************************************/

PER_tpCondRet PER_MostrarPerfil(PER_tppPerfil pPerfil);

char * PER_recuperaEmail(PER_tppPerfil pPerfil);

#undef PERFIL_EXT

/********** Fim do módulo de definição: PER  Perfil **********/

#else
#endif
