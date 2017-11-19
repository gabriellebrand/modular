/**************************************************************************
*  $MCI Módulo de implementação: CON controlador
*
*  Arquivo gerado:              CONTROLADOR.c
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
***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PERFIL.H"
#include "grafo.h"

#define CONTROLADOR_OWN
#include "CONTROLADOR.H"
#undef CONTROLADOR_OWN


/*******   Protótipo das Funções Encapsuladas no Módulo *********************/



/************** Dados encapsulados no modulo   *********************************************************/

static GRA_tppGrafo Grafo;			/* Ponteiro para o Grafo utilizado na rede de relacionamentos*/


/*******  Código das Funções Exportadas pelo Módulo ***********************/


/***********************************************************************
*
*  $FC Função: CON  &Criar Perfil
*
***********************************************************************/

CON_tpCondRet CON_CriarPerfil(char *pNome, char *pEmail, char *pCidade, char genero, char *pDataNasc) {

	PER_tppPerfil perfil;
	PER_tpCondRet retornoPerfil;
	GRA_tpCondRet retornoGrafo;

	/* Verifica se dados recebidos são válidos*/
	if ( pNome==NULL || pEmail==NULL || pCidade==NULL || pDataNasc==NULL)
		return CON_CondRetStringVazia;

	if (strlen(pNome)>100 || strlen(pEmail)>100 || strlen(pCidade)>100 || strlen(pDataNasc)>100 ) 
		return CON_CondRetLimiteString;

	if (genero!='M' && genero!='F' && genero!='O')
		return CON_CondRetErroFormato;

	/* Cria um ponteiro para o perfil*/
	perfil = PER_CriarPerfil (pNome, pEmail, pCidade, genero, pDataNasc);

	if (perfil==NULL)
		return CON_CondRetErroCadastro;

	/* Caso o Grafo ainda não exista, cria um Grafo*/
	if(Grafo==NULL)
		Grafo = GRA_CriarGrafo (PER_DestruirPerfil, PER_CompararPerfil);

	/*Adiciona o Perfil como um vertice do grafo*/
	retornoGrafo = GRA_CriarVertice (Grafo, perfil, pEmail);

	if (retornoGrafo != GRA_CondRetOK)
		return CON_CondRetErroCadastro;

	/*Mostra as informações do perfil cadastrado na tela*/
	retornoPerfil = PER_MostrarPerfil(perfil);

	if (retornoPerfil!= PER_CondRetOK)
		return CON_CondRetErroCadastro;

	return CON_CondRetOK;

}  /* Fim função: CON  &Criar Perfil */



/*  por fazer...

CON_BuscarPerfil();

CON_CriarAmizade();

CON_BuscarAmizade();

CON_EnviarMensagem();

CON_CarregarHistorico();
*/

/************************************************************************
