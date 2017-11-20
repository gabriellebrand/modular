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

static GRA_tppGrafo Grafo = NULL; /* Ponteiro para o Grafo utilizado na rede de relacionamentos*/


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

/***********************************************************************
*
*  $FC Função: CON  &Buscar Perfil
*
***********************************************************************/

CON_tpCondRet CON_BuscarPerfil(char *email, PER_tppPerfil pPerfil) {

	GRA_tpCondRet ret;

	if (email == NULL)
		return CON_CondRetValorNulo;
	if (strlen(email) == 0)
		return CON_CondRetStringVazia;

	ret = GRA_IrVertice(Grafo, (void*)email);

	if (ret != GRA_CondRetOK) 
		return CON_CondRetRedeVazia;
	
	if (ret == GRA_CondRetVerticeNaoExiste)
		return CON_CondRetNaoAchou;

	pPerfil = (PER_tppPerfil) GRA_ObterValor(Grafo);

	if (pPerfil == NULL)
		return CON_CondRetValorNulo;

	return CON_CondRetOK;
	
}/* Fim função: CON  &Buscar Perfil */

/***********************************************************************
*
*  $FC Função: CON  &Mostrar Perfil
*
***********************************************************************/

CON_tpCondRet CON_MostrarPerfil (char *email) {

	PER_tppPerfil pPerfil;
	CON_tpCondRet ret;

	/* Busca o perfil*/
	ret = CON_BuscarPerfil (email, pPerfil);

	if (ret!=CON_CondRetOK)
		return ret;

	/* Mostra o perfil, caso encontrado*/

	ret = PER_MostrarPerfil (pPerfil);

	if(ret!=PER_CondRetOK)
		return CON_CondRetValorNulo;

	return CON_CondRetOK;
	
} /* Fim função: CON  &Mostrar Perfil */

/***********************************************************************
*
*  $FC Função: CON  &Criar Amizade
*
***********************************************************************/
CON_tpCondRet CON_CriarAmizade(char *email1, char *email2) {
	GRA_tpCondRet ret;

	if ((email1 == NULL) || (email2 == NULL))
		return CON_CondRetValorNulo;
	if ((strlen(email1) == 0) || (strlen(email2) == 0))
		return CON_CondRetStringVazia;

	ret = GRA_CriarAresta(Grafo,(void*)email1, (void*)email2);

	switch (ret) {
		case GRA_CondRetVerticeNaoExiste:
		return CON_CondRetNaoAchou;

		case GRA_CondRetFaltouMemoria:
		//não sei o que precisa ser feito
		//tentar de novo? reportar que faltou memoria?

		case GRA_CondRetArestaJaExiste:
		return CON_CondRetAmizadeJaExiste;

		case GRA_CondRetArestaIlegal:
		return CON_ConRetAmizadeInvalida;

		case GRA_CondRetOK:
		return CON_CondRetOK;

		default:
		return CON_CondRetRedeVazia;
	}
		
} /* Fim função: CON  &Criar Amizade */


/***********************************************************************
*
*  $FC Função: CON  &Buscar Amizades
*
***********************************************************************/
CON_tpCondRet CON_BuscarAmizades(char *email) {
	GRA_tpCondRet ret;
	int i = 0;
	void * val;
	PER_tppPerfil perAmigo;
	//1. buscar o vertice relativo ao email passado
	ret = GRA_IrVertice (Grafo, email);

	if (ret == GRA_CondRetVerticeNaoExiste)
		return CON_CondRetNaoAchou;
	if (ret != GRA_CondRetOK)
		return CON_CondRetRedeVazia;

	//2. acessar a lista de arestas do vertice
	//3. retornar o perfil de cada uma das arestas acessadas
	while((ret = GRA_AvancarVizinho (Grafo, i, val)) == GRA_CondRetOK) {
		perAmigo = (PER_tppPerfil)val;
		//4. chamar aqui a funcao que imprime os valores do perfil
		//TODO: trocar isso por obter campos do perfil e chamar a funcao da interface que imprime os campos!!
		PER_MostrarPerfil(perAmigo);
		i++;
	}

	switch (ret) {
		case GRA_CondRetNaoPossuiAresta || GRA_CondRetFimArestas:
			return CON_CondRetNaoAchou;
		case GRA_CondRetValorNulo:
			return CON_CondRetValorNulo;
		default:
			return CON_CondRetRedeVazia;
	}
	
} /* Fim função: CON  &Buscar Amizades */

//TODO:

//CON_EnviarMensagem();

//CON_CarregarHistorico();

//CON_ExcluirPerfil();

//CON_ExcluirAmizade();
