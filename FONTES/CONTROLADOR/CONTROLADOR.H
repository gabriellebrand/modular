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
	
	CON_CondRetOK,

	CON_CondRetLimiteString,

	CON_CondRetStringVazia,

	CON_CondRetErroFormato,

	CON_CondRetErroCadastro,


} CON_tpCondRet;


/***********************************************************************
*
*  $FC Função: CON  &Criar Perfil
*
*  $ED Descrição da função
*     Checa se parametros estão OK, cria o Perfil, insere como um vertice no Grafo e, se tudo estiver ok, mostra as informações do Perfil na tela.
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
