#if ! defined( CONTROLADOR_ )
#define CONTROLADOR_
/***************************************************************************
*
*  $MCD Módulo de definição: CON Controlador - Rede de Relacionamentos
*
*  Arquivo gerado:              CONTROLADOR.H
*  Letras identificadoras:      CON
*
*
*  Projeto:    Trabalho 2 - Programaçăo Modular
*  Autores:    GB - Gabrielle Brandenburg
*              GC - Gabriel Cantergiani
*              WB - Wellingotn Bezerra
*
*  $HA Histórico de evoluçăo:
*     Versăo      Autor         Data                Observaçőes
*     1.0          GC        18/11/2017       início do desenvolvimento
*
*  $ED Descrição do módulo
*			
*		Implementa o modulo controlador da aplicação Rede de Relacionamentos.
*		Este modulo serve como um centralizador de funcionalidade da aplicação.
*		O Controlador faz a ponte entre o modulo de interface com o usuário e a execução de todas as funcionalidades da aplicação.
*		
*		Este Modulo usa todos os outros modulos do programa, fazendo algumas conexões entre alguns deles.
*
***************************************************************************/
 
#if defined( CONTROLADOR_OWN )
   #define CONTROLADOR_EXT
#else
   #define CONTROLADOR_EXT extern
#endif

#include "GRAFO.H"
#include "PERFIL.H"
#include "MENSAGEM.H"


/***** Declarações exportadas pelo módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: CON Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do Controlador
*
***********************************************************************/


typedef enum {
	
	CON_CondRetOK,					/* Concluiu corretamente */		

	CON_CondRetLimiteString, 		/* String passada é maior que o limite de 100 caracteres */

	CON_CondRetStringVazia,			/* String passada é vazia (nula */

	CON_CondRetErroFormato,			/* Genero passado esta fora do formato aceito */

	CON_CondRetErroCadastro,		/* Ocorreu um erro ao cadastrar um novo Perfil */

	CON_CondRetRedeVazia,			/* A rede de relacionamentos está vazia (não possui nenhum perfil) */

	CON_CondRetNaoAchou,			/* Não achou o perfil procurado */

	CON_CondRetValorNulo,			/* Ponteiro procurado têm valor nulo */

	CON_CondRetAmizadeJaExiste,		/* Amizade que tentou ser criada já existe */

	CON_CondRetAmizadeInvalida,		/* Amizade que tentou ser criada é invalida (ilegal) */

	CON_CondRetAmizadeNaoExiste,

	CON_CondRetFaltouMemoria

} CON_tpCondRet;


/***********************************************************************
*
*  $FC Função: CON  &Criar Perfil
*
*  $ED Descrição da função
*     Checa se parametros estão OK, cria o Perfil, e se tudo estiver ok, mostra as informações do Perfil na tela.
*
*  $EP Parâmetros
*     pNome - nome do perfil a ser criado (max 100 caracteres)
*     pEmail - email do perfil a ser criado (max 100 caracteres)
*	  pCidade - cidade do perfil a ser criado  (max 100 caracteres)
*	  genero - genero do perfil a ser criado  (Somente aceito os caracteres 'M', 'F' e 'O')
*	  pDataNasc - Data de Nascimento do perfil a ser criado (max 100 caracteres)
*
*  $FV Valor retornado
*		- Se executou corretamente retorna CON_CondRetOK
*		- Se alguma string é Nula (vazia), retorna CON_CondRetStringVazia
*		- Se alguma string estorou o limite de 100 caracteres, retorna CON_CondRetLimiteString
*		- Se o genero esta fora do formato indicado, retorna CON_ConRetErroFormato
*		- Se ocorreu algum outro erro no Cadastro do perfil, retorna CON_CondRetErroCadastro
*
***********************************************************************/
CON_tpCondRet CON_CriarPerfil(char *pNome, char *pEmail, char *pCidade, char genero, char *pDataNasc);

/***********************************************************************
*
*  $FC Função: CON  &Buscar Perfil
*
*  $ED Descrição da função
*     Recebe um email e retorna (por referência) um ponteiro para oPerfil associado à este email.
*  $EP Parâmetros
*     email - email do perfil que será buscado (max 100 caracteres)
*     pPerfil - ponteiro no qual será armazenado o endereço do perfil, caso seja encontrado
*
*  $FV Valor retornado
*		- CON_CondRetValorNulo
*		- CON_CondRetStringVazia
*		- CON_CondRetRedeVazia
*		- CON_CondRetNaoAchou
*		- CON_CondRetOK
*
***********************************************************************/
CON_tpCondRet CON_BuscarPerfil(char *email, PER_tppPerfil pPerfil);

/***********************************************************************
*
*  $FC Função: CON  &Mostrar Perfil
*
*  $ED Descrição da função
*     Recebe um email e mostra as informações do perfil associado na tela.
*  $EP Parâmetros
*     email - email do perfil que será mostrado (max 100 caracteres)
*
*  $FV Valor retornado
*		- CON_CondRetValorNulo
*		- CON_CondRetStringVazia
*		- CON_CondRetRedeVazia
*		- CON_CondRetNaoAchou
*		- CON_CondRetOK
*
***********************************************************************/
CON_tpCondRet CON_MostrarPerfil (char *email);


/***********************************************************************
*
*  $FC Função: CON  &Excluir Perfil
*
*  $ED Descrição da função
*     Recebe um email exclui o perfil correspondente da rede de relacionamentos
*  $EP Parâmetros
*     email - email do perfil que será excluido (max 100 caracteres)
*
*  $FV Valor retornado
*		- CON_CondRetValorNulo
*		- CON_CondRetStringVazia
*		- CON_CondRetRedeVazia
*		- CON_CondRetNaoAchou
*		- CON_CondRetOK
*
***********************************************************************/
CON_tpCondRet CON_ExcluirPerfil (char *pEmail);


/***********************************************************************
*
*  $FC Função: CON  &Criar Amizade
*
*  $ED Descrição da função
*		Recebe dois emails, busca os perfis associados a estes emails e cria uma amizade entre eles.     
*
*  $EP Parâmetros
*     email1 - email do perfil 1 (max 100 caracteres)
*     email2 - email do perfil 2 (max 100 caracteres)
*
*  $FV Valor retornado
*		- CON_CondRetValorNulo
*		- CON_CondRetStringVazia
*		- CON_CondRetRedeVazia
*		- CON_CondRetNaoAchou
*		- CON_CondRetAmizadeJaExiste
*		- CON_ConRetAmizadeInvalida
*		- CON_CondRetOK
*
***********************************************************************/
CON_tpCondRet CON_CriarAmizade(char *email1, char *email2);


/***********************************************************************
*
*  $FC Função: CON  &Excluir Amizade
*
*  $ED Descrição da função
*		Recebe dois emails, busca os perfis associados a estes emails e exclui a amizade entre eles (se existir).     
*
*  $EP Parâmetros
*     email1 - email do perfil 1 (max 100 caracteres)
*     email2 - email do perfil 2 (max 100 caracteres)
*
*  $FV Valor retornado
*		- CON_CondRetStringVazia
*		- CON_CondRetRedeVazia
*		- CON_CondRetNaoAchou
*		- CON_ConRetAmizadeInvalida
*		- CON_CondRetOK
*
***********************************************************************/
CON_tpCondRet CON_ExcluirAmizade (char *email1, char *email2);


/***********************************************************************
*
*  $FC Função: CON  &Buscar Amizade
*
*  $ED Descrição da função
*		Busca e mostra todas as amizades de um perfil    
*
*  $EP Parâmetros
*     email - email do perfil no qual serão buscadas as amizades (max 100 caracteres)
*
*  $FV Valor retornado
*		- CON_CondRetValorNulo
*		- CON_CondRetRedeVazia
*		- CON_CondRetNaoAchou
*		- CON_CondRetOK
*
***********************************************************************/
CON_tpCondRet CON_BuscarAmizades(char *email);

/***********************************************************************
*
*  $FC Função: CON  &Enviar Mensagem
*
*  $ED Descrição da função
*		Envia uma mensagem de um perfil para outro. 
*		Não é possível enviar mensagem de um perfil para si mesmo.
*
*  $EP Parâmetros
*     email1 - email do perfil remetente
*     email2 - email do perfil destinatario
*	  texto - cadeia de caracteres do texto da mensagem
*
*  $FV Valor retornado
*		- CON_CondRetValorNulo
*		- CON_CondRetRedeVazia
*		- CON_CondRetNaoAchou
*		- CON_AmizadeNaoExiste
*		- CON_CondRetFaltouMemoria
*		- CON_CondRetOK
*
***********************************************************************/
CON_tpCondRet CON_EnviarMensagem(char *email1, char *email2, char *texto);

/***********************************************************************
*
*  $FC Função: CON  &Carregar Histórico
*
***********************************************************************/
CON_tpCondRet CON_CarregarHistorico(char *pEmail1, char *pEmail2);

#undef CONTROLADOR_EXT

/********** Fim do módulo de definição: CON Controlador **********/

#else
#endif