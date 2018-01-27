#if ! defined( INTERFACE_ )
#define INTERFACE_

/***************************************************************************
*
*  $MCD Módulo de definição: INT Interface - Rede de Relacionamentos
*
*  Arquivo gerado:              INTERFACE.H
*  Letras identificadoras:      INT
*
*
*  Projeto:    Trabalho 2 - Programaçăo Modular
*  Autores:    GB - Gabrielle Brandenburg
*              GC - Gabriel Cantergiani
*              WB - Wellingotn Bezerra
*
*  $HA Histórico de evoluçăo:
*     Versăo      Autor         Data                Observaçőes
*     1.0          GC        26/11/2017       início do desenvolvimento
*
*  $ED Descrição do módulo
*			
*		Implementa o modulo interface da aplicação Rede de Relacionamentos.
*		Este modulo serve como uma interface de funcionalidade da aplicação.
*		Neste modulo e' feita a interacao com o usuario. Ele e' responsavel por capturar e retornar dados.
*
***************************************************************************/

#if defined( INTERFACE_OWN )
   #define INTERFACE_EXT
#else
   #define INTERFACE_EXT extern
#endif

#include "CONTROLADOR.H"

#undef INTERFACE_EXT


/***** Declarações exportadas pelo módulo *****/


/***********************************************************************
*
*  $FC Função: INT  &Menu Principal
*
*  $ED Descrição da função
*		Mostra o menu principal de navegacao e envia o usuario para a opcao selecionada.
*
***********************************************************************/
void INT_MenuPrincipal();

/***********************************************************************
*
*  $FC Função: INT  &Mostrar Mensagem
*
*  $ED Descrição da função
*		Recebe o texto da mensagem e o nome do remetente e imprime.
*
*  $EP Parâmetros
*		pTexto - string do texto da mensagem
*		pRemetente - string do nome do perfil remetente
*
***********************************************************************/
void INT_MostrarMensagem(char *pTexto, char * pRemetente);

/***********************************************************************
*
*  $FC Função: INT  &Mostrar Perfil
*
*  $ED Descrição da função
*		Recebe os dados do perfil e imprime.
*		Os parametros que receberem NULL nao serao impressos.
*
*  $EP Parâmetros
*		pTexto - string do texto da mensagem
*		pRemetente - string do nome do perfil remetente
*
***********************************************************************/
void INT_MostrarPerfil(char * email, char * nome, char * cidade, char *genero, char *dataNasc);


/********** Fim do módulo de definição: INT Interface **********/

#else
#endif
